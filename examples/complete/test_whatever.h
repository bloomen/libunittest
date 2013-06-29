#pragma once
#include "unittest.hpp"

//a test class without a test context
struct test_whatever : unittest::testcase<> {

    //this static method runs the tests
    static void run()
    {
        UNITTEST_RUN(test_whatever, test_throw)
        UNITTEST_RUN(test_whatever, test_in_range)
        UNITTEST_RUN(test_whatever, test_in_container)
    }

    void test_throw();
    void test_in_range();
    void test_in_container();

};
