/**
 * @brief The test suite collecting test information
 * @file testsuite.hpp
 */
#pragma once
#include <libunittest/testresults.hpp>
#include <libunittest/testlog.hpp>
#include <libunittest/pimplpattern.hpp>
#include <string>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief The test suite collecting test information (singleton, thread-safe)
 */
class testsuite : public pimplpattern<testsuite> {
public:
    /**
     * @brief Returns a pointer to the instance of this class
     * @returns A pointer to the instance of this class
     */
    static testsuite*
    instance();
    /**
     * @brief Sets whether output is verbose for running tests (default: false)
     * @param verbose Whether output is verbose for running tests
     */
    void
    set_verbose(bool verbose);
    /**
     * @brief Sets whether to stop running after the first test fails (default: false)
     * @param failure_stop Whether to stop running after first failure
     */
    void
    set_failure_stop(bool failure_stop);
    /**
     * @brief Sets a filter on the full test name. This will make the suite
     *  execute only those tests that begin with the given filter string (default: "")
     * @param name_filter The filter string
     */
    void
    set_name_filter(const std::string& name_filter);
    /**
     * @brief Sets a certain test to be run. This supersedes the name filter (default: "")
     * @param test_name The test name
     */
    void
    set_test_name(const std::string& test_name);
    /**
     * @brief Sets whether to handle exceptions. Setting it to false
     *  is useful for debugging purposes (default: true)
     * @param handle_exceptions Whether to handle exceptions
     */
    void
    set_handle_exceptions(bool handle_exceptions);
    /**
     * @brief Returns whether to handle exceptions
     * @returns Whether to handle exceptions
     */
    bool
    get_handle_exceptions() const;
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
    make_keep_running(const testlog& log);

    void
    start_timing();

    void
    stop_timing();

    void
    collect(const testlog& log);

    bool
    is_test_run(const std::string& class_name,
                const std::string& test_name) const;

    bool
    is_verbose() const;

};

} // unittest
