#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>

struct context {};

struct test_context final : unittest::testcase<context> {

    static void run()
    {
        UNITTEST_CLASS(test_context)
        UNITTEST_RUN(test_testcase_has_no_context)
        context cxt;
        UNITTEST_RUNCXT(cxt, test_testcase_has_context)
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

UNITTEST_REGISTER(test_context)
