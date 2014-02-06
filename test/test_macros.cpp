#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>

COLLECTION(test_macros)
{

TEST(test_spot)
{
    assert_equal(unittest::join(" @", __FILE__, ":", __LINE__, ". "), SPOT);
}

UNITTEST_TEST(test_unittest_spot)
{
    assert_equal(unittest::join(" @", __FILE__, ":", __LINE__, ". "), UNITTEST_SPOT);
}

TEST_SKIP(test_test_skip, "ok")
{
    assert_true(false, "should be skipped");
}

UNITTEST_TEST_SKIP(test_unittest_test_skip, "ok")
{
    assert_true(false, "should be skipped");
}

TEST_TIME(test_test_time, 0.1)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}


}
