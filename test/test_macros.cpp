#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>

struct fixture {
    int value;
    fixture() : value(42) {}
};

struct test_macros_run : unittest::testcase<unittest::sometype> {

    static void run()
    {
        UNITTEST_CLASS(test_macros_run)
        UNITTEST_RUN(test_unittest_run)
        UNITTEST_RUN_SKIP(test_unittest_run_skip, "ok")
        UNITTEST_RUN_TIME(test_unittest_run_time, 0.1)
        UNITTEST_RUN_TIME_SKIP(test_unittest_run_time_skip, 0.1, "ok")
        unittest::sometype cxt;
        UNITTEST_RUNCXT(cxt, test_unittest_runcxt)
        UNITTEST_RUNCXT_SKIP(cxt, test_unittest_runcxt_skip, "ok")
        UNITTEST_RUNCXT_TIME(cxt, test_unittest_runcxt_time, 0.1)
        UNITTEST_RUNCXT_TIME_SKIP(cxt, test_unittest_runcxt_time_skip, 0.1, "ok")
    }

    void test_unittest_run()
    {
        assert_true(true);
    }

    void test_unittest_run_skip()
    {
        fail(__func__, "should be skipped");
    }

    void test_unittest_run_time()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_run_time_skip()
    {
        fail(__func__, "should be skipped");
    }

    void test_unittest_runcxt()
    {
        assert_true(true);
    }

    void test_unittest_runcxt_skip()
    {
        fail(__func__, "should be skipped");
    }

    void test_unittest_runcxt_time()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    void test_unittest_runcxt_time_skip()
    {
        fail(__func__, "should be skipped");
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
    fail(__func__, "should be skipped");
}

UNITTEST_TEST_SKIP(test_unittest_test_skip, "ok")
{
    fail(__func__, "should be skipped");
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
    fail(__func__, "should be skipped");
}

UNITTEST_TEST_TIME_SKIP(test_unittest_test_time_skip, 0.1, "ok")
{
    fail(__func__, "should be skipped");
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
    fail(__func__, "should be skipped");
}

UNITTEST_TEST_FIXTURE_SKIP(fixture, test_unittest_test_fixture_skip, "ok")
{
    fail(__func__, "should be skipped");
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
    fail(__func__, "should be skipped");
}

UNITTEST_TEST_FIXTURE_TIME_SKIP(fixture, test_unittest_test_fixture_time_skip, 0.1, "ok")
{
    fail(__func__, "should be skipped");
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
    fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_skip<long>)

UNITTEST_TEST_TPL_SKIP(test_unittest_test_tpl_skip, "ok")
{
    fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_skip<int, double>)

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
    fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_time_skip<long>)

UNITTEST_TEST_TPL_TIME_SKIP(test_unittest_test_tpl_time_skip, 0.1, "ok")
{
    fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_time_skip<int, double>)

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
    fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_fixture_skip<long>)

UNITTEST_TEST_TPL_FIXTURE_SKIP(fixture, test_unittest_test_tpl_fixture_skip, "ok")
{
    fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_fixture_skip<int, double>)

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
    fail(__func__, "should be skipped");
}
REGISTER(test_test_tpl_fixture_time_skip<long>)

UNITTEST_TEST_TPL_FIXTURE_TIME_SKIP(fixture, test_unittest_test_tpl_fixture_time_skip, 0.1, "ok")
{
    fail(__func__, "should be skipped");
}
UNITTEST_REGISTER(test_unittest_test_tpl_fixture_time_skip<int, double>)

}
