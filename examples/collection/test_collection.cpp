#include <libunittest/all.hpp>
using namespace unittest::assertions;

TEST(test_value_is_false)
{
    int *ptr = nullptr;
    assert_false(ptr, SPOT);
}

TEST_SKIP(test_value_is_three, "to show how tests are skipped")
{
    int value = 3;
    assert_not_equal(3, value, SPOT);
}

TEST_MAYBE(test_value_not_three, false, "this is also skipped")
{
    int value = 4;
    // passing macro NDAS makes the assertion non-deadly
    assert_equal(3, value, SPOT, NDAS);
}

TEST_TIME(test_value_is_true, 2.5) // timeout of 2.5s
{
    assert_true(true, SPOT);
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
        assert_equal("here I am", message_, SPOT);
    }

    void helper(const std::string& spot)
    {
        assert_true(true, spot);
    }

    TEST(test_helper_asserts_true)
    {
        TESTINFO("some info about this test")
        helper(SPOT);
    }

}
}
