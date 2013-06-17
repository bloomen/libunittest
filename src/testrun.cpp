#include <libunittest/testrun.hpp>
#include <libunittest/utilities.hpp>

unittest::testrunner::testrunner(const std::string& class_name,
                                 const std::string& test_name)
    : suite_(testsuite::instance()),
      is_run_(true)
{
    if (!suite_->get_keep_running())
        is_run_ = false;
    else if (!suite_->is_test_run(class_name, test_name))
        is_run_ = false;

    if (is_run_) {
        suite_->start_timing();
        start_ = std::chrono::high_resolution_clock::now();
        log_.class_name = class_name;
        log_.test_name = test_name;
        write_test_start_message(std::cout, log_, suite_->verbose_);
    }
}

unittest::testrunner::~testrunner()
{
    if (is_run_) {
        log_.successful = log_.status==teststatus::success;
        if (!log_.successful && suite_->failure_stop_)
            suite_->set_keep_running(false);
        const auto end = std::chrono::high_resolution_clock::now();
        suite_->stop_timing();
        log_.duration = duration_in_seconds(end - start_);
    }
    suite_->collect(log_);
}

bool
unittest::testrunner::is_executed()
{
    return is_run_;
}
