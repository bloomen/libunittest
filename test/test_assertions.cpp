#include "test_assertions.h"
typedef test_assertions test;
#define SPOT UNITTEST_SPOT

bool test_assertions::is_value_one(double value)
{
    if (value<0) throw std::invalid_argument("wrong input");
    return value==1;
}

void test_assertions::test_assert_true()
{
    assert_true(true, SPOT);
    assert_true(1, SPOT);
    int *p = new int;
    assert_true(p, SPOT);
    delete p;
    assert_fail(std::bind(&test::assert_true<bool>, *this, false), SPOT);
}

void test_assertions::test_assert_false()
{
    assert_false(false, SPOT);
    assert_false(0, SPOT);
    int *p = nullptr;
    assert_false(p, SPOT);
    assert_fail(std::bind(&test::assert_false<bool>, *this, true), SPOT);
}

void test_assertions::test_assert_equal()
{
    assert_equal(1, 1, SPOT);
    assert_fail(std::bind(&test::assert_equal<int, int>, *this, 1, 2), SPOT);
}

void test_assertions::test_assert_not_equal()
{
    assert_not_equal(1, 2, SPOT);
    assert_fail(std::bind(&test::assert_not_equal<int, int>, *this, 1, 1), SPOT);
}

void test_assertions::test_assert_approx_equal()
{
    assert_approx_equal(1.0, 1.01, 0.011, SPOT);
    assert_fail(std::bind(&test::assert_approx_equal<double, double, double>, *this, 1.0, 1.01, 0.01), SPOT);
}

void test_assertions::test_assert_approx_not_equal()
{
    assert_approx_not_equal(1.0, 1.01, 0.01, SPOT);
    assert_fail(std::bind(&test::assert_approx_not_equal<double, double, double>, *this, 1.0, 1.01, 0.011), SPOT);
}

void test_assertions::test_assert_greater()
{
    assert_greater(2, 1, SPOT);
    assert_fail(std::bind(&test::assert_greater<int, int>, *this, 1, 2), SPOT);
    assert_fail(std::bind(&test::assert_greater<int, int>, *this, 1, 1), SPOT);
}

void test_assertions::test_assert_greater_equal()
{
    assert_greater_equal(2, 1, SPOT);
    assert_greater_equal(1, 1, SPOT);
    assert_fail(std::bind(&test::assert_greater_equal<int, int>, *this, 1, 2), SPOT);
}

void test_assertions::test_assert_lesser()
{
    assert_lesser(1, 2, SPOT);
    assert_fail(std::bind(&test::assert_lesser<int, int>, *this, 2, 1), SPOT);
    assert_fail(std::bind(&test::assert_lesser<int, int>, *this, 1, 1), SPOT);
}

void test_assertions::test_assert_lesser_equal()
{
    assert_lesser_equal(1, 2, SPOT);
    assert_lesser_equal(1, 1, SPOT);
    assert_fail(std::bind(&test::assert_lesser_equal<int, int>, *this, 2, 1), SPOT);
}

void test_assertions::test_assert_in_range()
{
    assert_in_range(1.5, 1, 2, SPOT);
    assert_in_range(1.01, 1, 2, SPOT);
    assert_in_range(1.99, 1, 2, SPOT);
    assert_fail(std::bind(&test::assert_in_range<int, int, int>, *this, 3, 1, 2), SPOT);
}

void test_assertions::test_assert_not_in_range()
{
    assert_not_in_range(3, 1, 2, SPOT);
    assert_not_in_range(1, 1, 2, SPOT);
    assert_not_in_range(2, 1, 2, SPOT);
    assert_fail(std::bind(&test::assert_not_in_range<double, int, int>, *this, 1.5, 1, 2), SPOT);
}

void test_assertions::test_assert_in_container()
{
    std::vector<int> vec = {1, 2, 3};
    assert_in_container(2, vec, SPOT);
    assert_fail(std::bind(&test::assert_in_container<double, std::vector<int>>, *this, 4, vec), SPOT);
}

void test_assertions::test_assert_not_in_container()
{
    std::vector<int> vec = {1, 2, 3};
    assert_not_in_container(4, vec, SPOT);
    assert_fail(std::bind(&test::assert_not_in_container<double, std::vector<int>>, *this, 2, vec), SPOT);
}

