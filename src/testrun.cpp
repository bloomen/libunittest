#include <libunittest/testrun.hpp>
#include <libunittest/utilities.hpp>
#include <libunittest/teststatus.hpp>
#include <libunittest/testlog.hpp>
#include <chrono>
#include <iostream>
#include <typeinfo>

namespace unittest {

void
observe_and_wait(const std::future<void>& future,
                 double time_out)
{
    if (time_out>0) {
        const auto wait_ms = std::chrono::milliseconds(100);
        const double wait_sec = duration_in_seconds(wait_ms);
        double duration(wait_sec);
        while (future.wait_for(wait_ms)!=std::future_status::ready) {
            if (duration>time_out) {
                throw testfailure(join("test has timed out after ", time_out, "s"));
            }
            duration += wait_sec;
        }
    }
    future.wait();
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

} // unittest
