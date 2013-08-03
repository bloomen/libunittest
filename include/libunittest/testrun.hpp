/**
 * @brief The testrun functions and the testrunner class
 * @file testrun.hpp
 */
#pragma once
#include <libunittest/testfailure.hpp>
#include <libunittest/pimplpattern.hpp>
#include <libunittest/testsuite.hpp>
#include <string>
#include <stdexcept>
#include <future>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Observes the progress of an asynchronous operation and waits until
 *  the operation is finished. It throws exception testfailure in case the
 *  given maximum run time is exceeded.
 * @param future The asynchronous operation
 * @param time_out The maximum allowed run time in seconds (ignored if <= 0)
 */
void
observe_and_wait(const std::future<void>& future,
                 double time_out);
/**
 * @brief A bare test run that is called by the testrunner
 * @param test An instance of a test class
 * @param method A test method belonging to the test class
 * @param time_out The maximum allowed run time in seconds (ignored if <= 0)
 */
template<typename TestCase>
void
bare_testrun(TestCase& test,
             void (TestCase::*method)(),
             double time_out)
{
    std::future<void> future = std::async(std::launch::async, std::bind(method, test));
    observe_and_wait(future, time_out);
}
/**
 * @brief The test runner that is called by the testrun function. It executes
 * 	and controls a test run
 */
class testrunner : public pimplpattern<testrunner> {
public:
    /**
     * @brief Constructor preparing for a test run
     * @param class_name The name of the test class
     * @param test_name The name of the current test method
     */
    testrunner(const std::string& class_name,
               const std::string& test_name);
    /**
     * @brief Destructor finishing up a test run
     */
    ~testrunner();
    /**
     * @brief Returns whether to execute the current test
     * @returns Whether to execute the current test
     */
    bool
    is_executed();
    /**
     * @brief Executes the test method
     * @param test An instance of a test class
     * @param method A test method belonging to the test class
     * @param time_out The maximum allowed run time in seconds (ignored if <= 0)
     */
    template<typename TestCase>
    void
    execute(TestCase& test,
            void (TestCase::*method)(),
            double time_out = 0)
    {
        auto suite = testsuite::instance();
        if (suite->get_arguments().handle_exceptions()) {
            try {
                bare_testrun(test, method, time_out);
                log_success();
            } catch (const testfailure& e) {
                log_failure(e);
            } catch (const std::exception& e) {
                log_error(e);
            } catch (...) {
                log_unknown_error();
            }
        } else {
            bare_testrun(test, method, time_out);
            log_success();
        }
    }

private:

    void
    log_success();

    void
    log_failure(const testfailure& e);

    void
    log_error(const std::exception& e);

    void
    log_unknown_error();

};
/**
 * @brief A test run (thread-safe)
 * @param method A pointer to the method to be run
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 * @param time_out The maximum allowed run time in seconds (ignored if <= 0)
 */
template<typename TestCase>
void
testrun(void (TestCase::*method)(),
        const std::string& class_name,
        const std::string& test_name,
        double time_out = 0)
{
    testrunner runner(class_name, test_name);
    if (runner.is_executed()) {
        TestCase test;
        test.set_up();
        runner.execute(test, method, time_out);
        test.tear_down();
    }
}
/**
 * @brief A test run with a test context (thread-safe)
 * @param context The test context
 * @param method A pointer to the method to be run
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 * @param time_out The maximum allowed run time in seconds (ignored if <= 0)
 */
template<typename TestContext,
         typename TestCase>
void
testrun(TestContext& context,
        void (TestCase::*method)(),
        const std::string& class_name,
        const std::string& test_name,
        double time_out = 0)
{
    testrunner runner(class_name, test_name);
    if (runner.is_executed()) {
        TestCase test;
        test.set_test_context(&context);
        test.set_up();
        runner.execute(test, method, time_out);
        test.tear_down();
    }
}

} // unittest
