#pragma once
#include <libunittest/teststatus.hpp>
#include <string>
#include <ostream>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Stores logging info about a single test
 */
struct testlog {
    /**
     * @brief Constructor
     */
    testlog();
    /**
     * @brief The name of the test class
     */
    std::string class_name;
    /**
     * @brief The name of the test method
     */
    std::string test_name;
    /**
     * @brief Whether the test ran successfully
     */
    bool successful;
    /**
     * @brief The test status
     */
    teststatus status;
    /**
     * @brief The name of the error type. Empty if test was successful
     */
    std::string error_type;
    /**
     * @brief The result message
     */
    std::string message;
    /**
     * @brief The test duration in seconds
     */
    double duration;
};
/**
 * @brief Writes a test start message to the given output stream
 * @param stream The output stream
 * @param log A test log
 * @param verbose Whether to use verbose output
 */
void
write_test_start_message(std::ostream& stream,
                         const testlog& log,
                         bool verbose);
/**
 * @brief Writes a test end message to the given output stream
 * @param stream The output stream
 * @param log A test log
 * @param verbose Whether to use verbose output
 */
void
write_test_end_message(std::ostream& stream,
                       const testlog& log,
                       bool verbose);

} // unittest
