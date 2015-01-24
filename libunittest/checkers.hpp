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
check_epsilon(T&& epsilon,
              const std::string& caller,
              Args&&... message)
{
    if (!(epsilon > epsilon - epsilon)) {
        const std::string text = "epsilon not greater than zero";
        unittest::fail(caller, text, std::forward<Args>(message)...);
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
check_range_bounds(T&& lower,
                   U&& upper,
                   const std::string& caller,
                   Args&&... message)
{
    if (lower > upper) {
        const std::string text = "lower bound cannot be greater than upper bound";
        unittest::fail(caller, text, std::forward<Args>(message)...);
    }
}

} // core
} // unittest
