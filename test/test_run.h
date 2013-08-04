#pragma once
#include "unittest.hpp"

struct test_run final : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_run)
        UNITTEST_RUN(test_observe_and_wait)
    }

    void test_observe_and_wait();

};
