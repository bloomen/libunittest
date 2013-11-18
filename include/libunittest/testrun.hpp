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
 * @brief Stores the test to be run and an optional test context.
 *  By using the ()-operator the test is executed.
 */
template<typename TestCase>
struct testfunctor final {
    /**
     * @brief Constructor storing test method and context
     * @param context A pointer to the test context
     * @param method The test to be run
     * @param timeout The test timeout
     * @param has_timed_out Whether the test has timed out
     */
    testfunctor(typename TestCase::context_type* context,
                void (TestCase::*method)(),
                double timeout,
                std::atomic<bool>* has_timed_out)
        : context_(context),
          method_(method),
          timeout_(timeout),
          has_timed_out_(has_timed_out)
    {}
    /**
     * @brief Executes the test
     */
    void
    operator()()
    {
        TestCase test;
        test.set_test_context(context_);
        test.set_up();
        (test.*method_)();
        test.tear_down();
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
    typename TestCase::context_type *context_;
    void (TestCase::*method_)();
    double timeout_;
    std::atomic<bool>* has_timed_out_;
};
/**
 * @brief A test run providing the ()-operator to run the test
 */
template<typename TestCase>
struct testrun_master final {
    /**
     * @brief Constructor assigning test information
     * @param context A pointer to the test context
     * @param method A pointer to the test method
     * @param class_name The name of test class
     * @param test_name The name of the test method
     * @param timeout The test timeout
     * @param has_timed_out Whether the test has timed out
     */
    testrun_master(typename TestCase::context_type* context,
                   void (TestCase::*method)(),
                   const std::string& class_name,
                   const std::string& test_name,
                   double timeout,
                   std::atomic<bool>* has_timed_out)
        : context_(context),
          method_(method),
          class_name_(class_name),
          test_name_(test_name),
          timeout_(timeout),
          has_timed_out_(has_timed_out)
    {}
    /**
     * @brief Runs the test
     */
    void
    operator()()
    {
        testrunner runner(class_name_, test_name_);
        if (runner.is_executed()) {
            testfunctor<TestCase> functor(context_, method_, timeout_, has_timed_out_);
            runner.execute(std::move(functor));
        }
    }

private:
    typename TestCase::context_type* context_;
    void (TestCase::*method_)();
    std::string class_name_;
    std::string test_name_;
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
 * @brief Updates the local timeout by assigning the global timeout
 *  from the test suite if the local one is not greater than zero
 * @param local_timeout The local timeout in seconds
 */
void
update_local_timeout(double& local_timeout);
/**
 * @brief Observes the progress of an asynchronous operation and waits until
 *  the operation has finished or timed out
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

} // internals

/**
 * @brief A test run with a test context
 * @param context The test context
 * @param method A pointer to the method to be run
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
template<typename TestCase>
void
testrun(typename TestCase::context_type& context,
        void (TestCase::*method)(),
        std::string class_name,
        std::string test_name,
        double timeout)
{
    const auto& class_maps = internals::testsuite::instance()->get_class_maps();
    internals::update_class_name(class_name, typeid(TestCase).name(), class_maps);
    internals::update_test_name(test_name, typeid(TestCase).name(), class_maps);
    internals::update_local_timeout(timeout);
    std::atomic<bool> has_timed_out(false);
    internals::testrun_master<TestCase>
        functor(&context, method, class_name, test_name, timeout, &has_timed_out);
    std::future<void> future = std::async(std::launch::async, std::move(functor));
    internals::observe_and_wait(std::move(future), timeout, has_timed_out);
}
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
        std::string class_name,
        std::string test_name,
        double timeout)
{
    typename TestCase::context_type* null_pointer = nullptr;
    testrun(*null_pointer, method, class_name, test_name, timeout);
}

} // unittest
