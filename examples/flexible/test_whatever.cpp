#include "test_whatever.h"
#define SPOT UNITTEST_SPOT

UNITTEST_REGISTER(test_whatever) // this registers the test class

void test_whatever::test_throw()
{
    auto functor = [](){ throw std::bad_cast(); };
    assert_throw<std::bad_cast>(functor, SPOT);
}

void test_whatever::test_in_range()
{
    assert_in_range(1, 0.9, 1.1, SPOT);
}

void test_whatever::test_in_container()
{
    const std::vector<int> container = {1, 2, 3};
    assert_in_container(2, container, SPOT);
}
