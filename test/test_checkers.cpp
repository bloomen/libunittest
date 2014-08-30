#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>
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
        check_epsilon(0.5, __func__);
        auto functor1 = []() { check_epsilon(0, __func__); };
        assert_throw<testfailure>(functor1, SPOT);
        auto functor2 = []() { check_epsilon(-1, __func__); };
        assert_throw<testfailure>(functor2, SPOT);
    }

    void test_check_range_bounds()
    {
        check_range_bounds(0.5, 1, __func__);
        check_range_bounds(1, 1, __func__);
        auto functor1 = []() { check_range_bounds(2, 1, __func__); };
        assert_throw<testfailure>(functor1, SPOT);
        auto functor2 = []() { check_range_bounds<double, double>(1+feps, 1, __func__); };
        assert_throw<testfailure>(functor2, SPOT);
    }

};

REGISTER(test_checkers)
