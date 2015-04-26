#include <libunittest/all.hpp>
using namespace unittest::assertions;

struct fixture {
    int value;
    fixture() : value(42) {}
    virtual ~fixture() UNITTEST_NOEXCEPT_FALSE {}
};

COLLECTION(test_macros_easy_tpl)
{

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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }
    REGISTER(test_test_tpl_skip<long>)

    UNITTEST_TEST_TPL_SKIP(test_unittest_test_tpl_skip, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }
    REGISTER(test_test_tpl_maybe_not_run<long>)

    UNITTEST_TEST_TPL_MAYBE(test_unittest_test_tpl_maybe_not_run, false, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }
    REGISTER(test_test_tpl_time_skip<long>)

    UNITTEST_TEST_TPL_TIME_SKIP(test_unittest_test_tpl_time_skip, 0.1, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }
    REGISTER(test_test_tpl_time_maybe_not_run<long>)

    UNITTEST_TEST_TPL_TIME_MAYBE(test_unittest_test_tpl_time_maybe_not_run, 0.1, false, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }
    REGISTER(test_test_tpl_fixture_skip<long>)

    UNITTEST_TEST_TPL_FIXTURE_SKIP(fixture, test_unittest_test_tpl_fixture_skip, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }
    REGISTER(test_test_tpl_fixture_maybe_not_run<long>)

    UNITTEST_TEST_TPL_FIXTURE_MAYBE(fixture, test_unittest_test_tpl_fixture_maybe_not_run, false, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }
    REGISTER(test_test_tpl_fixture_time_skip<long>)

    UNITTEST_TEST_TPL_FIXTURE_TIME_SKIP(fixture, test_unittest_test_tpl_fixture_time_skip, 0.1, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }
    REGISTER(test_test_tpl_fixture_time_maybe_not_run<long>)

    UNITTEST_TEST_TPL_FIXTURE_TIME_MAYBE(fixture, test_unittest_test_tpl_fixture_time_maybe_not_run, 0.1, false, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }
    UNITTEST_REGISTER(test_unittest_test_tpl_fixture_time_maybe_not_run<int, double>)

}
