#pragma once
#include "unittest.hpp"

//a test class without a test context
struct test_whatever : unittest::testcase<> {

    //this static method runs the tests
    static void run()
    {
        UNITTEST_CLASS(test_whatever)
        UNITTEST_RUN(test_throw)
        UNITTEST_RUN(test_in_range)
        UNITTEST_RUN_TIME(test_in_container, 2) //a run with a timeout of 2s
    }

    void test_throw();
    void test_in_range();
    void test_in_container();

};
