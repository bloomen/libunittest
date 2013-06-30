#include <libunittest/testrun.hpp>
#include <libunittest/utilities.hpp>
#include <libunittest/testsuite.hpp>
#include <chrono>
#include <iostream>

namespace unittest {

template<>
struct implementation<testrunner> {

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
        log_.class_name = class_name;
        log_.test_name = test_name;
        write_test_start_message(std::cout, log_, suite->is_verbose());
    }
}

testrunner::~testrunner()
{
    auto suite = testsuite::instance();
    if (impl_->is_executed_) {
        write_test_end_message(std::cout, log_, suite->is_verbose());
        log_.successful = log_.status==teststatus::success;
        suite->make_keep_running(log_);
        const auto end = std::chrono::high_resolution_clock::now();
        suite->stop_timing();
        log_.duration = duration_in_seconds(end - impl_->start_);
    }
    suite->collect(log_);
}

bool
testrunner::is_executed()
{
    return impl_->is_executed_;
}

} // unittest
