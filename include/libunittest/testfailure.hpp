/**
 * @brief The testfailure class to indicate test failures
 * @file testfailure.hpp
 */
#pragma once
#include <string>
#include <stdexcept>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief The exception class to indicate test failures
 */
class testfailure final : public std::runtime_error {
public:
    /**
     * @brief Constructor
     * @param message The exception message
     */
    explicit
    testfailure(const std::string& message);
};

} // unittest
