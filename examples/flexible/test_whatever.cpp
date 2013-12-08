#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>


// a test class without a test context
struct test_whatever : unittest::testcase<> {

    // this static method runs the tests
    static void run()
    {
        UNITTEST_CLASS(test_whatever)
        UNITTEST_RUN(test_throw)
        UNITTEST_RUN_TIME(test_in_container, 2) // a timeout of 2s
        UNITTEST_RUN(test_in_range)
    }

    test_whatever() {} // executed before each test
    ~test_whatever() {} // executed after each test

    void set_up() override {} // executed before each test
    void tear_down() override {} // executed after each test

    void test_throw()
    {
        LOGTEXT("some cool info about your test")
        auto functor = [](){ throw std::bad_cast(); };
        assert_throw<std::bad_cast>(functor, SPOT);
    }

    void test_in_container()
    {
        const std::vector<int> container = {1, 2, 3};
        assert_in_container(2, container, SPOT);
    }

    void test_in_range()
    {
        LOGTEXT("helpful information: ", 42)
        assert_in_range(1, 0.9, 1.1, SPOT);
    }

};

REGISTER(test_whatever) // this registers the test class
