#include <libunittest/all.hpp>
using namespace unittest::assertions;

// a test context
struct test_context {
    std::string message;
    test_context()
        : message("here I am")
    {
        // do something expensive here giving the same context to selected tests
    }
    ~test_context()
    {
        // shut down what you've done in the constructor
    }
};

// a test class with a test context
struct test_something : unittest::testcase<test_context> {

    // this static method runs the tests
    static void run()
    {
        UNITTEST_CLASS(test_something)
        auto context = std::make_shared<test_context>(); // context can be shared across tests
        UNITTEST_RUNCTX(context, test_has_context)
        UNITTEST_RUNCTX_TIME(context, test_correct_message, 3.5) // a timeout of 3.5s
        UNITTEST_RUN(test_no_context)
        UNITTEST_RUNCTX_TIME_SKIP(context, test_it_but_skipped, 5, "to show how tests are skipped")
    }

    void test_has_context()
    {
        // in case the test is run with a context, you can always
        // access the pointer to the context through get_test_context().
        auto context = get_test_context();
        assert_true(context, SPOT);
    }

    void test_correct_message()
    {
        TESTINFO("some cool info about your test")
        auto context = get_test_context();
        assert_equal("here I am", context->message, SPOT);
    }

    void test_no_context()
    {
        auto context = get_test_context();
        assert_false(context, SPOT);
    }

    void test_it_but_skipped()
    {
        assert_true(false, SPOT);
    }

};

REGISTER(test_something) // this registers the test class
