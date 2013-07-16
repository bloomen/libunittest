#pragma once
#include <ostream>
#include <string>
#include <chrono>
#include <sstream>
#include <regex>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Escapes a string for use in an XML document
 * @param data Some string
 * @returns The escaped string
 */
std::string
xml_escape(const std::string& data);
/**
 * @brief Generates the ISO8601 time stamp from a time point object
 * @param time_point The time point object
 * @param local_time Whether to convert to local time (if false converts to UTC)
 * @returns The ISO8601 time stamp (e.g. 2013-06-29T14:12:05)
 */
std::string
make_iso_timestamp(const std::chrono::system_clock::time_point& time_point,
                   bool local_time=true);
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
 * @brief Casts a duration value to seconds
 * @param duration The duration value
 * @returns The duration in seconds
 */
double
duration_in_seconds(const std::chrono::duration<double>& duration);
/**
 * @brief Checks if two values are equal up to some epsilon
 * @param first A value
 * @param second Another value
 * @param eps The epsilon
 * @returns Whether the values are equal up to some epsilon
 */
template<typename T,
         typename U,
         typename V>
bool
is_approx_equal(const T& first,
                const U& second,
                const V& eps)
{
    V diff = 0;
    if (first > second)
        diff = static_cast<V>(first - second);
    else if (first < second)
        diff = static_cast<V>(second - first);
    return diff < eps;
}
/**
 * @brief Checks whether the elements in two ranges are approx. equal
 *  up to some epsilon
 * @param first1 An input iterator
 * @param last1 An input iterator
 * @param first2 An input iterator
 * @param eps The epsilon
 * @returns Whether the elements in the two ranges are approx. equal
 */
template <typename InputIterator1,
          typename InputIterator2,
          typename T>
bool
is_approx_equal(InputIterator1 first1,
                InputIterator1 last1,
                InputIterator2 first2,
                const T& eps)
{
    while (first1 != last1) {
        if (!is_approx_equal(*first1, *first2, eps))
            return false;
        ++first1; ++first2;
    }
    return true;
}
/**
 * @brief Checks if a value is in a given range.
 *  The bounds are excluding
 * @param value A value
 * @param lower The lower bound
 * @param upper The upper bound
 * @returns Whether the value is in a given range
 */
template<typename T,
         typename U,
         typename V>
bool
is_in_range(const T& value,
            const U& lower,
            const V& upper)
{
    return value > lower && value < upper;
}
/**
 * @brief Checks if a value is in a container
 * @param value A value
 * @param container A container
 * @returns Whether the value is in the container
 */
template<typename T,
         typename Container>
bool
is_contained(const T& value,
             const Container& container)
{
    auto first = std::begin(container);
    auto last = std::end(container);
    return std::find(first, last, value) != last;
}
/**
 * @brief Checks if a value is approx. in a container
 *  up to some epsilon
 * @param value A value
 * @param container A container
 * @param eps The epsilon
 * @returns Whether the value is approx. in the container
 */
template<typename T,
         typename Container,
         typename U>
bool
is_approx_contained(const T& value,
                    const Container& container,
                    const U& eps)
{
    auto first = std::begin(container);
    auto last = std::end(container);
    while (first!=last) {
        if (is_approx_equal(*first, value, eps)) return true;
        ++first;
    }
    return false;
}
/**
 * @brief Checks if two containers are equal
 * @param first A container
 * @param second Another container
 * @returns Whether the containers are equal
 */
template<typename Container1,
         typename Container2>
bool
is_containers_equal(const Container1& first,
                    const Container2& second)
{
    const bool equal_first = std::equal(std::begin(first),
                                        std::end(first),
                                        std::begin(second));
    const bool equal_second = std::equal(std::begin(second),
                                         std::end(second),
                                         std::begin(first));
    return equal_first && equal_second;
}
/**
 * @brief Checks if two containers are approx. equal
 *  up to some epsilon
 * @param first A container
 * @param second Another container
 * @param eps The epsilon
 * @returns Whether the two containers are approx. equal
 */
template<typename Container1,
         typename Container2,
         typename V>
bool
is_containers_approx_equal(const Container1& first,
                           const Container2& second,
                           const V& eps)
{
    const bool equal_first = is_approx_equal(std::begin(first),
                                             std::end(first),
                                             std::begin(second),
                                             eps);
    const bool equal_second = is_approx_equal(std::begin(second),
                                              std::end(second),
                                              std::begin(first),
                                              eps);
    return equal_first && equal_second;
}
/**
 * @brief Checks if a value matches a regular expression
 * @param value A value
 * @param regex A regular expression
 * @returns Whether a value matches the regular expression
 */
bool
is_regex_matched(const std::string& value,
                 const std::string& regex);
/**
 * @brief Checks if a value matches a regular expression
 * @param value A value
 * @param regex A regular expression
 * @returns Whether a value matches the regular expression
 */
bool
is_regex_matched(const std::string& value,
                 const std::regex& regex);

} // unittest
