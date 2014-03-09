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
class testfailure : public std::runtime_error {
public:
    /**
     * @brief Constructor
     * @param assertion The name of the assertion
     * @param message The exception message
     */
    testfailure(const std::string& assertion,
                const std::string& message);
    /**
     * @brief Destructor
     */
    ~testfailure() throw ();
    /**
     * @brief Returns the name of the assertion
     * @returns The name of the assertion
     */
    std::string
    assertion() const;

private:
    std::string assertion_;
};

} // unittest
