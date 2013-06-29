#include "test_whatever.h"
#define SPOT UNITTEST_SPOT

void test_whatever::test_throw()
{
    assert_throw<std::bad_cast>([](){throw std::bad_cast();}, SPOT);
}

void test_whatever::test_in_range()
{
    assert_in_range(1, 0.9, 1.1, SPOT);
}

void test_whatever::test_in_container()
{
    assert_in_container(2, std::vector<int>{1, 2, 3}, SPOT);
}
