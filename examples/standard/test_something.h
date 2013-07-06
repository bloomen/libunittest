#pragma once
#include "unittest.hpp"

//a test context
struct test_context {
    std::string message;
    test_context()
        : message("here I am")
    {
        //do something expensive here giving the same context to selected tests
    }
    ~test_context()
    {
        //shut down what you've done in the constructor
    }
};

//a test class with a test context
struct test_something : unittest::testcase<test_context> {

    //this static method runs the tests
    static void run()
    {
        test_context context; //a test context that some tests are run within
        UNITTEST_RUNCXT(context, test_something, test_has_context)
        UNITTEST_RUNCXT(context, test_something, test_correct_message)
        UNITTEST_RUN(test_something, test_no_context)
    }

    void test_has_context();
    void test_correct_message();
    void test_no_context();

};