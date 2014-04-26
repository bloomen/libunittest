#include <libunittest/all.hpp>

TEST(test_value_is_false)
{
    int *ptr = nullptr;
    assert_false(ptr);
}

TEST_SKIP(test_value_is_three, "to show how tests are skipped")
{
    int value = 3;
    assert_equal(3, value);
}

TEST_TIME(test_value_is_true, 2.5) // timeout of 2.5s
{
    assert_true(true);
}

struct fixture {
    std::string message_;
    fixture()
        : message_("here I am")
    {}
    ~fixture()
    {}
};

COLLECTION(test_stuff)
{

    TEST_FIXTURE(fixture, test_fixture_is_correct)
    {
        TESTINFO("helpful info about this test")
        assert_equal("here I am", message_, SPOT);
    }

    void helper(const std::string& spot)
    {
        unittest::assert.assert_true(true, spot);
    }

    TEST(test_helper_asserts_true)
    {
        TESTINFO("some info about this test")
        helper(SPOT);
    }

}
