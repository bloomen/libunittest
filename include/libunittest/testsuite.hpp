/**
 * @brief The test suite collecting test information
 * @file testsuite.hpp
 */
#pragma once
#include <libunittest/userargs.hpp>
#include <libunittest/testresults.hpp>
#include <libunittest/testlog.hpp>
#include <libunittest/pimplpattern.hpp>
#include <string>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace internals {
/**
 * @brief The test suite collecting test information (singleton, thread-safe)
 */
class testsuite final : public pimplpattern<testsuite> {
public:
    /**
     * @brief Returns a pointer to the instance of this class
     * @returns A pointer to the instance of this class
     */
    static testsuite*
    instance();
    /**
     * @brief Assigns the user arguments
     * @param arguments The user arguments
     */
    void
    set_arguments(const userargs& arguments);
    /**
     * @brief Returns a reference to the user arguments
     * @returns A reference to the user arguments
     */
    userargs&
    get_arguments() const;
    /**
     * @brief Returns a reference to the vector of registered test runs
     * @returns A reference to the vector of registered test runs
     */
    std::vector<std::function<void()>>&
    get_test_runs() const;
    /**
     * @brief Returns the accumulated test results
     * @returns The test results
     */
    testresults
    get_results() const;

private:
    friend class testrunner;

    template<typename T>
    friend class testregistry;

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

    void
    add_test_run(const std::function<void()>& test_run);

};

} // internals
} // unittest
