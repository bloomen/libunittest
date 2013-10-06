#include <libunittest/testsuite.hpp>
#include <libunittest/teststatus.hpp>
#include <libunittest/utilities.hpp>
#include <mutex>
#include <memory>
#include <chrono>
#include <vector>

namespace unittest {

template<>
struct implementation<testsuite> {

    bool keep_running_;
    std::chrono::high_resolution_clock::time_point start_;
    std::chrono::high_resolution_clock::time_point end_;
    userargs arguments_;
    testresults results_;
    std::vector<std::function<void()>> test_runs_;

    implementation()
    	: keep_running_(true),
    	  start_(std::chrono::high_resolution_clock::time_point::min()),
    	  end_(std::chrono::high_resolution_clock::time_point::min())
    {}

};

testsuite*
testsuite::instance()
{
    static std::unique_ptr<testsuite> instance_ = nullptr;
    if (instance_==nullptr) {
        static std::mutex instance_mutex_;
        std::lock_guard<std::mutex> lock(instance_mutex_);
        if (instance_==nullptr)
            instance_.reset(new testsuite());
    }
    return instance_.get();
}

testsuite::testsuite()
    : pimplpattern(new implementation<testsuite>())
{}

void
testsuite::set_arguments(const userargs& arguments)
{
    static std::mutex set_arguments_mutex_;
    std::lock_guard<std::mutex> lock(set_arguments_mutex_);
    impl_->arguments_ = arguments;
}

userargs&
testsuite::get_arguments() const
{
    return impl_->arguments_;
}

std::vector<std::function<void()>>&
testsuite::get_test_runs() const
{
    return impl_->test_runs_;
}

testresults
testsuite::get_results() const
{
    testresults results(impl_->results_);
    results.successful = results.n_tests==results.n_successes;
    results.duration = duration_in_seconds(impl_->end_ - impl_->start_);
    return results;
}

void
testsuite::make_keep_running(const testlog& log)
{
    static std::mutex make_keep_running_mutex_;
    std::lock_guard<std::mutex> lock(make_keep_running_mutex_);
    if (!log.successful && get_arguments().failure_stop())
        impl_->keep_running_ = false;
}

void
testsuite::start_timing()
{
    static std::mutex start_timing_mutex_;
    std::lock_guard<std::mutex> lock(start_timing_mutex_);
    if (impl_->start_==std::chrono::high_resolution_clock::time_point::min())
        impl_->start_ = std::chrono::high_resolution_clock::now();
}

void
testsuite::stop_timing()
{
    static std::mutex stop_timing_mutex_;
    std::lock_guard<std::mutex> lock(stop_timing_mutex_);
    impl_->end_ = std::chrono::high_resolution_clock::now();
}

void
testsuite::collect(const testlog& log)
{
    static std::mutex collect_mutex_;
    std::lock_guard<std::mutex> lock(collect_mutex_);
    switch (log.status) {
    case teststatus::success: ++impl_->results_.n_successes; break;
    case teststatus::failure: ++impl_->results_.n_failures;  break;
    case teststatus::error: ++impl_->results_.n_errors;      break;
    default: ++impl_->results_.n_skipped;                    break;
    }
    if (log.status!=teststatus::skipped) {
        ++impl_->results_.n_tests;
        impl_->results_.testlogs.push_back(std::move(log));
    }
}

bool
testsuite::is_test_run(const std::string& class_name,
                       const std::string& test_name) const
{
    if (!impl_->keep_running_) {
    	return false;
    } else {
    	const std::string full_name = make_full_test_name(class_name, test_name);
    	return is_test_executed(full_name, get_arguments().test_name(), get_arguments().name_filter());
    }
}

void
testsuite::add_test_run(const std::function<void()>& test_run) {
    impl_->test_runs_.push_back(test_run);
}

} // unittest
