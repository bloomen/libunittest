#include <libunittest/all.hpp>

COLLECTION(sweet_stuff) {

// a test class without a test context
struct test_whatever : unittest::testcase<> {

    // this static method runs the tests
    static void run()
    {
        UNITTEST_CLASS(test_whatever)
        UNITTEST_RUN(test_throw)
        UNITTEST_RUN_TIME(test_in_container, 2) // a timeout of 2s
        UNITTEST_RUN(test_in_range)
        UNITTEST_RUN_SKIP(test_that_is_skipped, "for demo purposes")
        UNITTEST_RUN_MAYBE(test_that_is_run, true, "message for when not run")
    }

    test_whatever() {} // executed before each test and before set_up()
    ~test_whatever() {} // executed after each test and after tear_down()

    void set_up() {} // executed before each test and after constructor
    void tear_down() {} // executed after each test and before destructor

    void test_throw()
    {
        TESTINFO("some cool info about your test")
        auto functor = [](){ throw std::bad_cast(); };
        ASSERT_THROW(std::bad_cast, functor)
    }

    void test_in_container()
    {
        const std::vector<int> container = {1, 2, 3};
        NDASSERT_IN_CONTAINER(2, container) // a non-deadly assertion
    }

    void test_in_range()
    {
        TESTINFO("helpful information: ", 42)
        ASSERT_IN_RANGE(1, 0.9, 1.1)
    }

    void test_that_is_skipped()
    {
        ASSERT_TRUE(false)
    }

    void test_that_is_run()
    {
        ASSERT_TRUE(true)
    }

};

REGISTER(test_whatever) // this registers the test class

}
