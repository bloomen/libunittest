#pragma once
#include "unittest.hpp"
#define SPOT UNITTEST_SPOT

//a function to test
double dummy(int a)
{
    if (a < 0) throw std::invalid_argument("Wrong input");
    return 3.1415 * a;
}

//a class with method to test
class some_class {
public:
    double dummy_method(int a)
    {
        if (a < 0) throw std::invalid_argument("Wrong input");
        return 3.1415 * a;
    }
};

//a test class without a test context
struct test_whatever : unittest::testcase<> {

    //this static method runs the tests
    static void run()
    {
        UNITTEST_RUN(test_whatever, test_no_throw)
        UNITTEST_RUN(test_whatever, test_method_no_throw)
        UNITTEST_RUN(test_whatever, test_throw)
        UNITTEST_RUN(test_whatever, test_method_throw)
        UNITTEST_RUN(test_whatever, test_in_range)
        UNITTEST_RUN(test_whatever, test_not_in_range)
        UNITTEST_RUN(test_whatever, test_in_container)
        UNITTEST_RUN(test_whatever, test_approx_in_container)
        UNITTEST_RUN(test_whatever, test_approx_not_in_container)
        UNITTEST_RUN(test_whatever, test_not_in_container)
        UNITTEST_RUN(test_whatever, test_equal_containers)
        UNITTEST_RUN(test_whatever, test_not_equal_containers)
        UNITTEST_RUN(test_whatever, test_approx_equal_containers)
        UNITTEST_RUN(test_whatever, test_approx_not_equal_containers)
        UNITTEST_RUN(test_whatever, test_all_of)
        UNITTEST_RUN(test_whatever, test_not_all_of)
        UNITTEST_RUN(test_whatever, test_any_of)
        UNITTEST_RUN(test_whatever, test_none_of)
        UNITTEST_RUN(test_whatever, test_regex_match)
        UNITTEST_RUN(test_whatever, test_not_regex_match)
    }

    void test_no_throw()
    {
        int argument = 1;
        assert_no_throw(std::bind(dummy, argument), SPOT);
    }

    void test_method_no_throw()
    {
        int argument = 1;
        some_class object;
        auto functor = std::bind(&some_class::dummy_method, object, argument);
        assert_no_throw(functor, SPOT);
    }

    void test_throw()
    {
        int argument = -1;
        assert_throw<std::invalid_argument>(std::bind(dummy, argument), SPOT);
    }

    void test_method_throw()
    {
        int argument = -1;
        some_class object;
        auto functor = std::bind(&some_class::dummy_method, object, argument);
        assert_throw<std::invalid_argument>(functor, SPOT);
    }

    void test_in_range()
    {
        double value = 1;
        assert_in_range(value, 0.9, 1.1, SPOT);
    }

    void test_not_in_range()
    {
        double value = 1;
        assert_not_in_range(value, 0.9, 0.95, SPOT);
    }

    void test_in_container()
    {
        std::vector<double> vec = {1, 2, 3};
        double value = 2;
        assert_in_container(value, vec, SPOT);
    }

    void test_approx_in_container()
    {
        std::vector<double> vec = {1, 2, 3};
        double value = 2.1;
        assert_approx_in_container(value, vec, 0.15, SPOT);
    }

    void test_approx_not_in_container()
    {
        std::vector<double> vec = {1, 2, 3};
        double value = 2.2;
        assert_approx_not_in_container(value, vec, 0.15, SPOT);
    }

    void test_not_in_container()
    {
        std::vector<double> vec = {1, 2, 3};
        double value = 4;
        assert_not_in_container(value, vec, SPOT);
    }

    void test_equal_containers()
    {
        std::vector<double> vec1 = {1, 2, 3};
        std::vector<double> vec2 = {1, 2, 3};
        assert_equal_containers(vec1, vec2, SPOT);
    }

    void test_approx_equal_containers()
    {
        std::vector<double> vec1 = {1, 2, 3};
        std::vector<double> vec2 = {1, 2.1, 3};
        assert_approx_equal_containers(vec1, vec2, 0.15, SPOT);
    }

    void test_not_equal_containers()
    {
        std::vector<double> vec1 = {1, 2, 3};
        std::vector<double> vec2 = {1, 2, 4};
        assert_not_equal_containers(vec1, vec2, SPOT);
    }

    void test_approx_not_equal_containers()
    {
        std::vector<double> vec1 = {1, 2, 3};
        std::vector<double> vec2 = {1, 2.2, 3};
        assert_approx_not_equal_containers(vec1, vec2, 0.15, SPOT);
    }

    void test_all_of()
    {
        std::vector<double> vec = {1, 1, 1};
        assert_all_of(vec, [](double val){return val==1;}, SPOT);
    }

    void test_not_all_of()
    {
        std::vector<double> vec = {1, 1, 2};
        assert_not_all_of(vec, [](double val){return val==1;}, SPOT);
    }

    void test_any_of()
    {
        std::vector<double> vec = {2, 1, 2};
        assert_any_of(vec, [](double val){return val==1;}, SPOT);
    }

    void test_none_of()
    {
        std::vector<double> vec = {2, 2, 2};
        assert_none_of(vec, [](double val){return val==1;}, SPOT);
    }

    void test_regex_match()
    {
        std::string value = "peter";
        std::string regex = ".+";
        assert_regex_match(value, regex, SPOT);
    }

    void test_not_regex_match()
    {
        std::string value = "peter";
        std::string regex = "a-z";
        assert_not_regex_match(value, regex, SPOT);
    }

};
