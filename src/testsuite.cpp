#include <libunittest/testsuite.hpp>
#include <libunittest/teststatus.hpp>
#include <libunittest/utilities.hpp>
#include <mutex>
#include <memory>

unittest::testsuite*
unittest::testsuite::instance()
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

unittest::testsuite::testsuite()
    : keep_running_(true), verbose_(false), failure_stop_(false),
      n_tests_(0), n_successes_(0), n_failures_(0),
      n_errors_(0), n_skipped_(0), testlogs_(0), name_filter_(""),
      start_(std::chrono::high_resolution_clock::time_point::min()),
      end_(std::chrono::high_resolution_clock::time_point::min())
{}

void
unittest::testsuite::set_verbose(bool verbose)
{
    static std::mutex set_verbose_mutex_;
    std::lock_guard<std::mutex> lock(set_verbose_mutex_);
    verbose_ = verbose;
}

void
unittest::testsuite::set_failure_stop(bool failure_stop)
{
    static std::mutex set_failure_stop_mutex_;
    std::lock_guard<std::mutex> lock(set_failure_stop_mutex_);
    failure_stop_ = failure_stop;
}

void
unittest::testsuite::set_name_filter(const std::string& name_filter)
{
    static std::mutex set_name_filter_mutex_;
    std::lock_guard<std::mutex> lock(set_name_filter_mutex_);
    name_filter_ = name_filter;
}

void
unittest::testsuite::set_test_name(const std::string& test_name)
{
    static std::mutex set_test_name_mutex_;
    std::lock_guard<std::mutex> lock(set_test_name_mutex_);
    test_name_ = test_name;
}

void
unittest::testsuite::start_timing()
{
    static std::mutex start_timing_mutex_;
    std::lock_guard<std::mutex> lock(start_timing_mutex_);
    if (start_==std::chrono::high_resolution_clock::time_point::min())
        start_ = std::chrono::high_resolution_clock::now();
}

void
unittest::testsuite::stop_timing()
{
    static std::mutex stop_timing_mutex_;
    std::lock_guard<std::mutex> lock(stop_timing_mutex_);
    end_ = std::chrono::high_resolution_clock::now();
}

double
unittest::testsuite::get_duration() const
{
    return duration_in_seconds(end_ - start_);
}

unittest::testresults
unittest::testsuite::get_results() const
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
    return std::move(results);
}

bool
unittest::testsuite::get_keep_running() const
{
    return keep_running_;
}

void
unittest::testsuite::set_keep_running(bool keep_running)
{
    static std::mutex set_keep_running_mutex_;
    std::lock_guard<std::mutex> lock(set_keep_running_mutex_);
    keep_running_ = keep_running;
}

bool
unittest::testsuite::is_test_run(const std::string& class_name,
                                 const std::string& test_name) const
{
    const std::string full_name = class_name + "." + test_name;
    return is_test_executed(full_name, test_name_, name_filter_);
}

void
unittest::testsuite::collect(const testlog& log)
{
    static std::mutex collect_mutex_;
    std::lock_guard<std::mutex> lock(collect_mutex_);
    switch (log.status) {
    case teststatus::success: ++n_successes_; break;
    case teststatus::failure: ++n_failures_; break;
    case teststatus::error: ++n_errors_; break;
    case teststatus::skipped: ++n_skipped_; break;
    }
    if (log.status!=teststatus::skipped) {
        ++n_tests_;
        testlogs_.push_back(std::move(log));
    }
}
