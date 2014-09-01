#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>
using namespace unittest::assertions;

struct fixture {
    int value;
    fixture() : value(42) {}
    virtual ~fixture() noexcept(false) {}
};

struct context {
	context() {}
    virtual ~context() {}
};

struct test_macros_run : unittest::testcase<context> {

    static void run()
    {
        UNITTEST_CLASS(test_macros_run)
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
        unittest::fail(__func__, "should be skipped");
    }

    void test_unittest_run_maybe_run()
    {
        assert_true(true);
    }

    void test_unittest_run_maybe_not_run()
    {
        unittest::fail(__func__, "should be skipped");
    }

    void test_unittest_run_time()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_run_time_skip()
    {
        unittest::fail(__func__, "should be skipped");
    }

    void test_unittest_run_time_maybe_run()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_run_time_maybe_not_run()
    {
        unittest::fail(__func__, "should be skipped");
    }

    void test_unittest_runctx()
    {
        assert_true(true);
    }

    void test_unittest_runctx_skip()
    {
        unittest::fail(__func__, "should be skipped");
    }

    void test_unittest_runctx_maybe_run()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_runctx_maybe_not_run()
    {
        unittest::fail(__func__, "should be skipped");
    }

    void test_unittest_runctx_time()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_runctx_time_skip()
    {
        unittest::fail(__func__, "should be skipped");
    }

    void test_unittest_runctx_time_maybe_run()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_runctx_time_maybe_not_run()
    {
        unittest::fail(__func__, "should be skipped");
    }

};
REGISTER(test_macros_run)

