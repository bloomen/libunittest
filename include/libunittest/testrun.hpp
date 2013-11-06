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
#include <iostream>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace internals {
/**
 * @brief Observes the progress of an asynchronous operation and waits until
 *  the operation is finished. It throws exception testfailure in case the
 *  given maximum run time is exceeded.
 * @param future The asynchronous operation
 * @param timeout_sec The maximum allowed run time in seconds (ignored if <= 0)
 * @param has_timed_out Whether a timeout has occurred (note the reference)
 * @param resolution_ms The temporal resolution in number of milliseconds
 */
void
observe_and_wait(std::future<void>&& future,
                 double timeout_sec,
                 std::atomic<bool>& has_timed_out,
                 int resolution_ms=100);
/**
 * @brief Launches a given functor asynchronously
 * @param functor The functor
 * @param timeout_sec The maximum allowed run time in seconds (ignored if <= 0)
 * @param has_timed_out Whether a timeout has occurred (note the reference)
 */
template<typename Functor>
void
launch_async(Functor&& functor,
             double timeout_sec,
             std::atomic<bool>& has_timed_out)
{
    std::future<void> future = std::async(std::launch::async, std::move(functor));
    internals::observe_and_wait(std::move(future), timeout_sec, has_timed_out);
}
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
     * @param functor A functor taking no arguments
     */
    template<typename Functor>
    void
    execute(Functor&& functor)
    {
        auto suite = testsuite::instance();
        if (suite->get_arguments().dry_run()) {
            log_success();
        } else {
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
            if (functor.has_timed_out())
                has_timed_out(functor.timeout());
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

    void
    has_timed_out(double timeout);

};
/**
 * @brief Stores an instance of the test class and the test to be run.
 *  By using the ()-operator the test is executed.
 */
template<typename TestCase>
struct testfunctor final {
    /**
     * @brief Constructor storing instance and method
     * @param test An instance of the test class
     * @param method The test to be run
     * @param timeout The test timeout
     * @param has_timed_out Whether the test has timed out
     */
    testfunctor(TestCase& test,
                void (TestCase::*method)(),
                double timeout,
                std::atomic<bool>* has_timed_out)
        : test_(&test), method_(method), timeout_(timeout),
          has_timed_out_(has_timed_out)
    {}
    /**
     * @brief Executes the test
     */
    void
    operator()()
    {
        (test_->*method_)();
    }
    /**
     * @brief Returns the test timeout
     * @returns The test timeout
     */
    double
    timeout() const
    {
        return timeout_;
    }
    /**
     * @brief Returns whether the test has timed out
     * @returns Whether the test has timed out
     */
    bool
    has_timed_out() const
    {
        return has_timed_out_->load();
    }

private:
    TestCase* test_;
    void (TestCase::*method_)();
    double timeout_;
    std::atomic<bool>* has_timed_out_;
};
/**
 * @brief Updates the class name according to some heuristics
 * @param class_name The current class name
 * @param typeid_name The class' type ID name
 * @param class_maps Mappings from test class IDs to test class names
 */
void
update_class_name(std::string& class_name,
                  const std::string& typeid_name,
                  const std::map<std::string, std::string>& class_maps);
/**
 * @brief Updates the test name according to some heuristics
 * @param test_name The current test name
 * @param typeid_name The class' type ID name
 * @param class_maps Mappings from test class IDs to test class names
 */
void
update_test_name(std::string& test_name,
                 const std::string& typeid_name,
                 const std::map<std::string, std::string>& class_maps);
/**
 * @brief A class for storing test information
 */
template<typename TestCase>
struct testrun_store {
    /**
     * @brief Constructor storing test information
     * @param method A pointer to the test method
     * @param class_name The name of test class
     * @param test_name The name of the test method
     * @param timeout The test timeout
     * @param has_timed_out Whether the test has timed out
     */
    testrun_store(void (TestCase::*method)(),
                  const std::string& class_name,
                  const std::string& test_name,
                  double timeout,
                  std::atomic<bool>* has_timed_out)
        : method_(method), class_name_(class_name), test_name_(test_name),
          timeout_(timeout), has_timed_out_(has_timed_out)
    {
        const auto& class_maps = testsuite::instance()->get_class_maps();
        update_class_name(class_name_, typeid(TestCase).name(), class_maps);
        update_test_name(test_name_, typeid(TestCase).name(), class_maps);
    }
    /**
     * @brief Destructor
     */
    virtual
    ~testrun_store()
    {}

protected:
    /**
     * @brief A pointer to the test
     */
    void (TestCase::*method_)();
    /**
     * @brief The name of test class
     */
    std::string class_name_;
    /**
     * @brief The name of the test
     */
    std::string test_name_;
    /**
     * @brief The test timeout
     */
    double timeout_;
    /**
     * @brief Whether the test has timed out
     */
    std::atomic<bool>* has_timed_out_;

};
/**
 * @brief A free test run without a test context providing
 *  the ()-operator to run the test
 */
template<typename TestCase>
struct testrun_free final : testrun_store<TestCase> {
    /**
     * @brief Constructor assigning test information
     * @param method A pointer to the test method
     * @param class_name The name of test class
     * @param test_name The name of the test method
     * @param timeout The test timeout
     * @param has_timed_out Whether the test has timed out
     */
    testrun_free(void (TestCase::*method)(),
                 const std::string& class_name,
                 const std::string& test_name,
                 double timeout,
                 std::atomic<bool>* has_timed_out)
        : testrun_store<TestCase>(method, class_name, test_name, timeout, has_timed_out)
    {}
    /**
     * @brief Runs the test
     */
    void
    operator()()
    {
        testrunner runner(this->class_name_, this->test_name_);
        if (runner.is_executed()) {
            TestCase test;
            test.set_up();
            testfunctor<TestCase> functor(test, this->method_, this->timeout_, this->has_timed_out_);
            runner.execute(std::move(functor));
            test.tear_down();
        }
    }

};
/**
 * @brief A test run within a test context providing
 *  the ()-operator to run the test
 */
template<typename TestContext,
         typename TestCase>
struct testrun_context final : testrun_store<TestCase> {
    /**
     * @brief Constructor assigning test information
     * @param context A pointer to the test context
     * @param method A pointer to the test method
     * @param class_name The name of test class
     * @param test_name The name of the test method
     * @param timeout The test timeout
     * @param has_timed_out Whether the test has timed out
     */
    testrun_context(TestContext* context,
                    void (TestCase::*method)(),
                    const std::string& class_name,
                    const std::string& test_name,
                    double timeout,
                    std::atomic<bool>* has_timed_out)
        : testrun_store<TestCase>(method, class_name, test_name, timeout, has_timed_out),
          context_(context)
    {}
    /**
     * @brief Runs the test
     */
    void
    operator()()
    {
        testrunner runner(this->class_name_, this->test_name_);
        if (runner.is_executed()) {
            TestCase test;
            test.set_test_context(context_);
            test.set_up();
            testfunctor<TestCase> functor(test, this->method_, this->timeout_, this->has_timed_out_);
            runner.execute(std::move(functor));
            test.tear_down();
        }
    }

private:
    TestContext* context_;
};
/**
 * @brief Updates the local timeout by assigning the global timeout
 *  from the test suite if the local one is not greater than zero
 * @param local_timeout The local timeout in seconds
 */
void
update_local_timeout(double& local_timeout);

} // internals

/**
 * @brief A test run
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
    internals::update_local_timeout(timeout);
    std::atomic<bool> has_timed_out(false);
    internals::testrun_free<TestCase>
        functor(method, class_name, test_name, timeout, &has_timed_out);
    internals::launch_async(std::move(functor), timeout, has_timed_out);
}
/**
 * @brief A test run with a test context
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
    internals::update_local_timeout(timeout);
    std::atomic<bool> has_timed_out(false);
    internals::testrun_context<TestContext, TestCase>
        functor(&context, method, class_name, test_name, timeout, &has_timed_out);
    internals::launch_async(std::move(functor), timeout, has_timed_out);
}

} // unittest
