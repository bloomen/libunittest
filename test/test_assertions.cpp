#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>
using unittest::feps;
using unittest::testfailure;

bool is_value_one(double value)
{
    if (value<0) throw std::invalid_argument("wrong input");
    return value==1;
}


struct test_assertions : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_assertions)
        UNITTEST_RUN(test_assert_true)
        UNITTEST_RUN(test_assert_false)
        UNITTEST_RUN(test_assert_equal)
        UNITTEST_RUN(test_assert_not_equal)
        UNITTEST_RUN(test_assert_approx_equal)
        UNITTEST_RUN(test_assert_approx_not_equal)
        UNITTEST_RUN(test_assert_greater)
        UNITTEST_RUN(test_assert_greater_equal)
        UNITTEST_RUN(test_assert_lesser)
        UNITTEST_RUN(test_assert_lesser_equal)
        UNITTEST_RUN(test_assert_in_range)
        UNITTEST_RUN(test_assert_not_in_range)
        UNITTEST_RUN(test_assert_in_container)
        UNITTEST_RUN(test_assert_not_in_container)
        UNITTEST_RUN(test_assert_approx_in_container)
        UNITTEST_RUN(test_assert_approx_not_in_container)
        UNITTEST_RUN(test_assert_equal_containers)
        UNITTEST_RUN(test_assert_not_equal_containers)
        UNITTEST_RUN(test_assert_approx_equal_containers)
        UNITTEST_RUN(test_assert_approx_not_equal_containers)
        UNITTEST_RUN(test_assert_all_of)
        UNITTEST_RUN(test_assert_not_all_of)
        UNITTEST_RUN(test_assert_any_of)
        UNITTEST_RUN(test_assert_none_of)
        UNITTEST_RUN(test_assert_regex_match)
        UNITTEST_RUN(test_assert_not_regex_match)
        UNITTEST_RUN(test_assert_throw)
        UNITTEST_RUN(test_assert_no_throw)
        UNITTEST_RUN(test_check_epsilon)
        UNITTEST_RUN(test_check_range_bounds)
    }

    void test_assert_true()
    {
        assert_true(true, SPOT);
        assert_true(1, SPOT);
        int *p = new int;
        assert_true(p, SPOT);
        delete p;
	auto functor = [this]() { this->assert_true(false); };
	assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_false()
    {
        assert_false(false, SPOT);
        assert_false(0, SPOT);
        int *p = nullptr;
        assert_false(p, SPOT);
	auto functor = [this]() { this->assert_false(true); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_equal()
    {
        assert_equal(1, 1, SPOT);
	auto functor = [this]() { this->assert_equal(1, 2); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_not_equal()
    {
        assert_not_equal(1, 2, SPOT);
	auto functor = [this]() { this->assert_not_equal(1, 1); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_approx_equal()
    {
        assert_approx_equal(1.0, 1.01, 0.011, SPOT);
        auto functor = [this]() { this->assert_approx_equal(1.0, 1.01, 0.01); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_approx_not_equal()
    {
        assert_approx_not_equal(1.0, 1.01, 0.01, SPOT);
	auto functor = [this]() { this->assert_approx_not_equal(1.0, 1.01, 0.011); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_greater()
    {
        assert_greater(2, 1, SPOT);
	auto functor1 = [this]() { this->assert_greater(1, 2); };
        assert_throw<testfailure>(functor1, SPOT);
	auto functor2 = [this]() { this->assert_greater(1, 1); };
        assert_throw<testfailure>(functor2, SPOT);
    }

    void test_assert_greater_equal()
    {
        assert_greater_equal(2, 1, SPOT);
        assert_greater_equal(1, 1, SPOT);
	auto functor = [this]() { this->assert_greater_equal(1, 2); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_lesser()
    {
        assert_lesser(1, 2, SPOT);
	auto functor1 = [this]() { this->assert_lesser(2, 1); };
        assert_throw<testfailure>(functor1, SPOT);
	auto functor2 = [this]() { this->assert_lesser(1, 1); };
        assert_throw<testfailure>(functor2, SPOT);
    }

    void test_assert_lesser_equal()
    {
        assert_lesser_equal(1, 2, SPOT);
        assert_lesser_equal(1, 1, SPOT);
	auto functor = [this]() { this->assert_lesser_equal(2, 1); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_in_range()
    {
        assert_in_range(1.5, 1, 2, SPOT);
        assert_in_range(1, 1, 2, SPOT);
        assert_in_range(2, 1, 2, SPOT);
	auto functor = [this]() { this->assert_in_range(3, 1, 2); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_not_in_range()
    {
        assert_not_in_range(3, 1, 2, SPOT);
        assert_not_in_range(1.-feps, 1, 2, SPOT);
        assert_not_in_range(2.+feps, 1, 2, SPOT);
	auto functor = [this]() { this->assert_not_in_range(1.5, 1, 2); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_in_container()
    {
        std::vector<int> vec = {1, 2, 3};
        assert_in_container(2, vec, SPOT);
	auto functor = [this,vec]() { this->assert_in_container(4, vec); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_not_in_container()
    {
        std::vector<int> vec = {1, 2, 3};
        assert_not_in_container(4, vec, SPOT);
	auto functor = [this,vec]() { this->assert_not_in_container(2, vec); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_approx_in_container()
    {
        std::vector<int> vec = {1, 2, 3};
        assert_approx_in_container(2.1, vec, 0.11, SPOT);
	auto functor = [this,vec]() { this->assert_approx_in_container(2.1, vec, 0.1); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_approx_not_in_container()
    {
        std::vector<int> vec = {1, 2, 3};
        assert_approx_not_in_container(2.1, vec, 0.1, SPOT);
	auto functor = [this,vec]() { this->assert_approx_not_in_container(2.1, vec, 0.11); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_equal_containers()
    {
        std::vector<int> vec = {1, 2, 3};
        assert_equal_containers(vec, vec, SPOT);
        std::vector<int> vec2 = {1, 2, 4};
	auto functor = [this,vec,vec2]() { this->assert_equal_containers(vec, vec2); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_not_equal_containers()
    {
        std::vector<int> vec = {1, 2, 3};
        std::vector<int> vec2 = {1, 2, 4};
        assert_not_equal_containers(vec, vec2, SPOT);
	auto functor = [this,vec]() { this->assert_not_equal_containers(vec, vec); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_approx_equal_containers()
    {
        std::vector<int> vec = {1, 2, 3};
        std::vector<int> vec2 = {1, 2, 4};
        assert_approx_equal_containers(vec, vec2, 1.01, SPOT);
	auto functor = [this,vec,vec2]() { this->assert_approx_equal_containers(vec, vec2, 1); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_approx_not_equal_containers()
    {
        std::vector<int> vec = {1, 2, 3};
        std::vector<int> vec2 = {1, 2, 4};
        assert_approx_not_equal_containers(vec, vec2, 1, SPOT);
	auto functor = [this,vec,vec2]() { this->assert_approx_not_equal_containers(vec, vec2, 1.01); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_all_of()
    {
        std::vector<double> vec = {1, 1, 1};
        assert_all_of(vec, is_value_one, SPOT);
        std::vector<double> vec2 = {1, 2, 1};
	auto functor = [this,vec2]() { this->assert_all_of(vec2, is_value_one); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_not_all_of()
    {
        std::vector<double> vec = {1, 2, 1};
        assert_not_all_of(vec, is_value_one, SPOT);
        std::vector<double> vec2 = {1, 1, 1};
	auto functor = [this,vec2]() { this->assert_not_all_of(vec2, is_value_one); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_any_of()
    {
        std::vector<double> vec = {1, 2, 3};
        assert_any_of(vec, is_value_one, SPOT);
        std::vector<double> vec2 = {3, 4, 5};
	auto functor = [this,vec2]() { this->assert_any_of(vec2, is_value_one); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_none_of()
    {
        std::vector<double> vec = {3, 4, 5};
        assert_none_of(vec, is_value_one, SPOT);
        std::vector<double> vec2 = {1, 2, 3};
	auto functor = [this,vec2]() { this->assert_none_of(vec2, is_value_one); };
        assert_throw<testfailure>(functor, SPOT);
    }

    void test_assert_regex_match()
    {
        assert_regex_match("peter", ".+", SPOT);
    }

    void test_assert_not_regex_match()
    {
        assert_not_regex_match("peter", "a-z", SPOT);
    }

    void test_assert_throw()
    {
        assert_throw<std::invalid_argument>(std::bind(is_value_one, -1), SPOT);
    }

    void test_assert_no_throw()
    {
        assert_no_throw(std::bind(is_value_one, 1), SPOT);
    }

    void test_check_epsilon()
    {
        check_epsilon(0.5, __func__);
	auto functor1 = [this]() { this->check_epsilon(0, __func__); };
        assert_throw<testfailure>(functor1, SPOT);
	auto functor2 = [this]() { this->check_epsilon(-1, __func__); };
        assert_throw<testfailure>(functor2, SPOT);
    }

    void test_check_range_bounds()
    {
        check_range_bounds(0.5, 1, __func__);
        check_range_bounds(1, 1, __func__);
	auto functor1 = [this]() { this->check_range_bounds(2, 1, __func__); };
        assert_throw<testfailure>(functor1, SPOT);
        auto functor2 = [this]() { this->check_range_bounds<double, double>(1+feps, 1, __func__); };
        assert_throw<testfailure>(functor2, SPOT);
    }

};

REGISTER(test_assertions)
