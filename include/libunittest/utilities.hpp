/**
 * @brief Utilities used throughout this library
 * @file utilities.hpp
 */
#pragma once
#include <ostream>
#include <string>
#include <chrono>
#include <sstream>
#include <regex>
#include <limits>
#include <future>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace internals {
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
 * @brief Writes a horizontal bar to the given output stream
 * @param stream The output stream
 * @param character The character to repeat
 * @param length The length of the bar
 */
void
write_horizontal_bar(std::ostream& stream,
                     char character,
                     int length=79);
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
 *  The bounds are included
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
    return !(value < lower) && !(value > upper);
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
/**
 * @brief Calls each function of a given vector of functions
 * @param functions The vector of functions
 * @param n_threads The number of concurrent threads, ignored if <= 1
 * @returns The number of function calls
 */
long
call_functions(const std::vector<std::function<void()>>& functions,
               int n_threads=1);
/**
 * @brief Limits a given string to some maximum length
 * @param value The string
 * @param max_length The maximum length
 * @returns A string not exceeding a length of max_length
 */
std::string
limit_string_length(const std::string& value,
                    int max_length);
/**
 * @brief Builds a string from given filename and line number
 * @param filename The name of the file
 * @param linenumber The line number within the file
 * @returns A string build from given filename and line number
 */
std::string
string_of_file_and_line(const std::string& filename,
                        int linenumber);
/**
 * @brief Ensures that all futures passed will wait for the threads
 *  they've spawned to finish. This makes the futures happy.
 * @param stream An output stream
 * @param futures The vector of lonely futures
 * @param verbose Whether output is verbose
 */
void
make_futures_happy(std::ostream& stream,
                   const std::vector<std::future<void>>& futures,
                   bool verbose);
/**
 * @brief Gets a value from a map for a given key
 * @param map The map
 * @param key The key
 * @returns The value
 * @throws std::runtime_error if key not found in map
 */
template<typename Map>
typename Map::mapped_type
get_from_map(const Map& map,
             const typename Map::key_type& key)
{
    const auto& element = map.find(key);
    if (element==map.end())
        throw std::runtime_error("key not found in map");
    return element->second;
}
/**
 * @brief A utility class to indicate 'no type' property
 */
class notype {};
/**
 * @brief Returns a unique type id
 * @returns A unique type id
 */
template<typename T>
std::string
get_type_id()
{
    return typeid(T).name();
}
/**
 * @brief Removes leading and trailing white characters
 * @param value The string to trim
 * @returns The new string
 */
std::string
trim(std::string value);
/**
 * @brief Checks whether a given string has a valid numeric representation
 * @param value The string to check
 * @returns Whether a given string has a valid numeric representation
 */
bool
is_numeric(const std::string& value);
/**
 * @brief Converts a given string to a number of type T
 * @param value The string to convert
 * @returns The number
 * @throws std::invalid_argument if given string is not numeric
 */
template<typename T>
T
to_number(const std::string& value)
{
    std::istringstream stream(value);
    double number;
    if (stream >> number) {
        return static_cast<T>(number);
    } else {
        throw std::invalid_argument("Not numeric: " + value);
    }
}

} // internals

/**
 * @brief Joins an arbitrary number of input arguments to a single string.
 *  All arguments must implement the << operator
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
    internals::write_to_stream(stream, args...);
    return std::move(stream.str());
}
/**
 * @brief Machine epsilon of float
 */
const float feps = std::numeric_limits<float>::epsilon();
/**
 * @brief Machine epsilon of double
 */
const double deps = std::numeric_limits<double>::epsilon();

} // unittest
