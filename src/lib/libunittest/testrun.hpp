/**
 * @brief Functionality to run tests
 * @file testrun.hpp
 */
#pragma once
#include "testfailure.hpp"
#include "testsuite.hpp"
#include "utilities.hpp"
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
 * @param class_id The id of the test class
 * @param test_name The name of the test method
 * @returns A unique method id
 */
std::string
make_method_id(const std::string& class_id, const std::string& test_name);
/**
 * @brief The test info
 */
struct testinfo {
	/**
	 * @brief The id of the test method
	 */
    const std::string method_id;
	/**
	 * @brief The name of the test class
	 */
    const std::string class_name;
	/**
	 * @brief The name of the current test method
	 */
    const std::string test_name;
	/**
	 * @brief Whether a dry run is performed
	 */
    const bool dry_run;
	/**
	 * @brief Whether to handle unexpected exceptions
	 */
    const bool handle_exceptions;
	/**
	 * @brief Whether the test is done
	 */
	std::shared_ptr<std::atomic_bool> done;
	/**
	 * @brief @brief Whether the test has timed out
	 */
    std::shared_ptr<std::atomic_bool> has_timed_out;
	/**
	 * The test timeout
	 */
    const double timeout;
	/**
	 * @brief Whether the current test is skipped
	 */
    const bool skipped;
	/**
	 * @brief A message explaining why the test is skipped
	 */
    const std::string skip_message;
};
/**
 * @brief Runs the given test function and logs using the monitor
 * @param info The test info
 * @param monitor The test monitor
 * @param function The test function
 */
void run_testfunction(const unittest::core::testinfo& info,
					  unittest::core::testmonitor& monitor,
					  std::function<void()> function);
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
     * @param info The test info
     */
    testfunctor(std::shared_ptr<typename TestCase::context_type> context,
                void (TestCase::*method)(),
				unittest::core::testinfo info)
        : context_(context),
          method_(method),
          info_(std::move(info))
    {}
    /**
     * @brief Destructor
     */
    virtual
    ~testfunctor()
    {}
    /**
     * @brief Returns the test info
     * @returns The test info
     */
    const unittest::core::testinfo&
	info() const
    {
    	return info_;
    }
    /**
     * @brief Executes the test
     */
    void
    operator()()
    {
        unittest::core::testmonitor monitor(info_.class_name, info_.test_name, info_.method_id);
        run_testfunction(info_, monitor, [this, &monitor](){
            TestCase* test = nullptr;
            this->run(test, monitor);
        });
    }

private:

    void
    run(TestCase*& test,
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
    do_nothing(TestCase*&,
               unittest::core::testmonitor&)
    {
        return true;
    }

    bool
    handle(TestCase*& test,
           unittest::core::testmonitor& monitor,
           bool (testfunctor::*function)(TestCase*&, unittest::core::testmonitor&),
           bool (testfunctor::*error_callback)(TestCase*&, unittest::core::testmonitor&))
    {
        if (info_.handle_exceptions) {
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
    construct(TestCase*& test,
              unittest::core::testmonitor& monitor)
    {
        return handle(test, monitor,
                      &testfunctor::_construct,
                      &testfunctor::destruct);
    }

    bool
    _construct(TestCase*& test,
               unittest::core::testmonitor&)
    {
        test = new TestCase;
        test->set_test_context(context_);
        test->set_test_id(info_.method_id);
        return true;
    }

    bool
    set_up(TestCase*& test,
           unittest::core::testmonitor& monitor)
    {
        return this->handle(test, monitor,
                            &testfunctor::_set_up,
                            &testfunctor::tear_down);
    }

    bool
    _set_up(TestCase*& test,
            unittest::core::testmonitor&)
    {
        test->set_up();
        return true;
    }

    bool
    execute(TestCase*& test,
            unittest::core::testmonitor& monitor)
    {
        return this->handle(test, monitor,
                            &testfunctor::_execute,
                            &testfunctor::tear_down);
    }

    bool
    _execute(TestCase*& test,
             unittest::core::testmonitor&)
    {
    	(test->*method_)();
        return true;
    }

    bool
    tear_down(TestCase*& test,
              unittest::core::testmonitor& monitor)
    {
        return this->handle(test, monitor,
                            &testfunctor::_tear_down,
                            &testfunctor::destruct);
    }

    bool
    _tear_down(TestCase*& test,
               unittest::core::testmonitor&)
    {
        test->tear_down();
        return true;
    }

    bool
    destruct(TestCase*& test,
             unittest::core::testmonitor& monitor)
    {
        return this->handle(test, monitor,
                            &testfunctor::_destruct,
                            &testfunctor::do_nothing);
    }

    bool
    _destruct(TestCase*& test,
              unittest::core::testmonitor&)
    {
    	delete test;
        return true;
    }

    std::shared_ptr<typename TestCase::context_type> context_;
    void (TestCase::*method_)();
    const unittest::core::testinfo info_;
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
 */
void
observe_and_wait(std::thread&& thread,
                 std::shared_ptr<std::atomic_bool> done,
                 std::shared_ptr<std::atomic_bool> has_timed_out,
                 double timeout);
/**
 * @brief Creates the test info object
 * @param class_id The id of the test class
 * @param class_name The name of the test class
 * @param test_name The name of the current test method
 * @param skipped Whether this test run is skipped
 * @param skip_message A message explaining why the test is skipped
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @returns The test info object
 */
unittest::core::testinfo
make_testinfo(std::string class_id,
			  std::string class_name,
			  std::string test_name,
			  bool skipped,
			  std::string skip_message,
			  double timeout);

} // core

/**
 * @brief A test run with a test context and with timeout measurement
 * @param context The test context, can be a nullptr
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
    unittest::core::testfunctor<TestCase> functor(context, method,
    		unittest::core::make_testinfo(unittest::core::get_type_id<TestCase>(),
										  class_name, test_name, skipped, skip_message, timeout));
	const double updated_timeout = functor.info().timeout;
    if (updated_timeout > 0) {
    	std::shared_ptr<std::atomic_bool> done = functor.info().done;
    	std::shared_ptr<std::atomic_bool> has_timed_out = functor.info().has_timed_out;
    	std::thread thread(functor);
        unittest::core::observe_and_wait(std::move(thread), done, has_timed_out, updated_timeout);
    } else {
    	functor();
    }
}
/**
 * @brief A test run with a test context and without timeout measurement
 * @param context The test context, can be a nullptr
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
    unittest::testrun(context, method, class_name, test_name, skipped, skip_message, -1.);
}

} // unittest
