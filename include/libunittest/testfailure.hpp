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
     * @param message The message of the test failure
     */
    testfailure(const std::string& assertion,
                const std::string& message);
    /**
     * @brief Destructor
     */
    ~testfailure() noexcept;
    /**
     * @brief Returns the name of the assertion
     * @returns The name of the assertion
     */
    std::string
    assertion() const;
    /**
     * @brief Returns the name of the file in which the test failure occurred
     * @returns The name of the file in which the test failure occurred
     */
    std::string
    filename() const;
    /**
     * @brief Returns the line number in which the test failure occurred
     * @returns The line number in which the test failure occurred
     */
    int
    linenumber() const;

private:
    std::string assertion_;
    std::string filename_;
    int linenumber_;
};

} // unittest
