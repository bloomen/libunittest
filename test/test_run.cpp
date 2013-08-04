#include "test_run.h"
#define SPOT UNITTEST_SPOT

void test_run::test_observe_and_wait_no_timeout()
{
    std::function<void()> functor = []() { int a = 2; a += 1; std::this_thread::sleep_for(std::chrono::milliseconds(50)); };
    obswait obswait_functor(&functor, false);
    std::future<void> future = std::async(std::launch::deferred, obswait_functor);
    unittest::observe_and_wait(future, 0.3, 10);
}

void test_run::test_observe_and_wait_with_timeout()
{
    std::function<void()> functor = []() { std::this_thread::sleep_for(std::chrono::milliseconds(50)); };
    obswait obswait_functor(&functor, true);
    std::future<void> future = std::async(std::launch::deferred, obswait_functor);
    unittest::observe_and_wait(future, 0.7, 10);
}
