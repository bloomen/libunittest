#include <libunittest/all.hpp>

COLLECTION(templates_easy)
{

TEST_TPL(test_sum)
{
    Type1 a = 2;
    Type2 b = 3; // you can use up to 3 template types: Type1, Type2, Type3
    ASSERT_EQUAL(5, a + b)
}
REGISTER(test_sum<int, int>) // registers the test by passing concrete types
REGISTER(test_sum<int, double>)


struct fixture {
    int value_;
    fixture()
        : value_(1)
    {}
    virtual ~fixture() UNITTEST_NOEXCEPT_FALSE
    {}
};

TEST_TPL_FIXTURE(fixture, test_fixture)
{
    ASSERT_EQUAL(value_, static_cast<Type1>(1))
}
REGISTER(test_fixture<int>)
REGISTER(test_fixture<long>)


TEST_TPL_SKIP(test_that_is_skipped, "for demo purposes")
{
    Type1 a = 2;
    ASSERT_EQUAL(2, a)
}
REGISTER(test_that_is_skipped<int>) // registers the test by passing concrete types

}
