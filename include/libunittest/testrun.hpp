#pragma once
#include <libunittest/teststatus.hpp>
#include <libunittest/testfailure.hpp>
#include <libunittest/testsuite.hpp>
#include <libunittest/testlog.hpp>
#include <libunittest/pimplpattern.hpp>
#include <string>
#include <iostream>
#include <chrono>
#include <typeinfo>
#include <stdexcept>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief The test runner that is called by the testrun function
 */
class testrunner : public pimplpattern<testrunner> {
public:
    /**
     * @brief Constructor
     * @param class_name The name of the test class
     * @param test_name The name of the current test method
     */
    testrunner(const std::string& class_name,
               const std::string& test_name);
    /**
     * @brief Destructor
     */
    virtual ~testrunner();
    /**
     * @brief Returns whether to execute the current test
     * @returns Whether to execute the current test
     */
    bool
    is_executed();
    /**
     * @brief Executes the test method
     * @param test An instance of a testcase class
     * @param method A test method belonging to the testcase class
     */
    template<typename TestCase>
    void
    execute(TestCase& test,
            void (TestCase::*method)())
    {
        try {
            (test.*method)();
            log_.status = teststatus::success;
            log_.message = "ok";
        } catch (const testfailure& e) {
            log_.status = teststatus::failure;
            log_.error_type = "testfailure";
            log_.message = e.what();
        } catch (const std::exception& e) {
            log_.status = teststatus::error;
            log_.error_type = typeid(e).name();
            log_.message = e.what();
        } catch (...) {
            log_.status = teststatus::error;
            log_.error_type = "Unknown exception";
            log_.message = "Unknown message";
        }
    }

private:

    testrunner(const testrunner&) = delete;

    testrunner&
    operator=(const testrunner&) = delete;

    testlog log_;
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
