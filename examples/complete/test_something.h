#pragma once
#include "unittest.hpp"
#define SPOT UNITTEST_SPOT

//a test context
struct test_context {
    bool context_alive;
    test_context() : context_alive(true)
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
        UNITTEST_RUNCXT(context, test_something, test_true)
        UNITTEST_RUNCXT(context, test_something, test_false)
        UNITTEST_RUNCXT(context, test_something, test_equal)
        UNITTEST_RUNCXT(context, test_something, test_not_equal)
        UNITTEST_RUN(test_something, test_no_context)
        UNITTEST_RUN(test_something, test_approx_equal)
        UNITTEST_RUN(test_something, test_approx_not_equal)
        UNITTEST_RUN(test_something, test_greater)
        UNITTEST_RUN(test_something, test_greater_equal)
        UNITTEST_RUN(test_something, test_smaller)
        UNITTEST_RUN(test_something, test_smaller_equal)
    }

    //in case the test is run within a context, you can always
    //access the pointer to the context through get_test_context().
    void test_true()
    {
        auto context = get_test_context();
        assert_true(context, SPOT);
        assert_true(context->context_alive, SPOT);
    }

    void test_false()
    {
        bool result = false;
        assert_false(result, SPOT);
    }

    void test_equal()
    {
        double expected = 3.1415;
        assert_equal(expected, 3.1415, SPOT);
    }

    void test_not_equal()
    {
        double value = 3.1416;
        assert_not_equal(value, 3.1415, SPOT);
    }

    void test_no_context()
    {
        assert_false(get_test_context(), SPOT);
    }

    void test_approx_equal()
    {
        double expected = 1;
        assert_approx_equal(expected, 1.009, 0.01, SPOT);
    }

    void test_approx_not_equal()
    {
        double value = 1;
        assert_approx_not_equal(value, 1.01, 0.01, SPOT);
    }

    void test_greater()
    {
        assert_greater(2, 1, SPOT);
    }

    void test_greater_equal()
    {
        assert_greater_equal(2, 2, SPOT);
    }

    void test_smaller()
    {
        assert_smaller(1, 2, SPOT);
    }

    void test_smaller_equal()
    {
        assert_smaller_equal(2, 2, SPOT);
    }

};
