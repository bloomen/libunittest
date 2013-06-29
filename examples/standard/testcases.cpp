#include "test_whatever.h"
#include "test_something.h"

void unittest::run_all_tests() {

    unittest::call<test_whatever>();
    unittest::call<test_something>();

// Or run in parallel using, e.g., std::thread
/*
	std::thread t1(unittest::call<test_whatever>);
	std::thread t2(unittest::call<test_something>);
	t1.join();
	t2.join();
*/
}
