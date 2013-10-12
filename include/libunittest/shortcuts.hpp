/**
 * @brief A collection of short aliases for selected macros
 * @file macros.hpp
 */
#pragma once
/**
 * @brief Defines a string with info about the current file name
 *  and the current line number
 */
#define SPOT \
UNITTEST_SPOT
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