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
        UNITTEST_RUN(test_check_isnan)
        UNITTEST_RUN(test_check_isfinite)
        UNITTEST_RUN(test_check_isfinite_container)
    }

    void test_check_isfinite_container()
    {
        unittest::core::check_isfinite_container(std::vector<double>{}, "", "");
        unittest::core::check_isfinite_container(std::vector<double>{0.}, "", "");
        unittest::core::check_isfinite_container(std::vector<int>{42}, "", "");
        unittest::core::check_isfinite_container(std::vector<double>{1.3}, "", "");
        unittest::core::check_isfinite_container(std::vector<double>{1.3, 47.4}, "", "");
        unittest::core::check_isfinite_container(std::vector<bool>{true}, "", "");
        unittest::core::check_isfinite_container(std::vector<std::string>{"peter"}, "", "");
        assert_throw<unittest::testfailure>([]() {
            unittest::core::check_isfinite_container(std::vector<double>{std::numeric_limits<double>::infinity()}, "", "");
        }, SPOT, NDAS);
        assert_throw<unittest::testfailure>([]() {
            unittest::core::check_isfinite_container(std::vector<double>{std::numeric_limits<double>::quiet_NaN()}, "", "");
        }, SPOT, NDAS);
        assert_throw<unittest::testfailure>([]() {
            unittest::core::check_isfinite_container(std::vector<double>{1.1, std::numeric_limits<double>::infinity()}, "", "");
        }, SPOT, NDAS);
        assert_throw<unittest::testfailure>([]() {
            unittest::core::check_isfinite_container(std::vector<double>{std::numeric_limits<double>::quiet_NaN(), 3.4}, "", "");
        }, SPOT, NDAS);
    }

    void test_check_isfinite()
    {
        unittest::core::check_isfinite(0., "", "");
        unittest::core::check_isfinite(42, "", "");
        unittest::core::check_isfinite(1.3, "", "");
        unittest::core::check_isfinite(true, "", "");
        unittest::core::check_isfinite("peter", "", "");
        assert_throw<unittest::testfailure>([]() {
            unittest::core::check_isfinite(std::numeric_limits<double>::infinity(), "", "");
        }, SPOT);
        assert_throw<unittest::testfailure>([]() {
            unittest::core::check_isfinite(std::numeric_limits<double>::quiet_NaN(), "", "");
        }, SPOT);
    }

    void test_check_isnan()
    {
        unittest::core::check_isnan(0., "", "");
        unittest::core::check_isnan(42, "", "");
        unittest::core::check_isnan(1.3, "", "");
        unittest::core::check_isnan(true, "", "");
        unittest::core::check_isnan("peter", "", "");
        unittest::core::check_isnan(std::numeric_limits<double>::infinity(), "", "");
        assert_throw<unittest::testfailure>([]() {
            unittest::core::check_isnan(std::numeric_limits<double>::quiet_NaN(), "", "");
        }, SPOT);
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
