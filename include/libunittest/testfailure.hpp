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
class testfailure : public std::runtime_error {
public:
    /**
     * @brief Constructor
     * @param message The exception message
     */
    explicit
    testfailure(const std::string& message);
};

} // unittest
