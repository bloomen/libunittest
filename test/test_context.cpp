#include <libunittest/all.hpp>
using namespace unittest::assertions;

struct context {};

struct test_context : unittest::testcase<context> {

    static void run()
    {
        UNITTEST_CLASS(test_context)
        UNITTEST_RUN(test_testcase_has_no_context)
        auto ctx = std::make_shared<context>();
        UNITTEST_RUNCTX(ctx, test_testcase_has_context)
    }

    void test_testcase_has_no_context()
    {
        assert_false(get_test_context(), SPOT);
    }

    void test_testcase_has_context()
    {
        assert_true(get_test_context(), SPOT);
    }

};

REGISTER(test_context)