COLLECTION(test_macros_other)
{

TEST(test_test)
{
    assert_equal(unittest::join("@SPOT@", __FILE__, ":", __LINE__, "@SPOT@"), SPOT);
}

UNITTEST_TEST(test_unittest_test)
{
    assert_equal(unittest::join("@SPOT@", __FILE__, ":", __LINE__, "@SPOT@"), UNITTEST_SPOT);
}

TEST_SKIP(test_test_skip, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

UNITTEST_TEST_SKIP(test_unittest_test_skip, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

TEST_MAYBE(test_test_maybe_run, true, "ok")
{
	assert_true(true);
}

UNITTEST_TEST_MAYBE(test_unittest_test_maybe_run, true, "ok")
{
	assert_true(true);
}

TEST_MAYBE(test_test_maybe_not_run, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

UNITTEST_TEST_MAYBE(test_unittest_test_maybe_not_run, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

TEST_TIME(test_test_time, 0.1)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

UNITTEST_TEST_TIME(test_unittest_test_time, 0.1)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

TEST_TIME_SKIP(test_test_time_skip, 0.1, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

UNITTEST_TEST_TIME_SKIP(test_unittest_test_time_skip, 0.1, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

TEST_TIME_MAYBE(test_test_time_maybe_run, 0.1, true, "ok")
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

UNITTEST_TEST_TIME_MAYBE(test_unittest_test_time_maybe_run, 0.1, true, "ok")
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

TEST_TIME_MAYBE(test_test_time_maybe_not_run, 0.1, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

UNITTEST_TEST_TIME_MAYBE(test_unittest_test_time_maybe_not_run, 0.1, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

TEST_FIXTURE(fixture, test_test_fixture)
{
    assert_equal(42, value);
}

UNITTEST_TEST_FIXTURE(fixture, test_unittest_test_fixture)
{
    assert_equal(42, value);
}

TEST_FIXTURE_SKIP(fixture, test_test_fixture_skip, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

UNITTEST_TEST_FIXTURE_SKIP(fixture, test_unittest_test_fixture_skip, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

TEST_FIXTURE_MAYBE(fixture, test_test_fixture_maybe_run, true, "ok")
{
    assert_equal(42, value);
}

UNITTEST_TEST_FIXTURE_MAYBE(fixture, test_unittest_test_fixture_maybe_run, true, "ok")
{
    assert_equal(42, value);
}

TEST_FIXTURE_MAYBE(fixture, test_test_fixture_maybe_not_run, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

UNITTEST_TEST_FIXTURE_MAYBE(fixture, test_unittest_test_fixture_maybe_not_run, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

TEST_FIXTURE_TIME(fixture, test_test_fixture_time, 0.1)
{
    assert_equal(42, value);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

UNITTEST_TEST_FIXTURE_TIME(fixture, test_unittest_test_fixture_time, 0.1)
{
    assert_equal(42, value);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

TEST_FIXTURE_TIME_SKIP(fixture, test_test_fixture_time_skip, 0.1, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

UNITTEST_TEST_FIXTURE_TIME_SKIP(fixture, test_unittest_test_fixture_time_skip, 0.1, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

TEST_FIXTURE_TIME_MAYBE(fixture, test_test_fixture_time_maybe_run, 0.1, true, "ok")
{
    assert_equal(42, value);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

UNITTEST_TEST_FIXTURE_TIME_MAYBE(fixture, test_unittest_test_fixture_time_maybe_run, 0.1, true, "ok")
{
    assert_equal(42, value);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

TEST_FIXTURE_TIME_MAYBE(fixture, test_test_fixture_time_maybe_not_run, 0.1, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

UNITTEST_TEST_FIXTURE_TIME_MAYBE(fixture, test_unittest_test_fixture_time_maybe_not_run, 0.1, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}

TEST_TPL(test_test_tpl)
{
    Type1 value = 1;
    assert_true(value);
}
REGISTER(test_test_tpl<long>)

UNITTEST_TEST_TPL(test_unittest_test_tpl)
{
    Type1 value1 = 1;
    Type2 value2 = 2;
    assert_greater(value2, value1);
}
UNITTEST_REGISTER(test_unittest_test_tpl<int, double>)

TEST_TPL_SKIP(test_test_tpl_skip, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_skip<long>)

UNITTEST_TEST_TPL_SKIP(test_unittest_test_tpl_skip, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_skip<int, double>)

TEST_TPL_MAYBE(test_test_tpl_maybe_run, true, "ok")
{
    Type1 value = 1;
    assert_true(value);
}
REGISTER(test_test_tpl_maybe_run<long>)

UNITTEST_TEST_TPL_MAYBE(test_unittest_test_tpl_maybe_run, true, "ok")
{
    Type1 value1 = 1;
    Type2 value2 = 2;
    assert_greater(value2, value1);
}
UNITTEST_REGISTER(test_unittest_test_tpl_maybe_run<int, double>)

TEST_TPL_MAYBE(test_test_tpl_maybe_not_run, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_maybe_not_run<long>)

UNITTEST_TEST_TPL_MAYBE(test_unittest_test_tpl_maybe_not_run, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_maybe_not_run<int, double>)

TEST_TPL_TIME(test_test_tpl_time, 0.1)
{
    Type1 value = 1;
    assert_true(value);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
REGISTER(test_test_tpl_time<long>)

UNITTEST_TEST_TPL_TIME(test_unittest_test_tpl_time, 0.1)
{
    Type1 value1 = 1;
    Type2 value2 = 2;
    assert_greater(value2, value1);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
UNITTEST_REGISTER(test_unittest_test_tpl_time<int, double>)

TEST_TPL_TIME_SKIP(test_test_tpl_time_skip, 0.1, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_time_skip<long>)

UNITTEST_TEST_TPL_TIME_SKIP(test_unittest_test_tpl_time_skip, 0.1, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_time_skip<int, double>)

TEST_TPL_TIME_MAYBE(test_test_tpl_time_maybe_run, 0.1, true, "ok")
{
    Type1 value = 1;
    assert_true(value);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
REGISTER(test_test_tpl_time_maybe_run<long>)

UNITTEST_TEST_TPL_TIME_MAYBE(test_unittest_test_tpl_time_maybe_run, 0.1, true, "ok")
{
    Type1 value1 = 1;
    Type2 value2 = 2;
    assert_greater(value2, value1);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
UNITTEST_REGISTER(test_unittest_test_tpl_time_maybe_run<int, double>)

TEST_TPL_TIME_MAYBE(test_test_tpl_time_maybe_not_run, 0.1, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_time_maybe_not_run<long>)

UNITTEST_TEST_TPL_TIME_MAYBE(test_unittest_test_tpl_time_maybe_not_run, 0.1, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_time_maybe_not_run<int, double>)

TEST_TPL_FIXTURE(fixture, test_test_tpl_fixture)
{
    Type1 value1 = 1;
    assert_true(value1);
    assert_equal(42, value);
}
REGISTER(test_test_tpl_fixture<long>)

UNITTEST_TEST_TPL_FIXTURE(fixture, test_unittest_test_tpl_fixture)
{
    Type1 value1 = 1;
    Type2 value2 = 2;
    assert_greater(value2, value1);
    assert_equal(42, value);
}
UNITTEST_REGISTER(test_unittest_test_tpl_fixture<int, double>)

TEST_TPL_FIXTURE_SKIP(fixture, test_test_tpl_fixture_skip, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_fixture_skip<long>)

UNITTEST_TEST_TPL_FIXTURE_SKIP(fixture, test_unittest_test_tpl_fixture_skip, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_fixture_skip<int, double>)

TEST_TPL_FIXTURE_MAYBE(fixture, test_test_tpl_fixture_maybe_run, true, "ok")
{
    Type1 value1 = 1;
    assert_true(value1);
    assert_equal(42, value);
}
REGISTER(test_test_tpl_fixture_maybe_run<long>)

UNITTEST_TEST_TPL_FIXTURE_MAYBE(fixture, test_unittest_test_tpl_fixture_maybe_run, true, "ok")
{
    Type1 value1 = 1;
    Type2 value2 = 2;
    assert_greater(value2, value1);
    assert_equal(42, value);
}
UNITTEST_REGISTER(test_unittest_test_tpl_fixture_maybe_run<int, double>)

TEST_TPL_FIXTURE_MAYBE(fixture, test_test_tpl_fixture_maybe_not_run, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_fixture_maybe_not_run<long>)

UNITTEST_TEST_TPL_FIXTURE_MAYBE(fixture, test_unittest_test_tpl_fixture_maybe_not_run, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_fixture_maybe_not_run<int, double>)

TEST_TPL_FIXTURE_TIME(fixture, test_test_tpl_fixture_time, 0.1)
{
    Type1 value1 = 1;
    assert_true(value1);
    assert_equal(42, value);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
REGISTER(test_test_tpl_fixture_time<long>)

UNITTEST_TEST_TPL_FIXTURE_TIME(fixture, test_unittest_test_tpl_fixture_time, 0.1)
{
    Type1 value1 = 1;
    Type2 value2 = 2;
    assert_greater(value2, value1);
    assert_equal(42, value);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
UNITTEST_REGISTER(test_unittest_test_tpl_fixture_time<int, double>)

TEST_TPL_FIXTURE_TIME_SKIP(fixture, test_test_tpl_fixture_time_skip, 0.1, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_fixture_time_skip<long>)

UNITTEST_TEST_TPL_FIXTURE_TIME_SKIP(fixture, test_unittest_test_tpl_fixture_time_skip, 0.1, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_fixture_time_skip<int, double>)

TEST_TPL_FIXTURE_TIME_MAYBE(fixture, test_test_tpl_fixture_time_maybe_run, 0.1, true, "ok")
{
    Type1 value1 = 1;
    assert_true(value1);
    assert_equal(42, value);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
REGISTER(test_test_tpl_fixture_time_maybe_run<long>)

UNITTEST_TEST_TPL_FIXTURE_TIME_MAYBE(fixture, test_unittest_test_tpl_fixture_time_maybe_run, 0.1, true, "ok")
{
    Type1 value1 = 1;
    Type2 value2 = 2;
    assert_greater(value2, value1);
    assert_equal(42, value);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
UNITTEST_REGISTER(test_unittest_test_tpl_fixture_time_maybe_run<int, double>)

TEST_TPL_FIXTURE_TIME_MAYBE(fixture, test_test_tpl_fixture_time_maybe_not_run, 0.1, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_fixture_time_maybe_not_run<long>)

UNITTEST_TEST_TPL_FIXTURE_TIME_MAYBE(fixture, test_unittest_test_tpl_fixture_time_maybe_not_run, 0.1, false, "ok")
{
    unittest::fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_fixture_time_maybe_not_run<int, double>)

}
