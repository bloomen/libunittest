#include <libunittest/all.hpp>
using namespace unittest::assertions;

struct context {
    context() {}
    virtual ~context() {}
};

struct test_macros_explicit : unittest::testcase<context> {

    static void run()
    {
        UNITTEST_CLASS(test_macros_explicit)
        UNITTEST_RUN(test_unittest_run)
        UNITTEST_RUN_SKIP(test_unittest_run_skip, "ok")
        UNITTEST_RUN_MAYBE(test_unittest_run_maybe_run, true, "ok")
        UNITTEST_RUN_MAYBE(test_unittest_run_maybe_not_run, false, "ok")
        UNITTEST_RUN_TIME(test_unittest_run_time, 0.1)
        UNITTEST_RUN_TIME_SKIP(test_unittest_run_time_skip, 0.1, "ok")
        UNITTEST_RUN_TIME_MAYBE(test_unittest_run_time_maybe_run, 0.1, true, "ok")
        UNITTEST_RUN_TIME_MAYBE(test_unittest_run_time_maybe_not_run, 0.1, false, "ok")
        auto ctx = std::make_shared<context>();
        UNITTEST_RUNCTX(ctx, test_unittest_runctx)
        UNITTEST_RUNCTX_SKIP(ctx, test_unittest_runctx_skip, "ok")
        UNITTEST_RUNCTX_MAYBE(ctx, test_unittest_runctx_maybe_run, true, "ok")
        UNITTEST_RUNCTX_MAYBE(ctx, test_unittest_runctx_maybe_not_run, false, "ok")
        UNITTEST_RUNCTX_TIME(ctx, test_unittest_runctx_time, 0.1)
        UNITTEST_RUNCTX_TIME_SKIP(ctx, test_unittest_runctx_time_skip, 0.1, "ok")
        UNITTEST_RUNCTX_TIME_MAYBE(ctx, test_unittest_runctx_time_maybe_run, 0.1, true, "ok")
        UNITTEST_RUNCTX_TIME_MAYBE(ctx, test_unittest_runctx_time_maybe_not_run, 0.1, false, "ok")
    }

    void test_unittest_run()
    {
        assert_true(true);
    }

    void test_unittest_run_skip()
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    void test_unittest_run_maybe_run()
    {
        assert_true(true);
    }

    void test_unittest_run_maybe_not_run()
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    void test_unittest_run_time()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_run_time_skip()
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    void test_unittest_run_time_maybe_run()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_run_time_maybe_not_run()
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    void test_unittest_runctx()
    {
        assert_true(true);
    }

    void test_unittest_runctx_skip()
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    void test_unittest_runctx_maybe_run()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_runctx_maybe_not_run()
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    void test_unittest_runctx_time()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_runctx_time_skip()
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    void test_unittest_runctx_time_maybe_run()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_runctx_time_maybe_not_run()
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

};

REGISTER(test_macros_explicit)
