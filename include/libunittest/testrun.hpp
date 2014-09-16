/**
 * @brief Functionality to run tests
 * @file testrun.hpp
 */
#pragma once
#include <libunittest/testfailure.hpp>
#include <libunittest/testsuite.hpp>
#include <libunittest/utilities.hpp>
#include <string>
#include <stdexcept>
#include <thread>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace core {
/**
 * @brief The test monitor logs information about a single test
 */
class testmonitor {
public:
    /**
     * @brief Constructor
     * @param class_name The name of the test class
     * @param test_name The name of the current test method
     * @param method_id The ID of the current test method
     */
    testmonitor(const std::string& class_name,
                const std::string& test_name,
                const std::string& method_id);
    /**
     * @brief Destructor
     */
    virtual
    ~testmonitor();
    /**
     * @brief Copy constructor. Deleted
     * @param other An instance of testmonitor
     */
    testmonitor(const testmonitor& other) = delete;
    /**
     * @brief Copy assignment operator. Deleted
     * @param other An instance of testmonitor
     * @returns An testmonitor instance
     */
    testmonitor&
    operator=(const testmonitor& other) = delete;
    /**
     * @brief Move constructor. Deleted
     * @param other An instance of testmonitor
     */
    testmonitor(testmonitor&& other) = delete;
    /**
     * @brief Move assignment operator. Deleted
     * @param other An instance of testmonitor
     * @returns An testmonitor instance
     */
    testmonitor&
    operator=(testmonitor&& other) = delete;
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
     * @brief Logs skipped for the current test
     */
    void
    log_skipped(const std::string& message);
    /**
     * @brief Logs failure for the current test
     * @param e The failure exception
     */
    void
    log_failure(const unittest::testfailure& e);
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

private:
    struct impl;
    std::unique_ptr<impl> impl_;
};
/**
 * @brief Returns a unique method id
 * @param test_name The name of the test method
 * @returns A unique method id
 */
template<typename TestCase>
std::string
make_method_id(const std::string& test_name)
{
    return unittest::core::get_type_id<TestCase>() + test_name;
}
/**
 * @brief Stores the test to be run and an optional test context.
 *  By using the ()-operator the test is executed.
 */
template<typename TestCase>
struct testfunctor {
    /**
     * @brief Constructor
     * @param context A pointer to the test context
     * @param method The test to be run
     * @param method_id The id of the test method
     * @param class_name The name of the test class
     * @param test_name The name of the current test method
     * @param dry_run Whether a dry run is performed
     * @param handle_exceptions Whether to handle unexpected exceptions
     * @param has_timed_out Whether the test has timed out
     * @param timeout The test timeout
     * @param skipped Whether the current test is skipped
     * @param skip_message A message explaining why the test is skipped
     */
    testfunctor(std::shared_ptr<typename TestCase::context_type> context,
                void (TestCase::*method)(),
                const std::string& method_id,
                const std::string& class_name,
                const std::string& test_name,
                bool dry_run,
                bool handle_exceptions,
                std::shared_ptr<std::atomic_bool> has_timed_out,
                double timeout,
                bool skipped,
                std::string skip_message)
        : context_(context),
          method_(method),
          method_id_(method_id),
          class_name_(class_name),
          test_name_(test_name),
          dry_run_(dry_run),
          handle_exceptions_(handle_exceptions),
          has_timed_out_(has_timed_out),
          timeout_(timeout),
          skipped_(skipped),
          skip_message_(skip_message)
    {}
    /**
     * @brief Destructor
     */
    virtual
    ~testfunctor()
    {}
    /**
     * @brief Executes the test
     */
    void
    operator()()
    {
        unittest::core::testmonitor monitor(class_name_, test_name_, method_id_);
        if (skipped_)
            monitor.log_skipped(skip_message_);
        else if (monitor.is_executed()) {
            if (dry_run_) {
                monitor.log_success();
            } else {
                std::unique_ptr<TestCase> test;
                this->run(test, monitor);
                if (has_timed_out_->load())
                    monitor.has_timed_out(timeout_);
            }
        }
    }

private:

    void
    run(std::unique_ptr<TestCase>& test,
        unittest::core::testmonitor& monitor)
    {
        if (this->construct(test, monitor)) {
            if (this->set_up(test, monitor)) {
                if (this->execute(test, monitor)) {
                    if (this->tear_down(test, monitor)) {
                    	this->destruct(test, monitor);
                    }
                }
            }
        }
    }