void test_assertions::test_assert_approx_in_container()
{
    std::vector<int> vec = {1, 2, 3};
    assert_approx_in_container(2.1, vec, 0.11, SPOT);
    assert_fail(std::bind(&test::assert_approx_in_container<double, std::vector<int>, double>, *this, 2.1, vec, 0.1), SPOT);
}

void test_assertions::test_assert_approx_not_in_container()
{
    std::vector<int> vec = {1, 2, 3};
    assert_approx_not_in_container(2.1, vec, 0.1, SPOT);
    assert_fail(std::bind(&test::assert_approx_not_in_container<double, std::vector<int>, double>, *this, 2.1, vec, 0.11), SPOT);
}

void test_assertions::test_assert_equal_containers()
{
    std::vector<int> vec = {1, 2, 3};
    assert_equal_containers(vec, vec, SPOT);
    std::vector<int> vec2 = {1, 2, 4};
    assert_fail(std::bind(&test::assert_equal_containers<std::vector<int>, std::vector<int>>, *this, vec, vec2), SPOT);
}

void test_assertions::test_assert_not_equal_containers()
{
    std::vector<int> vec = {1, 2, 3};
    std::vector<int> vec2 = {1, 2, 4};
    assert_not_equal_containers(vec, vec2, SPOT);
    assert_fail(std::bind(&test::assert_not_equal_containers<std::vector<int>, std::vector<int>>, *this, vec, vec), SPOT);
}

void test_assertions::test_assert_approx_equal_containers()
{
    std::vector<int> vec = {1, 2, 3};
    std::vector<int> vec2 = {1, 2, 4};
    assert_approx_equal_containers(vec, vec2, 1.01, SPOT);
    assert_fail(std::bind(&test::assert_approx_equal_containers<std::vector<int>, std::vector<int>, double>, *this, vec, vec2, 1), SPOT);
}

void test_assertions::test_assert_approx_not_equal_containers()
{
    std::vector<int> vec = {1, 2, 3};
    std::vector<int> vec2 = {1, 2, 4};
    assert_approx_not_equal_containers(vec, vec2, 1, SPOT);
    assert_fail(std::bind(&test::assert_approx_not_equal_containers<std::vector<int>, std::vector<int>, double>, *this, vec, vec2, 1.01), SPOT);
}

void test_assertions::test_assert_all_of()
{
    std::vector<double> vec = {1, 1, 1};
    assert_all_of(vec, test::is_value_one, SPOT);
    std::vector<double> vec2 = {1, 2, 1};
    assert_fail(std::bind(&test::assert_all_of<std::vector<double>, decltype(test::is_value_one)>, *this, vec2, test::is_value_one), SPOT);
}

void test_assertions::test_assert_not_all_of()
{
    std::vector<double> vec = {1, 2, 1};
    assert_not_all_of(vec, test::is_value_one, SPOT);
    std::vector<double> vec2 = {1, 1, 1};
    assert_fail(std::bind(&test::assert_not_all_of<std::vector<double>, decltype(test::is_value_one)>, *this, vec2, test::is_value_one), SPOT);
}

void test_assertions::test_assert_any_of()
{
    std::vector<double> vec = {1, 2, 3};
    assert_any_of(vec, test::is_value_one, SPOT);
    std::vector<double> vec2 = {3, 4, 5};
    assert_fail(std::bind(&test::assert_any_of<std::vector<double>, decltype(test::is_value_one)>, *this, vec2, test::is_value_one), SPOT);
}

void test_assertions::test_assert_none_of()
{
    std::vector<double> vec = {3, 4, 5};
    assert_none_of(vec, test::is_value_one, SPOT);
    std::vector<double> vec2 = {1, 2, 3};
    assert_fail(std::bind(&test::assert_none_of<std::vector<double>, decltype(test::is_value_one)>, *this, vec2, test::is_value_one), SPOT);
}

void test_assertions::test_assert_regex_match()
{
    assert_regex_match("peter", ".+", SPOT);
}

void test_assertions::test_assert_not_regex_match()
{
    assert_not_regex_match("peter", "a-z", SPOT);
}

void test_assertions::test_assert_throw()
{
    assert_throw<std::invalid_argument>(std::bind(test::is_value_one, -1), SPOT);
}

void test_assertions::test_assert_no_throw()
{
    assert_no_throw(std::bind(test::is_value_one, 1), SPOT);
}
