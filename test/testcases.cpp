#include "test_assertions.h"
#include "test_misc.h"
#include "test_argparser.h"

void unittest::run_all_tests() {
    unittest::call<test_assertions>();
    unittest::call<test_misc>();
    unittest::call<test_argparser>();
}
