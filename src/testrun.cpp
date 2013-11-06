#include <libunittest/testrun.hpp>
#include <libunittest/utilities.hpp>
#include <libunittest/teststatus.hpp>
#include <libunittest/testlog.hpp>
#include <libunittest/testcollection.hpp>
#include <chrono>
#include <iostream>
#include <typeinfo>

namespace unittest {
namespace internals {

void
observe_and_wait(std::future<void>&& future,
                 double timeout_sec,
                 std::atomic<bool>& has_timed_out,
                 int resolution_ms)
{
    if (timeout_sec > 0) {
        std::chrono::milliseconds wait_ms(resolution_ms);
        const double wait_sec = duration_in_seconds(wait_ms);
        double duration(wait_sec);
        while (future.wait_for(wait_ms)!=std::future_status::ready) {
            if (duration > timeout_sec) {
                has_timed_out = true;
                auto suite = testsuite::instance();
                std::string message("T");
                if (suite->get_arguments().verbose())
                    message = "TIMEOUT\n";
                std::cout << message << std::flush;
                suite->add_lonely_future(std::move(future));
                break;
            }
            duration += wait_sec;
        }
    } else {
        future.wait();
    }
}

template<>
struct implementation<testrunner> {

    testlog log_;
    std::chrono::high_resolution_clock::time_point start_;
    bool is_executed_;

    implementation()
    	: start_(std::chrono::high_resolution_clock::time_point::min()),
    	  is_executed_(true)
    {}

};

testrunner::testrunner(const std::string& class_name,
                       const std::string& test_name)
    : pimplpattern(new implementation<testrunner>())
{
    auto suite = testsuite::instance();
    impl_->is_executed_ = suite->is_test_run(class_name, test_name);
    if (impl_->is_executed_) {
        suite->start_timing();
        impl_->start_ = std::chrono::high_resolution_clock::now();
        impl_->log_.class_name = class_name;
        impl_->log_.test_name = test_name;
        write_test_start_message(std::cout, impl_->log_, suite->get_arguments().verbose());
    }
}

testrunner::~testrunner()
{
    auto suite = testsuite::instance();
    if (impl_->is_executed_) {
        write_test_end_message(std::cout, impl_->log_, suite->get_arguments().verbose());
        impl_->log_.successful = impl_->log_.status==teststatus::success;
        suite->make_keep_running(impl_->log_);
        const auto end = std::chrono::high_resolution_clock::now();
        suite->stop_timing();
        impl_->log_.duration = duration_in_seconds(end - impl_->start_);
    }
    suite->collect(impl_->log_);
}

bool
testrunner::is_executed()
{
    return impl_->is_executed_;
}

void
testrunner::log_success()
{
    impl_->log_.status = teststatus::success;
    impl_->log_.message = "ok";
    impl_->log_.error_type = "";
}

void
testrunner::log_failure(const testfailure& e)
{
    impl_->log_.status = teststatus::failure;
    impl_->log_.message = e.what();
    impl_->log_.error_type = "testfailure";
}

void
testrunner::log_error(const std::exception& e)
{
    impl_->log_.status = teststatus::error;
    impl_->log_.message = e.what();
    impl_->log_.error_type = typeid(e).name();
}
void
testrunner::log_unknown_error()
{
    impl_->log_.status = teststatus::error;
    impl_->log_.message = "Unknown message";
    impl_->log_.error_type = "Unknown exception";
}

void
testrunner::has_timed_out(double timeout)
{
    impl_->log_.has_timed_out = true;
    impl_->log_.timeout = timeout;
}

void
update_local_timeout(double& local_timeout)
{
    if (!(local_timeout > 0))
        local_timeout = testsuite::instance()->get_arguments().timeout();
}

void
update_class_name(std::string& class_name,
                  const std::string& typeid_name,
                  const std::map<std::string, std::string>& class_maps)
{
    if (class_name=="") {
        class_name = get_from_map(class_maps, typeid_name);
    } else if (class_name==testcollection::inactive_name()) {
        class_name = "";
    }
}

void
update_test_name(std::string& test_name,
                 const std::string& typeid_name,
                 const std::map<std::string, std::string>& class_maps)
{
    if (test_name=="") {
        test_name = get_from_map(class_maps, typeid_name);
    }
}

} // internals
} // unittest
