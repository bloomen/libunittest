/**
 * @brief Functionality to run tests
 * @file testrun.hpp
 */
#pragma once
#include <libunittest/testfailure.hpp>
#include <libunittest/pimplpattern.hpp>
#include <libunittest/testsuite.hpp>
#include <libunittest/utilities.hpp>
#include <string>
#include <stdexcept>
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
 * @brief The test monitor logs information about a single test
 */
class testmonitor final : public pimplpattern<testmonitor> {
public:
    /**
     * @brief Constructor
     * @param class_name The name of the test class
     * @param test_name The name of the current test method
     */
    testmonitor(const std::string& class_name,
                const std::string& test_name);
    /**
     * @brief Destructor
     */
    ~testmonitor();
    /**
     * @brief Returns whether to execute the current test
     * @returns Whether to execute the current test
     */
    bool
    is_executed();
    /**
     * @brief Logs success for the current test
     */
    void
    log_success();
    /**
     * @brief Logs failure for the current test
     * @param e The failure exception
     */
    void
    log_failure(const testfailure& e);
    /**
     * @brief Logs error for the current test
     * @param e The error exception
     */
    void
    log_error(const std::exception& e);
    /**
     * @brief Logs unknown error for the current test
     */
    void
    log_unknown_error();
    /**
     * @brief Sets a certain timeout in seconds
     * @param timeout The timeout in seconds
     */
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
     * @brief Constructor
     * @param context A pointer to the test context
     * @param method The test to be run
     * @param class_name The name of the test class
     * @param test_name The name of the current test method
     * @param dry_run Whether a dry run is performed
     * @param handle_exceptions Whether to handle unexpected exceptions
     * @param timeout The test timeout
     * @param has_timed_out Whether the test has timed out
     */
    testfunctor(typename TestCase::context_type* context,
                void (TestCase::*method)(),
                std::string class_name,
                std::string test_name,
                bool dry_run,
                bool handle_exceptions,
                double timeout,
                std::atomic<bool>* has_timed_out)
        : context_(context),
          method_(method),
          class_name_(std::move(class_name)),
          test_name_(std::move(test_name)),
          dry_run_(dry_run),
          handle_exceptions_(handle_exceptions),
          timeout_(timeout),
          has_timed_out_(has_timed_out)
    {}
    /**
     * @brief Executes the test
     */
    void
    operator()()
    {
        testmonitor monitor(class_name_, test_name_);
        if (monitor.is_executed()) {
            if (dry_run_) {
                monitor.log_success();
            } else {
                std::unique_ptr<TestCase> test;
                run(test, monitor);
            }
        }
    }

private:

    void
    run(std::unique_ptr<TestCase>& test,
        testmonitor& monitor)
    {
        if (construct(test, monitor)) {
            if (set_up(test, monitor)) {
                if (execute(test, monitor)) {
                    tear_down(test, monitor);
                }
            }
            if (has_timed_out_->load())
                monitor.has_timed_out(timeout_);
        }
    }

    bool
    do_nothing(std::unique_ptr<TestCase>& test,
               testmonitor& monitor)
    {
        return true;
    }

    bool
    handle(std::unique_ptr<TestCase>& test,
           testmonitor& monitor,
           bool (testfunctor::*function)
                       (std::unique_ptr<TestCase>&, testmonitor&),
           bool (testfunctor::*error_callback)
                       (std::unique_ptr<TestCase>&, testmonitor&))
    {
        if (handle_exceptions_) {
            try {
                (this->*function)(test, monitor);
                monitor.log_success();
                return true;
            } catch (const testfailure& e) {
                (this->*error_callback)(test, monitor);
                monitor.log_failure(e);
                return false;
            } catch (const std::exception& e) {
                (this->*error_callback)(test, monitor);
                monitor.log_error(e);
                return false;
            } catch (...) {
                (this->*error_callback)(test, monitor);
                monitor.log_unknown_error();
                return false;
            }
        } else {
            try {
                (this->*function)(test, monitor);
                monitor.log_success();
                return true;
            } catch (const testfailure& e) {
                (this->*error_callback)(test, monitor);
                monitor.log_failure(e);
                return false;
            }
        }
    }

