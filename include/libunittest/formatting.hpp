/**
 * @brief Formatting functionality
 * @file formatting.hpp
 */
#pragma once
#include <libunittest/testsuite.hpp>
#include <string>
#include <sstream>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace core {
/**
 * @brief Converts a given string stream to string by taking into account
 *  the maximum string length
 * @param stream The string stream
 * @returns A string
 */
std::string
stream_to_string(const std::ostringstream& stream);
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
    std::ostringstream stream;
    stream.precision(unittest::core::testsuite::instance()->get_arguments().max_value_precision);
    stream << value;
    return unittest::core::stream_to_string(stream);
}
/**
 * @brief Converts a given value to string. Spec. for bool
 * @param value The value
 * @returns A string
 */
template<>
std::string
str<bool>(const bool& value);

} // core
} // unittest
