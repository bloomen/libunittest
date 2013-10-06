#include <libunittest/unittest.hpp>

struct test_stuff : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_stuff)
        UNITTEST_RUN(test_value_is_true)
    }

    void test_value_is_true()
    {
        assert_true(true);
    }
};

UNITTEST_REGISTER(test_stuff)

int main(int argc, char **argv) {
    return unittest::process(argc, argv);
}

/* Screen output with './unittest.exe -v':
test_stuff.test_value_is_true ... ok

--------------------------------------------------
Ran 1 tests in 0.00045s

OK
*/
