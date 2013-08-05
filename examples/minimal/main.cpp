#include "libunittest/unittest.hpp"

struct test_stuff : unittest::testcase<> {
    static void run()
    {
        UNITTEST_CLASS(test_stuff)
        UNITTEST_RUN(test_value_is_true)
    }

    void test_value_is_true()
    {
        bool value = true;
        assert_true(value);
    }
};

void unittest::run_all_tests()
{
    unittest::call<test_stuff>();
}

int main(int argc, char **argv) {
    return unittest::make_default_environment(argc, argv);
}

/* Screen output with './unittest_example -v':
test_stuff.test_value_is_true ... ok

--------------------------------------------------
Ran 1 tests in 0.00045s

OK
*/

