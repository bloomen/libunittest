#pragma once
#include <libunittest/unittest.hpp>

struct test_random : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_random)
        UNITTEST_RUN(test_random_int)
        UNITTEST_RUN(test_random_bool)
        UNITTEST_RUN(test_random_double)
        UNITTEST_RUN(test_random_choice)
        UNITTEST_RUN(test_random_vector)
        UNITTEST_RUN(test_random_shuffle)
    }

    void test_random_int();
    void test_random_bool();
    void test_random_double();
    void test_random_choice();
    void test_random_vector();
    void test_random_shuffle();

};
