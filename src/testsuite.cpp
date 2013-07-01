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

    bool verbose_;
    bool keep_running_;
    bool failure_stop_;
    long n_tests_;
    long n_successes_;
    long n_failures_;
    long n_errors_;
    long n_skipped_;
    std::vector<testlog> testlogs_;
    std::string name_filter_;
    std::string test_name_;
    std::chrono::high_resolution_clock::time_point start_;
    std::chrono::high_resolution_clock::time_point end_;

    implementation()
    	: verbose_(false), keep_running_(true), failure_stop_(false),
    	  n_tests_(0), n_successes_(0), n_failures_(0),
    	  n_errors_(0), n_skipped_(0), testlogs_(0), name_filter_(""),
    	  start_(std::chrono::high_resolution_clock::time_point::min()),
    	  end_(std::chrono::high_resolution_clock::time_point::min())
    {}

    double
    get_duration() const
    {
        return duration_in_seconds(end_ - start_);
    }

    void
    set_keep_running(bool keep_running)
    {
        static std::mutex set_keep_running_mutex_;
        std::lock_guard<std::mutex> lock(set_keep_running_mutex_);
        keep_running_ = keep_running;
    }

    bool
    get_keep_running() const
    {
        return keep_running_;
    }

    testresults
    get_results() const
    {
        testresults results;
        results.successful = n_tests_==n_successes_;
        results.n_tests = n_tests_;
        results.n_successes = n_successes_;
        results.n_failures = n_failures_;
        results.n_errors = n_errors_;
        results.n_skipped = n_skipped_;
        results.duration = get_duration();
        results.testlogs = testlogs_;
        return results;
    }

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
testsuite::set_verbose(bool verbose)
{
    static std::mutex set_verbose_mutex_;
    std::lock_guard<std::mutex> lock(set_verbose_mutex_);
    impl_->verbose_ = verbose;
}

void
testsuite::set_failure_stop(bool failure_stop)
{
    static std::mutex set_failure_stop_mutex_;
    std::lock_guard<std::mutex> lock(set_failure_stop_mutex_);
    impl_->failure_stop_ = failure_stop;
}

void
testsuite::set_name_filter(const std::string& name_filter)
{
    static std::mutex set_name_filter_mutex_;
    std::lock_guard<std::mutex> lock(set_name_filter_mutex_);
    impl_->name_filter_ = name_filter;
}

void
testsuite::set_test_name(const std::string& test_name)
{
    static std::mutex set_test_name_mutex_;
    std::lock_guard<std::mutex> lock(set_test_name_mutex_);
    impl_->test_name_ = test_name;
}

testresults
testsuite::get_results() const
{
    return impl_->get_results();
}

void
testsuite::make_keep_running(const testlog& log)
{
    static std::mutex make_keep_running_mutex_;
    std::lock_guard<std::mutex> lock(make_keep_running_mutex_);
    if (!log.successful && impl_->failure_stop_)
        impl_->set_keep_running(false);
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
    case teststatus::success: ++impl_->n_successes_; break;
    case teststatus::failure: ++impl_->n_failures_;  break;
    case teststatus::error: ++impl_->n_errors_;      break;
    default: ++impl_->n_skipped_;                    break;
    }
    if (log.status!=teststatus::skipped) {
        ++impl_->n_tests_;
        impl_->testlogs_.push_back(std::move(log));
    }
}

bool
testsuite::is_test_run(const std::string& class_name,
                       const std::string& test_name) const
{
    if (!impl_->get_keep_running()) {
    	return false;
    } else {
    	const std::string full_name = make_full_test_name(class_name, test_name);
    	return is_test_executed(full_name, impl_->test_name_, impl_->name_filter_);
    }
}

bool
testsuite::is_verbose() const
{
    return impl_->verbose_;
}

} // unittest
