#pragma once
#include <ostream>
#include <string>
#include <chrono>
#include <sstream>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief An overload doing nothing to finish template recursion
 * @param stream An output stream
 */
void
write_to_stream(std::ostream& stream);
/**
 * @brief Writes arguments to an output stream via template recursion
 * @param stream An output stream
 * @param arg An argument
 * @param args An arbitrary number of arguments
 */
template<typename T,
         typename... Args>
void
write_to_stream(std::ostream& stream,
                const T& arg,
                const Args&... args)
{
    stream << arg;
    write_to_stream(stream, args...);
}
/**
 * @brief Joins an arbitrary number of input arguments to a single string. All
 *  arguments must implement the << operator
 * @param arg An argument
 * @param args An arbitrary number of arguments, can be omitted
 * @returns The joined string
 */
template<typename T,
         typename... Args>
std::string
join(const T& arg,
     const Args&... args)
{
    std::ostringstream stream;
    stream << arg;
    write_to_stream(stream, args...);
    return std::move(stream.str());
}
/**
 * @brief Writes a horizontal bar to the given output stream
 * @param stream The output stream
 * @param character The character to repeat
 * @param length The length of the bar
 */
void
write_horizontal_bar(std::ostream& stream,
                     char character,
                     int length=50);
/**
 * @brief Returns whether a given test is executed
 * @param test_name The full test name
 * @param exact_name An exact name to be checked for, ignored if empty
 * @param filter_name A filter for the beginning of the test name, ignored if empty
 * @returns Whether a given test is executed
 */
bool
is_test_executed(const std::string& test_name,
                 const std::string& exact_name,
                 const std::string& filter_name);
/**
 * @brief Casts a duration value to seconds
 * @param duration The duration value
 * @returns The duration in seconds
 */
double
duration_in_seconds(const std::chrono::duration<double>& duration);

} // unittest
