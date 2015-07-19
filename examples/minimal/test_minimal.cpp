#include <libunittest/all.hpp>

TEST(test_value_is_true)
{
    const auto value = true;
    ASSERT_TRUE(value)
}

/* Screen output with './unittest.exe -v':
test_value_is_true::test ... [0.00045s] ok

--------------------------------------------------
Ran 1 tests in 0.00045s

OK
*/
