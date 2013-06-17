#pragma once
#include <libunittest/testresults.hpp>
#include <libunittest/testlog.hpp>
#include <string>
#include <vector>
#include <chrono>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief The test suite controlling the test runs (singleton, thread-safe)
 */
class testsuite {
public:
    /**
     * @brief Returns a pointer to the instance of this class
     * @returns A pointer to the instance of this class
     */
    static testsuite*
    instance();
    /**
     * @brief Sets whether output is verbose for running tests
     * @param verbose Whether output is verbose for running tests
     */
    void
    set_verbose(bool verbose);
    /**
     * @brief Sets whether to stop running after the first test fails
     * @param failure_stop Whether to stop running after first failure
     */
    void
    set_failure_stop(bool failure_stop);
    /**
     * @brief Sets a filter on the full test name. This will make the suite
     *  execute only those tests that begin with the given filter string
     * @param name_filter The filter string
     */
    void
    set_name_filter(const std::string& name_filter);
    /**
     * @brief Sets a certain test to be run. This supersedes the name filter
     * @param test_name The test name
     */
    void
    set_test_name(const std::string& test_name);
    /**
     * @brief Returns the accumulated test results
     * @returns The test results
     */
    testresults
    get_results() const;

private:
    friend class testrunner;

    testsuite();

    testsuite(const testsuite&) = delete;

    testsuite&
    operator=(const testsuite&) = delete;

    void
    collect(const testlog&);

    void
    start_timing();

    void
    stop_timing();

    double
    get_duration() const;

    void
    set_keep_running(bool keep_running);

    bool
    get_keep_running() const;

    bool
    is_test_run(const std::string& class_name,
                const std::string& test_name) const;

    bool keep_running_;
    bool verbose_;
    bool failure_stop_;
    long n_tests_;
    long n_successes_;
    long n_failures_;
    long n_errors_;
    long n_skipped_;
    std::vector<testlog> testlogs_;
    std::string name_filter_;
    std::string test_name_;
    std::chrono::high_resolution_clock::time_point start_;
    std::chrono::high_resolution_clock::time_point end_;
};

} // unittest
