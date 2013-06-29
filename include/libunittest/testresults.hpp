#pragma once
#include <libunittest/testlog.hpp>
#include <ostream>
#include <vector>
#include <chrono>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Stores the test results
 */
struct testresults {
    /**
     * @brief Constructor
     */
    testresults();
    /**
     * @brief Whether all tests ran successfully
     */
    bool successful;
    /**
     * @brief The number of tests
     */
    long n_tests;
    /**
     * @brief The number of test successes
     */
    long n_successes;
    /**
     * @brief The number of test failures
     */
    long n_failures;
    /**
     * @brief The number of test errors
     */
    long n_errors;
    /**
     * @brief The number of skipped tests
     */
    long n_skipped;
    /**
     * @brief The duration of all tests in seconds
     */
    double duration;
    /**
     * @brief A vector of testlog instances. One instance for each test
     */
    std::vector<testlog> testlogs;
};
/**
 * @brief Writes the test results as an XML to the given output stream
 * @param stream The output stream
 * @param results The test results
 * @param time_point The time point used in the root tag (defaults to now)
 */
void
write_xml(std::ostream& stream,
          const testresults& results,
          const std::chrono::system_clock::time_point& time_point=std::chrono::system_clock::now());
/**
 * @brief Writes the test summary to the given output stream
 * @param stream The output stream
 * @param results The test results
 */
void
write_summary(std::ostream& stream,
              const testresults& results);
/**
 * @brief Writes the error info to the given output stream
 * @param stream The output stream
 * @param results The test results
 */
void
write_error_info(std::ostream& stream,
                 const testresults& results);

} // unittest
