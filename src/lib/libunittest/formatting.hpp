/**
 * @brief Formatting functionality
 * @file formatting.hpp
 */
#pragma once
#include "testsuite.hpp"
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
struct tostr_converter_int {
    /**
     * @brief Converts an int to string
     * @param value The value to convert
     * @returns A string
     */
    template<typename T>
    std::string
    operator()(const T& value)
    {
        std::ostringstream stream;
        stream << value;
        return stream.str();
    }
};
/**
 * @brief Converts a float to string
 */
struct tostr_converter_float {
    /**
     * @brief Converts a float to string
     * @param value The value to convert
     * @returns A string
     */
    template<typename T>
    std::string
    operator()(const T& value)
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
struct tostr_converter_other {
    /**
     * @brief Converts a value to string
     * @param value The value to convert
     * @returns A string
     */
    template<typename T>
    std::string
    operator()(const T& value)
    {
        std::ostringstream stream;
        stream << value;
        return "'" + limit_string_length(stream.str(), unittest::core::testsuite::instance()->get_arguments().max_string_length) + "'";
    }
};
/**
 * @brief Converts a value to string
 */
template<bool is_integral,
         bool is_float>
struct tostr_converter;
/**
 * @brief Converts a value to string. Spec. for int
 */
template<>
struct tostr_converter<true, false> {
    /**
     * @brief The actual converter type
     */
    typedef unittest::core::tostr_converter_int type;
};
/**
 * @brief Converts a value to string. Spec. for float
 */
template<>
struct tostr_converter<false, true> {
    /**
     * @brief The actual converter type
     */
    typedef unittest::core::tostr_converter_float type;
};
/**
 * @brief Converts a value to string. Spec. for other than int or float
 */
template<>
struct tostr_converter<false, false> {
    /**
     * @brief The actual converter type
     */
    typedef unittest::core::tostr_converter_other type;
};
/**
 * @brief Converts a given value to string by taking into account
 * 	the maximum string length and the maximum value precision
 * @param value The value
 * @returns A string
 */
template<typename T>
std::string
str(const T& value)
{
    typename unittest::core::tostr_converter<std::is_integral<T>::value, std::is_floating_point<T>::value>::type converter;
    return converter(value);
}
/**
 * @brief Converts a given value to string. Spec. for bool
 * @param value The value
 * @returns A string
 */
template<>
std::string
str<bool>(const bool& value);

struct tostr_if_converter_arithmetic {

    template<typename T>
    std::string
    operator()(const std::string& prefix, const T& value, const std::string& postfix)
    {
        return prefix + unittest::core::str(value) + postfix;
    }
};

struct tostr_if_converter_other {

    template<typename T>
    std::string
    operator()(const std::string&, const T&, const std::string&)
    {
        return "";
    }
};

template<bool is_arithmetic>
struct tostr_if_converter;

template<>
struct tostr_if_converter<true> {
    typedef unittest::core::tostr_if_converter_arithmetic type;
};

template<>
struct tostr_if_converter<false> {
    typedef unittest::core::tostr_if_converter_other type;
};

template<typename T>
std::string
str_if(const std::string& prefix, const T& value, const std::string& postfix="")
{
    typename unittest::core::tostr_if_converter<std::is_arithmetic<T>::value>::type converter;
    return converter(prefix, value, postfix);
}

} // core
} // unittest
