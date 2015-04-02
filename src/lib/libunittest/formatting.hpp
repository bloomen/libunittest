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
/**
 * @brief Converts an int to string
 */
template<typename T>
struct tostr_converter_int {
	/**
	 * @brief Converts an int to string
	 * @param value The value to convert
	 * @returns A string
	 */
	std::string
	operator()(T&& value)
	{
	    std::ostringstream stream;
	    stream << value;
	    return stream.str();
	}
};
/**
 * @brief Converts a float to string
 */
template<typename T>
struct tostr_converter_float {
	/**
	 * @brief Converts a float to string
	 * @param value The value to convert
	 * @returns A string
	 */
	std::string
	operator()(T&& value)
	{
	    std::ostringstream stream;
	    stream.precision(unittest::core::testsuite::instance()->get_arguments().max_value_precision);
	    stream << value;
	    return stream.str();
	}
};
/**
 * @brief Converts a value to string
 */
template<typename T>
struct tostr_converter_other {
	/**
	 * @brief Converts a value to string
	 * @param value The value to convert
	 * @returns A string
	 */
	std::string
	operator()(T&& value)
	{
	    std::ostringstream stream;
	    stream << value;
		return "'" + limit_string_length(stream.str(), unittest::core::testsuite::instance()->get_arguments().max_string_length) + "'";
	}
};
/**
 * @brief Converts a value to string
 */
template<typename T,
		 bool is_integral,
		 bool is_float>
struct tostr_converter;
/**
 * @brief Converts a value to string. Spec. for int
 */
template<typename T>
struct tostr_converter<T, true, false> {
	/**
	 * @brief The actual converter type
	 */
	typedef unittest::core::tostr_converter_int<T> type;
};
/**
 * @brief Converts a value to string. Spec. for float
 */
template<typename T>
struct tostr_converter<T, false, true> {
	/**
	 * @brief The actual converter type
	 */
	typedef unittest::core::tostr_converter_float<T> type;
};
/**
 * @brief Converts a value to string. Spec. for other than int or float
 */
template<typename T>
struct tostr_converter<T, false, false> {
	/**
	 * @brief The actual converter type
	 */
	typedef unittest::core::tostr_converter_other<T> type;
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
	typedef typename std::remove_reference<T>::type type;
	static_assert(unittest::core::is_output_streamable<type>::value, "argument is not output streamable");
	typename unittest::core::tostr_converter<T, std::is_integral<type>::value, std::is_floating_point<type>::value>::type converter;
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
