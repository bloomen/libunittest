/**
 * @brief Functions for calling test classes
 * @file call.hpp
 */
#pragma once
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Calls the static run() method of the test class
 */
template<typename TestCase>
void
call()
{
    TestCase::run();
}
/**
 * @brief Calls the static run() method of the test class with the test
 *  context as the one parameter
 * @param context The test context
 */
template<typename TestCase,
         typename TestContext>
void
call(const TestContext& context)
{
    TestCase::run(context);
}

} // unittest
