#include "test_something.h"
#define SPOT UNITTEST_SPOT

void test_something::test_has_context()
{
    //in case the test is run within a context, you can always
    //access the pointer to the context through get_test_context().
    auto context = get_test_context();
    assert_true(context, SPOT);
}

void test_something::test_correct_message()
{
    auto context = get_test_context();
    assert_equal("here I am", context->message, SPOT);
}

void test_something::test_no_context()
{
    auto context = get_test_context();
    assert_false(context, SPOT);
}
