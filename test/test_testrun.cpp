#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>

struct test_testrun : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_testrun)
        UNITTEST_RUN(test_testfunctor)
    }

    struct some_class {
        bool was_run_;
        some_class()
            : was_run_(false)
        {}
        void method()
        {
            was_run_= true;
        }
    };

    void test_testfunctor()
    {
        some_class object;
        std::atomic<bool> timed_out(false);
        unittest::internals::testfunctor<some_class>
            functor(object, &some_class::method, 3.5, &timed_out);
        functor();
        assert_true(object.was_run_, SPOT);
        assert_equal(3.5, functor.timeout(), SPOT);
        assert_false(functor.has_timed_out(), SPOT);
        timed_out = true;
        assert_true(functor.has_timed_out(), SPOT);
    }

};

REGISTER(test_testrun)
