/**
 * @brief Formatting functionality
 * @file formatting.hpp
 */
#pragma once
#include "testsuite.hpp"
#include "typetraits.hpp"
#include <string>
#include <sstream>
#include <type_traits>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace core {

template<typename T>
struct converter_int {
	std::string
	operator()(T&& value)
	{
	    std::ostringstream stream;
	    stream << value;
	    return stream.str();
	}
};

template<typename T>
struct converter_float {
	std::string
	operator()(T&& value)
	{
	    std::ostringstream stream;
	    stream.precision(unittest::core::testsuite::instance()->get_arguments().max_value_precision);
	    stream << value;
	    return stream.str();
	}
};

template<typename T>
struct converter_other {
	std::string
	operator()(T&& value)
	{
	    std::ostringstream stream;
	    stream << value;
		return "'" + limit_string_length(stream.str(), unittest::core::testsuite::instance()->get_arguments().max_string_length) + "'";
	}
};

template<typename T,
		 bool is_integral,
		 bool is_float>
struct converter;

template<typename T>
struct converter<T, true, false> {
	typedef converter_int<T> type;
};

template<typename T>
struct converter<T, false, true> {
	typedef converter_float<T> type;
};

template<typename T>
struct converter<T, false, false> {
	typedef converter_other<T> type;
};
/**
 * @brief Converts a given value to string by taking into account
 * 	the maximum string length and the maximum value precision
 * @param value The value
 * @returns A string
 */
template<typename T>
std::string
str(T&& value)
{
	static_assert(unittest::core::is_output_streamable<T>::value, "argument is not output streamable");
	typename unittest::core::converter<T, std::is_integral<T>::value, std::is_floating_point<T>::value>::type converter;
	return converter(std::forward<T>(value));
}
/**
 * @brief Converts a given value to string. Spec. for bool
 * @param value The value
 * @returns A string
 */
template<>
std::string
str<bool&>(bool& value);
/**
 * @brief Converts a given value to string. Spec. for bool
 * @param value The value
 * @returns A string
 */
template<>
std::string
str<bool>(bool&& value);

} // core
} // unittest