    bool
    construct(std::unique_ptr<TestCase>& test,
              testmonitor& monitor)
    {
        return handle(test, monitor,
                      &testfunctor<TestCase>::_construct,
                      &testfunctor<TestCase>::do_nothing);
    }

    bool
    _construct(std::unique_ptr<TestCase>& test,
               testmonitor& monitor)
    {
        test = std::move(std::unique_ptr<TestCase>(new TestCase));
        test->set_test_context(context_);
        return true;
    }

    bool
    set_up(std::unique_ptr<TestCase>& test,
           testmonitor& monitor)
    {
        return handle(test, monitor,
                      &testfunctor<TestCase>::_set_up,
                      &testfunctor<TestCase>::tear_down);
    }

    bool
    _set_up(std::unique_ptr<TestCase>& test,
            testmonitor& monitor)
    {
        test->set_up();
        return true;
    }

    bool
    execute(std::unique_ptr<TestCase>& test,
            testmonitor& monitor)
    {
        return handle(test, monitor,
                      &testfunctor<TestCase>::_execute,
                      &testfunctor<TestCase>::tear_down);
    }

    bool
    _execute(std::unique_ptr<TestCase>& test,
             testmonitor& monitor)
    {
        (test.get()->*method_)();
        return true;
    }

    bool
    tear_down(std::unique_ptr<TestCase>& test,
              testmonitor& monitor)
    {
        return handle(test, monitor,
                      &testfunctor<TestCase>::_tear_down,
                      &testfunctor<TestCase>::do_nothing);
    }

    bool
    _tear_down(std::unique_ptr<TestCase>& test,
               testmonitor& monitor)
    {
        test->tear_down();
        return true;
    }

    typename TestCase::context_type *context_;
    void (TestCase::*method_)();
    std::string class_name_;
    std::string test_name_;
    bool dry_run_;
    bool handle_exceptions_;
    double timeout_;
    std::atomic<bool>* has_timed_out_;
};
/**
 * @brief Updates the class name according to some heuristics
 * @param class_name The current class name
 * @param class_id The class' type ID
 * @param class_maps Mappings from test class IDs to test class names
 */
void
update_class_name(std::string& class_name,
                  const std::string& class_id,
                  const std::map<std::string, std::string>& class_maps);
/**
 * @brief Updates the test name according to some heuristics
 * @param test_name The current test name
 * @param class_id The class' type ID
 * @param class_maps Mappings from test class IDs to test class names
 */
void
update_test_name(std::string& test_name,
                 const std::string& class_id,
                 const std::map<std::string, std::string>& class_maps);
/**
 * @brief Updates the local timeout by assigning the global timeout
 *  from the test suite if the local one is not greater than zero
 * @param local_timeout The local timeout in seconds
 * @param global_timeout The global timeout in seconds
 */
void
update_local_timeout(double& local_timeout,
                     double global_timeout);
/**
 * @brief Observes the progress of an asynchronous operation and waits until
 *  the operation has finished or timed out
 * @param future The asynchronous operation
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @param has_timed_out Whether a timeout has occurred (note the reference)
 * @param resolution The temporal resolution in milliseconds
 */
void
observe_and_wait(std::future<void>&& future,
                 double timeout,
                 std::atomic<bool>& has_timed_out,
                 std::chrono::milliseconds resolution=std::chrono::milliseconds(100));

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
    auto suite = internals::testsuite::instance();
    const auto& class_maps = suite->get_class_maps();
    const std::string class_id = internals::get_type_id<TestCase>();
    internals::update_class_name(class_name, class_id, class_maps);
    internals::update_test_name(test_name, class_id, class_maps);
    const bool dry_run = suite->get_arguments().dry_run();
    const bool handle_exceptions = suite->get_arguments().handle_exceptions();
    const double global_timeout = suite->get_arguments().timeout();
    internals::update_local_timeout(timeout, global_timeout);
    std::atomic<bool> has_timed_out(false);
    internals::testfunctor<TestCase> functor(&context, method,
                                             std::move(class_name),
                                             std::move(test_name),
                                             dry_run, handle_exceptions,
                                             timeout, &has_timed_out);
    if (handle_exceptions) {
        std::future<void> future = std::async(std::launch::async, std::move(functor));
        internals::observe_and_wait(std::move(future), timeout, has_timed_out);
    } else {
        functor();
    }
}
/**
 * @brief A test run without a test context
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
