#include <libunittest/all.hpp>

TEST(test_value_is_false)
{
    int *ptr = nullptr;
    ASSERT_FALSE(ptr)
}

TEST_SKIP(test_value_is_three, "to show how tests are skipped")
{
    int value = 3;
    ASSERT_NOT_EQUAL(3, value)
}

TEST_MAYBE(test_value_not_three, false, "this is also skipped")
{
    int value = 4;
    NDASSERT_EQUAL(3, value) // a non-deadly assertion
}

TEST_TIME(test_value_is_true, 2.5) // timeout of 2.5s
{
    ASSERT_TRUE(true)
}

struct fixture {
    std::string message_;
    fixture()
        : message_("here I am")
    {}
    virtual ~fixture() UNITTEST_NOEXCEPT_FALSE
    {}
};


COLLECTION(test_stuff)
{
COLLECTION(test_more_stuff) // collection macros can be nested
{

    TEST_FIXTURE(fixture, test_fixture_is_correct)
    {
        TESTINFO("helpful info about this test")
        ASSERT_EQUAL("here I am", message_)
    }

    TEST(test_helper_asserts_true)
    {
        TESTINFO("some info about this test")
        ASSERT_TRUE(true)
    }

}
}
