#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>


TEST(test_value_is_false)
{
    assert_false(false);
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
        assert_equal("here I am", message_, SPOT);
    }

    void helper(const unittest::testcase<>& obj,
                const std::string& spot)
    {
        obj.assert_true(true, spot);
    }

    TEST(test_helper_asserts_true)
    {
        helper(*this, SPOT);
    }

}
