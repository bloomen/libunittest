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
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
void
observe_and_wait(const std::future<void>& future,
                 double timeout);
/**
 * @brief The test runner that is called by the testrun function. It executes
 * 	and controls a test run
 */
class testrunner final : public pimplpattern<testrunner> {
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
     * @param Functor A functor taking no arguments
     * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
     */
    template<typename Functor>
    void
    execute(Functor functor)
    {
        auto suite = testsuite::instance();
        if (suite->get_arguments().handle_exceptions()) {
            try {
                functor();
                log_success();
            } catch (const testfailure& e) {
                log_failure(e);
            } catch (const std::exception& e) {
                log_error(e);
            } catch (...) {
                log_unknown_error();
            }
        } else {
            functor();
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
 * @brief
 */
template<typename TestCase>
struct testfunctor final {
    /**
     * @brief
     */
    testfunctor(TestCase& test,
                void (TestCase::*method)())
        : test_(&test),
          method_(method)
    {}
    /**
     * @brief
     */
    void operator()() {
        (test_->*method_)();
    }

private:
    TestCase* test_;
    void (TestCase::*method_)();
};
/**
 * @brief
 */
template<typename TestCase>
struct testrun_base {
    /**
     * @brief
     */
    testrun_base(void (TestCase::*method)(),
                 const std::string& class_name,
                 const std::string& test_name)
        : method_(method), class_name_(class_name), test_name_(test_name)
    {}
    /**
     * @brief
     */
    virtual
    ~testrun_base()
    {}

protected:
    /**
     * @brief
     */
    void (TestCase::*method_)();
    /**
     * @brief
     */
    std::string class_name_;
    /**
     * @brief
     */
    std::string test_name_;

};
/**
 * @brief
 */
template<typename TestCase>
struct testrun_free final : testrun_base<TestCase> {
    /**
     * @brief
     */
    testrun_free(void (TestCase::*method)(),
                 const std::string& class_name,
                 const std::string& test_name)
        : testrun_base<TestCase>(method, class_name, test_name)
    {}
    /**
     * @brief
     */
    void operator()()
    {
        testrunner runner(this->class_name_, this->test_name_);
        if (runner.is_executed()) {
            TestCase test;
            test.set_up();
            testfunctor<TestCase> functor(test, this->method_);
            runner.execute(functor);
            test.tear_down();
        }
    }

};
/**
 * @brief
 */
template<typename TestContext,
         typename TestCase>
struct testrun_context final : testrun_base<TestCase> {
    /**
     * @brief
     */
    testrun_context(TestContext* context,
                    void (TestCase::*method)(),
                    const std::string& class_name,
                    const std::string& test_name)
        : testrun_base<TestCase>(method, class_name, test_name), context_(context)
    {}
    /**
     * @brief
     */
    void operator()()
    {
        testrunner runner(this->class_name_, this->test_name_);
        if (runner.is_executed()) {
            TestCase test;
            test.set_test_context(context_);
            test.set_up();
            testfunctor<TestCase> functor(test, this->method_);
            runner.execute(functor);
            test.tear_down();
        }
    }

private:
    TestContext* context_;
};
/**
 * @brief
 */
void
update_timeout(double& timeout);
/**
 * @brief A test run (thread-safe)
 * @param method A pointer to the method to be run
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
template<typename TestCase>
void
testrun(void (TestCase::*method)(),
        const std::string& class_name,
        const std::string& test_name,
        double timeout)
{
    update_timeout(timeout);
    testrun_free<TestCase> functor(method, class_name, test_name);
    std::future<void> future = std::async(std::launch::async, functor);
    observe_and_wait(future, timeout);
}
/**
 * @brief A test run with a test context (thread-safe)
 * @param context The test context
 * @param method A pointer to the method to be run
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
template<typename TestContext,
         typename TestCase>
void
testrun(TestContext& context,
        void (TestCase::*method)(),
        const std::string& class_name,
        const std::string& test_name,
        double timeout)
{
    update_timeout(timeout);
    testrun_context<TestContext, TestCase> functor(&context, method, class_name, test_name);
    std::future<void> future = std::async(std::launch::async, functor);
    observe_and_wait(future, timeout);
}

} // unittest
