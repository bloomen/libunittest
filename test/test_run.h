#pragma once
#include "unittest.hpp"

struct test_run final : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_run)
        UNITTEST_RUN(test_observe_and_wait_no_timeout)
        UNITTEST_RUN(test_observe_and_wait_with_timeout)
    }

    void test_observe_and_wait_no_timeout();
    void test_observe_and_wait_with_timeout();

private:
    struct obswait {
        obswait(std::function<void()>* functor,
                bool expect_throw)
            : functor_(functor), expect_throw_(expect_throw)
        {}
        void operator()()
        {
            if (expect_throw_) {
                bool caught=false;
                try {
                    (*functor_)();
                } catch (unittest::testfailure&) {
                    caught = true;
                }
                if (!caught)
                    throw unittest::testfailure("'testfailure' not thrown");
            } else {
                (*functor_)();
            }
        }
    private:
        std::function<void()>* functor_;
        bool expect_throw_;
    };

};

