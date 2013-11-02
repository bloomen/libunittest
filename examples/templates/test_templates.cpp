#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>


COLLECTION(templates)
{

TEST_TPL(test_simple)
{
    Type1 a = 2;
    Type2 b = 3; // you can use up to 5 template types: Type1, ..., Type5
    assert_equal(5, a + b, SPOT);
}
REGISTER_TPL(test_simple<int, int>) // registers the test by passing concrete types
REGISTER_TPL(test_simple<int, double>)


struct fixture {
    bool value_;
    fixture()
        : value_(true)
    {}
    ~fixture()
    {}
};

TEST_TPL_FIXTURE(fixture, test_fixture)
{
    assert_equal(value_, static_cast<Type1>(1));
}
REGISTER_TPL(test_fixture<int>)
REGISTER_TPL(test_fixture<long>)

}
