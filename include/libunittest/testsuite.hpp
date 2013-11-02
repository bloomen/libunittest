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
#include <future>
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
     * @brief Returns a reference to the vector of registered class runs
     * @returns A reference to the vector of registered class runs
     */
    std::vector<std::function<void()>>&
    get_class_runs() const;
    /**
     * @brief Returns a reference to the vector of lonely futures
     * @returns A reference to the vector of lonely futures
     */
    std::vector<std::future<void>>&
    get_lonely_futures();
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

    friend void
    observe_and_wait(std::future<void>&&, double, std::atomic<bool>&, int);

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
    add_class_run(const std::function<void()>& class_run);

    void
    add_lonely_future(std::future<void>&& future);

};

} // internals
} // unittest
