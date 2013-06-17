#pragma once
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief An enumeration for the test status
 */
enum teststatus : unsigned int {
    success = 0,
    failure = 1,
    error = 2,
    skipped = 3
};

} // unittest
