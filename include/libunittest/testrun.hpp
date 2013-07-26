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
/**
 * @brief Unit testing in C++
 */
namespace unittest {
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
     */
    template<typename TestCase>
    void
    execute(TestCase& test,
            void (TestCase::*method)())
    {
        if (testsuite::instance()->get_handle_exceptions()) {
            try {
                (test.*method)();
                log_success();
            } catch (const testfailure& e) {
                log_failure(e);
            } catch (const std::exception& e) {
                log_error(e);
            } catch (...) {
                log_unknown_error();
            }
        } else {
            (test.*method)();
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
 */
template<typename TestCase>
void
testrun(void (TestCase::*method)(),
        const std::string& class_name,
        const std::string& test_name)
{
    testrunner runner(class_name, test_name);
    if (runner.is_executed()) {
        TestCase test;
        test.set_up();
        runner.execute(test, method);
        test.tear_down();
    }
}
/**
 * @brief A test run with a test context (thread-safe)
 * @param context The test context
 * @param method A pointer to the method to be run
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 */
template<typename TestContext,
         typename TestCase>
void
testrun(TestContext& context,
        void (TestCase::*method)(),
        const std::string& class_name,
        const std::string& test_name)
{
    testrunner runner(class_name, test_name);
    if (runner.is_executed()) {
        TestCase test;
        test.set_test_context(&context);
        test.set_up();
        runner.execute(test, method);
        test.tear_down();
    }
}

} // unittest