    bool
    do_nothing(std::unique_ptr<TestCase>&,
               unittest::core::testmonitor&)
    {
        return true;
    }

    bool
    handle(std::unique_ptr<TestCase>& test,
           unittest::core::testmonitor& monitor,
           bool (testfunctor::*function)
                       (std::unique_ptr<TestCase>&, unittest::core::testmonitor&),
           bool (testfunctor::*error_callback)
                       (std::unique_ptr<TestCase>&, unittest::core::testmonitor&))
    {
        if (handle_exceptions_) {
            try {
                (this->*function)(test, monitor);
                monitor.log_success();
                return true;
            } catch (const unittest::testfailure& e) {
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
            } catch (const unittest::testfailure& e) {
                (this->*error_callback)(test, monitor);
                monitor.log_failure(e);
                return false;
            }
        }
    }

    bool
    construct(std::unique_ptr<TestCase>& test,
              unittest::core::testmonitor& monitor)
    {
        return handle(test, monitor,
                      &testfunctor::_construct,
                      &testfunctor::destruct);
    }

    bool
    _construct(std::unique_ptr<TestCase>& test,
               unittest::core::testmonitor&)
    {
        test = unittest::core::make_unique<TestCase>();
        test->set_test_context(context_);
        test->set_test_id(method_id_);
        return true;
    }

    bool
    set_up(std::unique_ptr<TestCase>& test,
           unittest::core::testmonitor& monitor)
    {
        return this->handle(test, monitor,
                            &testfunctor::_set_up,
                            &testfunctor::tear_down);
    }

    bool
    _set_up(std::unique_ptr<TestCase>& test,
            unittest::core::testmonitor&)
    {
        test->set_up();
        return true;
    }

    bool
    execute(std::unique_ptr<TestCase>& test,
            unittest::core::testmonitor& monitor)
    {
        return this->handle(test, monitor,
                            &testfunctor::_execute,
                            &testfunctor::tear_down);
    }

    bool
    _execute(std::unique_ptr<TestCase>& test,
             unittest::core::testmonitor&)
    {
    	(test.get()->*method_)();
        return true;
    }

    bool
    tear_down(std::unique_ptr<TestCase>& test,
              unittest::core::testmonitor& monitor)
    {
        return this->handle(test, monitor,
                            &testfunctor::_tear_down,
                            &testfunctor::destruct);
    }

    bool
    _tear_down(std::unique_ptr<TestCase>& test,
               unittest::core::testmonitor&)
    {
        test->tear_down();
        return true;
    }

    bool
    destruct(std::unique_ptr<TestCase>& test,
             unittest::core::testmonitor& monitor)
    {
        return this->handle(test, monitor,
                            &testfunctor::_destruct,
                            &testfunctor::do_nothing);
    }

    bool
    _destruct(std::unique_ptr<TestCase>& test,
              unittest::core::testmonitor&)
    {
    	delete test.release();
        return true;
    }

