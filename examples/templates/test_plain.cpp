#include <libunittest/all.hpp>
using namespace unittest::assertions;

COLLECTION(templates_plain)
{

TEST_TPL(test_sum)
{
    Type1 a = 2;
    Type2 b = 3; // you can use up to 3 template types: Type1, Type2, Type3
    assert_equal(5, a + b, SPOT);
}
REGISTER(test_sum<int, int>) // registers the test by passing concrete types
REGISTER(test_sum<int, double>)


struct fixture {
    int value_;
    fixture()
        : value_(1)
    {}
    virtual ~fixture() noexcept(false)
    {}
};

TEST_TPL_FIXTURE(fixture, test_fixture)
{
    assert_equal(value_, static_cast<Type1>(1));
}
REGISTER(test_fixture<int>)
REGISTER(test_fixture<long>)


TEST_TPL_SKIP(test_that_is_skipped, "for demo purposes")
{
    Type1 a = 2;
    assert_equal(2, a);
}
REGISTER(test_that_is_skipped<int>) // registers the test by passing concrete types

}
