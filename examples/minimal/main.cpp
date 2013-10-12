#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>

TEST(test_value_is_true)
{
    assert_true(true);
}

int main(int argc, char **argv)
{
    return unittest::process(argc, argv);
}

/* Screen output with './unittest.exe -v':
test_value_is_true ... ok

--------------------------------------------------
Ran 1 tests in 0.00045s

OK
*/