    std::shared_ptr<typename TestCase::context_type> context_;
    void (TestCase::*method_)();
    std::string method_id_;
    std::string class_name_;
    std::string test_name_;
    bool dry_run_;
    bool handle_exceptions_;
    std::shared_ptr<std::atomic_bool> has_timed_out_;
    double timeout_;
    bool skipped_;
    std::string skip_message_;
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
 * @brief Updates information needed or a test run
 * @param class_id The current class' type ID
 * @param class_name The current class name
 * @param test_name The current test name
 * @param local_timeout The local timeout in seconds
 */
void
update_testrun_info(const std::string& class_id,
                    std::string& class_name,
                    std::string& test_name,
                    double& local_timeout);
/**
 * @brief Observes the progress of an asynchronous operation and waits until
 *  the operation has finished or timed out
 * @param thread The asynchronous operation
 * @param done Whether the operation is finished
 * @param has_timed_out Whether the test has timed out
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @param resolution The temporal resolution
 */
void
observe_and_wait(std::thread&& thread,
                 std::shared_ptr<std::atomic_bool> done,
                 std::shared_ptr<std::atomic_bool> has_timed_out,
                 double timeout,
                 std::chrono::milliseconds resolution=std::chrono::milliseconds(10));
/**
 * @brief Prepares a test run
 * @param context The test context
 * @param method A pointer to the method to be run
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 * @param skipped Whether this test run is skipped
 * @param skip_message A message explaining why the test is skipped
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @returns A tuple of prepared data
 */
template<typename TestCase>
std::tuple<unittest::core::testfunctor<TestCase>, std::shared_ptr<std::atomic_bool>, double>
prepare_testrun(std::shared_ptr<typename TestCase::context_type> context,
                void (TestCase::*method)(),
                std::string class_name,
                std::string test_name,
                bool skipped,
                std::string skip_message,
                double timeout)
{
    const std::string class_id = unittest::core::get_type_id<TestCase>();
    const std::string method_id = unittest::core::make_method_id<TestCase>(test_name);
    unittest::core::update_testrun_info(class_id, class_name, test_name, timeout);
    const unittest::core::userargs& args = unittest::core::testsuite::instance()->get_arguments();
    std::shared_ptr<std::atomic_bool> has_timed_out = std::make_shared<std::atomic_bool>();
    has_timed_out->store(false);
    unittest::core::testfunctor<TestCase> functor(context, method, method_id,
                                                  class_name, test_name,
                                                  args.dry_run,
                                                  args.handle_exceptions,
                                                  has_timed_out, timeout,
                                                  skipped, skip_message);
    return std::make_tuple(std::move(functor), has_timed_out, timeout);
}

} // core

/**
 * @brief A test run with a test context and with timeout measurement
 * @param context The test context
 * @param method A pointer to the method to be run
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 * @param skipped Whether this test run is skipped
 * @param skip_message A message explaining why the test is skipped
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
template<typename TestCase>
void
testrun(std::shared_ptr<typename TestCase::context_type> context,
        void (TestCase::*method)(),
        std::string class_name,
        std::string test_name,
        bool skipped,
        std::string skip_message,
        double timeout)
{
    auto data = unittest::core::prepare_testrun(context, method,
                                                     class_name, test_name,
                                                     skipped, skip_message, timeout);
    if (unittest::core::testsuite::instance()->get_arguments().disable_timeout || timeout<=0) {
    	std::get<0>(data)();
    } else {
        std::shared_ptr<std::atomic_bool> done = std::make_shared<std::atomic_bool>();
        done->store(false);
        auto function = [done](unittest::core::testfunctor<TestCase> functor) { functor(); done->store(true); };
        std::thread thread(function, std::move(std::get<0>(data)));
        unittest::core::observe_and_wait(std::move(thread), done, std::get<1>(data), std::get<2>(data));
    }
}
/**
 * @brief A test run with a test context and without timeout measurement
 * @param context The test context
 * @param method A pointer to the method to be run
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 * @param skipped Whether this test run is skipped
 * @param skip_message A message explaining why the test is skipped
 */
template<typename TestCase>
void
testrun(std::shared_ptr<typename TestCase::context_type> context,
        void (TestCase::*method)(),
        std::string class_name,
        std::string test_name,
        bool skipped,
        std::string skip_message)
{
    const double timeout = -1;
    auto data = unittest::core::prepare_testrun(context, method,
												class_name, test_name,
												skipped, skip_message, timeout);
    std::get<0>(data)();
}
/**
 * @brief A test run without a test context and with timeout measurement
 * @param method A pointer to the method to be run
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @param skipped Whether this test run is skipped
 * @param skip_message A message explaining why the test is skipped
 */
template<typename TestCase>
void
testrun(void (TestCase::*method)(),
        std::string class_name,
        std::string test_name,
        bool skipped,
        std::string skip_message,
        double timeout)
{
	std::shared_ptr<typename TestCase::context_type> context(nullptr);
    unittest::testrun(context, method, class_name, test_name, skipped, skip_message, timeout);
}
/**
 * @brief A test run without a test context and without timeout measurement
 * @param method A pointer to the method to be run
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 * @param skipped Whether this test run is skipped
 * @param skip_message A message explaining why the test is skipped
 */
template<typename TestCase>
void
testrun(void (TestCase::*method)(),
        std::string class_name,
        std::string test_name,
        bool skipped,
        std::string skip_message)
{
	std::shared_ptr<typename TestCase::context_type> context(nullptr);
    unittest::testrun(context, method, class_name, test_name, skipped, skip_message);
}

} // unittest
