/**
 * @brief A collection of short aliases for selected macros
 * @file shortcuts.hpp
 */
#pragma once
/**
 * @brief Defines a string with info about the current file name
 *  and the current line number
 */
#define SPOT \
UNITTEST_SPOT
/**
 * @brief Logs info for the current test
 */
#define TESTINFO(...) \
UNITTEST_TESTINFO(__VA_ARGS__)
/**
 * @brief Registers a test class at the global registry
 */
#define REGISTER(...) \
UNITTEST_REGISTER(__VA_ARGS__)
/**
 * @brief Sets up a plain test
 * @param test_name The name of the test
 */
#define TEST(test_name) \
UNITTEST_TEST(test_name)
/**
 * @brief Sets up a plain test with a timeout
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define TEST_TIME(test_name, timeout) \
UNITTEST_TEST_TIME(test_name, timeout)
/**
 * @brief Sets up a plain test with a test fixture
 * @param fixture The test fixture
 * @param test_name The name of the test
 */
#define TEST_FIXTURE(fixture, test_name) \
UNITTEST_TEST_FIXTURE(fixture, test_name)
/**
 * @brief Sets up a plain test with a test fixture and timeout
 * @param fixture The test fixture
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define TEST_FIXTURE_TIME(fixture, test_name, timeout) \
UNITTEST_TEST_FIXTURE_TIME(fixture, test_name, timeout)
/**
 * @brief A test collection
 * @param name The name of the test collection
 */
#define COLLECTION(name) \
UNITTEST_COLLECTION(name)
/**
 * @brief Sets up a templated test
 * @param test_name The name of the test
 */
#define TEST_TPL(test_name) \
UNITTEST_TEST_TPL(test_name)
/**
 * @brief Sets up a templated test with a timeout
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define TEST_TPL_TIME(test_name, timeout) \
UNITTEST_TEST_TPL_TIME(test_name, timeout)
/**
 * @brief Sets up a templated test with a test fixture
 * @param fixture The test fixture
 * @param test_name The name of the test
 */
#define TEST_TPL_FIXTURE(fixture, test_name) \
UNITTEST_TEST_TPL_FIXTURE(fixture, test_name)
/**
 * @brief Sets up a templated test with a test fixture and timeout
 * @param fixture The test fixture
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define TEST_TPL_FIXTURE_TIME(fixture, test_name, timeout) \
UNITTEST_TEST_TPL_FIXTURE_TIME(fixture, test_name, timeout)
