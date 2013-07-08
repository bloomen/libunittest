#pragma once
#include "unittest.hpp"

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
    }

    void test_assert_true();
    void test_assert_false();
    void test_assert_equal();
    void test_assert_not_equal();
    void test_assert_approx_equal();
    void test_assert_approx_not_equal();
    void test_assert_greater();
    void test_assert_greater_equal();
    void test_assert_lesser();
    void test_assert_lesser_equal();
    void test_assert_in_range();
    void test_assert_not_in_range();
    void test_assert_in_container();
    void test_assert_not_in_container();
    void test_assert_approx_in_container();
    void test_assert_approx_not_in_container();
    void test_assert_equal_containers();
    void test_assert_not_equal_containers();
    void test_assert_approx_equal_containers();
    void test_assert_approx_not_equal_containers();
    void test_assert_all_of();
    void test_assert_not_all_of();
    void test_assert_any_of();
    void test_assert_none_of();
    void test_assert_regex_match();
    void test_assert_not_regex_match();
    void test_assert_throw();
    void test_assert_no_throw();

private:
    template<typename Functor>
    void assert_fail(Functor functor, const std::string& spot)
    {
        assert_throw<unittest::testfailure>(functor, spot);
    }

    static bool is_value_one(double value);
};
