#include <libunittest/all.hpp>
using namespace unittest::assertions;

struct fixture {
    int value;
    fixture() : value(42) {}
    virtual ~fixture() UNITTEST_NOEXCEPT_FALSE {}
};

COLLECTION(test_macros_easy)
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    UNITTEST_TEST_SKIP(test_unittest_test_skip, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    UNITTEST_TEST_MAYBE(test_unittest_test_maybe_not_run, false, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    UNITTEST_TEST_TIME_SKIP(test_unittest_test_time_skip, 0.1, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    UNITTEST_TEST_TIME_MAYBE(test_unittest_test_time_maybe_not_run, 0.1, false, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    UNITTEST_TEST_FIXTURE_SKIP(fixture, test_unittest_test_fixture_skip, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    UNITTEST_TEST_FIXTURE_MAYBE(fixture, test_unittest_test_fixture_maybe_not_run, false, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    UNITTEST_TEST_FIXTURE_TIME_SKIP(fixture, test_unittest_test_fixture_time_skip, 0.1, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
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
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

    UNITTEST_TEST_FIXTURE_TIME_MAYBE(fixture, test_unittest_test_fixture_time_maybe_not_run, 0.1, false, "ok")
    {
        unittest::fail(UNITTEST_FUNC, "should be skipped");
    }

}
