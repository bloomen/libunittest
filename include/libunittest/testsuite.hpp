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
/**
 * @brief Returns whether a given test is executed
 * @param test_name The full test name
 * @param exact_name An exact name to be checked for, ignored if empty
 * @param filter_name A filter for the beginning of the test name, ignored if empty
 * @returns Whether a given test is executed
 */
bool
is_test_executed(const std::string& test_name,
                 const std::string& exact_name,
                 const std::string& filter_name);

} // unittest
