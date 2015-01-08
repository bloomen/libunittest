#include <libunittest/all.hpp>
using namespace unittest::assertions;

TEST(test_value_is_true)
{
    assert_true(true);
}

/* Screen output with './unittest.exe -v':
test_value_is_true::test ... [0.00045s] ok

--------------------------------------------------
Ran 1 tests in 0.00045s

OK
*/
