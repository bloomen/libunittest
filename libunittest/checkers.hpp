/**
 * @brief A collection of check functions to be used with assertions
 * @file checkers.hpp
 */
#pragma once
#include "testfailure.hpp"
#include "typetraits.hpp"
#include <string>
/**
 * @brief Unit testing in C++
 */
namespace unittest {

/**
 * @brief Internal functionality, not relevant for most users
 */
namespace core {
/**
 * @brief Checks if an epsilon is valid
 * @param epsilon The epsilon
 * @param caller The name of the caller
 * @param message If given, is appended to the default fail message
 */
template<typename T,
         typename... Args>
void
check_epsilon(const T& epsilon,
              const std::string& caller,
              const Args&... message)
{
	static_assert(unittest::core::is_lesser_comparable<T>::value, "epsilon is not lesser comparable");
	static_assert(unittest::core::is_greater_comparable<T>::value, "epsilon is not greater comparable");
    if (!(epsilon > static_cast<T>(0))) {
        const std::string text = "epsilon not greater than zero";
        unittest::fail(caller, text, message...);
    }
}
/**
 * @brief Checks if the range bounds are valid
 * @param lower The lower bound
 * @param upper The upper bound
 * @param caller The name of the caller
 * @param message If given, is appended to the default fail message
 */
template<typename T,
         typename U,
         typename... Args>
void
check_range_bounds(const T& lower,
                   const U& upper,
                   const std::string& caller,
                   const Args&... message)
{
	static_assert(unittest::core::is_lesser_comparable<T>::value, "lower is not lesser comparable");
	static_assert(unittest::core::is_greater_comparable<T>::value, "lower is not greater comparable");
	static_assert(unittest::core::is_lesser_comparable<U>::value, "upper is not lesser comparable");
	static_assert(unittest::core::is_greater_comparable<U>::value, "upper is not greater comparable");
    if (lower > upper) {
        const std::string text = "lower bound cannot be greater than upper bound";
        unittest::fail(caller, text, message...);
    }
}

} // core
} // unittest
