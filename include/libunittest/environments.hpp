#pragma once
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief This function is to be implemented by the user if any of the
 *  predefined environment functions are called. run_all_tests() should
 *  contain a list of calls to test classes
 */
void
run_all_tests();
/**
 * @brief Sets up a default testing environment and calls run_all_tests().
 *  This high-level function is intended to be used directly from the
 *  user's main() function
 * @param argc The number of user arguments
 * @param argv The array of user arguments
 * @returns A platform dependent program execution status: A success value if
 *  all tests succeed and an error value otherwise
 */
int
make_default_environment(int argc, char **argv);

} // unittest
