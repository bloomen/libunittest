#include <libunittest/all.hpp>
using namespace unittest::assertions;
using namespace unittest::core;
using unittest::feps;
using unittest::testfailure;


struct test_checkers : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_checkers)
        UNITTEST_RUN(test_check_epsilon)
        UNITTEST_RUN(test_check_range_bounds)
    }

    void test_check_epsilon()
    {
        check_epsilon(0.5, UNITTEST_FUNC);
        auto functor1 = []() { check_epsilon(0, UNITTEST_FUNC); };
        assert_throw<testfailure>(functor1, SPOT);
        auto functor2 = []() { check_epsilon(-1, UNITTEST_FUNC); };
        assert_throw<testfailure>(functor2, SPOT);
    }

    void test_check_range_bounds()
    {
        check_range_bounds(0.5, 1, UNITTEST_FUNC);
        check_range_bounds(1, 1, UNITTEST_FUNC);
        auto functor1 = []() { check_range_bounds(2, 1, UNITTEST_FUNC); };
        assert_throw<testfailure>(functor1, SPOT);
        auto functor2 = []() { check_range_bounds<double, double>(1+feps, 1, UNITTEST_FUNC); };
        assert_throw<testfailure>(functor2, SPOT);
    }

};

REGISTER(test_checkers)
