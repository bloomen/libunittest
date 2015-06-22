/**
 * @brief Assertion macros for further convenience
 * @file assertmacros.hpp
 */
#pragma once
/**
 * @brief Asserts that a value is true.
 * @param value A value
 */
#define UNITTEST_ASSERT_TRUE(value) \
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value))
/**
 * @brief Asserts that a value is true.
 * @param value A value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_TRUE_MSG(value, message) \
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value, message), message)
/**
 * @brief Asserts that a value is true (non-deadly assertion).
 * @param value A value
 */
#define UNITTEST_NDASSERT_TRUE(value) \
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value), UNITTEST_NDAS)
/**
 * @brief Asserts that a value is true (non-deadly assertion).
 * @param value A value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_TRUE_MSG(value, message) \
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value, message), UNITTEST_NDAS, message)
/**
 * @brief Asserts that a value is false.
 * @param value A value
 */
#define UNITTEST_ASSERT_FALSE(value) \
unittest::assertions::assert_false(value, UNITTEST_SPOT, UNITTEST_CALL(value))
/**
 * @brief Asserts that a value is false.
 * @param value A value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_FALSE_MSG(value, message) \
unittest::assertions::assert_false(value, UNITTEST_SPOT, UNITTEST_CALL(value, message), message)
/**
 * @brief Asserts that a value is false (non-deadly assertion).
 * @param value A value
 */
#define UNITTEST_NDASSERT_FALSE(value) \
unittest::assertions::assert_false(value, UNITTEST_SPOT, UNITTEST_CALL(value), UNITTEST_NDAS)
/**
 * @brief Asserts that a value is false (non-deadly assertion).
 * @param value A value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_FALSE_MSG(value, message) \
unittest::assertions::assert_false(value, UNITTEST_SPOT, UNITTEST_CALL(value, message), UNITTEST_NDAS, message)
/**
 * @brief Asserts that two values are equal.
 *  Required operators: ==, <<
 * @param expected The expected value
 * @param actual The actual value
 */
#define UNITTEST_ASSERT_EQUAL(expected, actual) \
unittest::assertions::assert_equal(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual))
/**
 * @brief Asserts that two values are equal.
 *  Required operators: ==, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_EQUAL_MSG(expected, actual, message) \
unittest::assertions::assert_equal(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, message), message)
/**
 * @brief Asserts that two values are equal (non-deadly assertion).
 *  Required operators: ==, <<
 * @param expected The expected value
 * @param actual The actual value
 */
#define UNITTEST_NDASSERT_EQUAL(expected, actual) \
unittest::assertions::assert_equal(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual), UNITTEST_NDAS)
/**
 * @brief Asserts that two values are equal (non-deadly assertion).
 *  Required operators: ==, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_EQUAL_MSG(expected, actual, message) \
unittest::assertions::assert_equal(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, message), UNITTEST_NDAS, message)
/**
 * @brief Asserts that two values are not equal.
 *  Required operators: ==, <<
 * @param first The first value
 * @param second The second value
 */
#define UNITTEST_ASSERT_NOT_EQUAL(first, second) \
unittest::assertions::assert_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second))
/**
 * @brief Asserts that two values are not equal.
 *  Required operators: ==, <<
 * @param first The first value
 * @param second The second value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_NOT_EQUAL_MSG(first, second, message) \
unittest::assertions::assert_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second, message), message)
/**
 * @brief Asserts that two values are not equal (non-deadly assertion).
 *  Required operators: ==, <<
 * @param first The first value
 * @param second The second value
 */
#define UNITTEST_NDASSERT_NOT_EQUAL(first, second) \
unittest::assertions::assert_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS)
/**
 * @brief Asserts that two values are not equal (non-deadly assertion).
 *  Required operators: ==, <<
 * @param first The first value
 * @param second The second value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_NOT_EQUAL_MSG(first, second, message) \
unittest::assertions::assert_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second, message), UNITTEST_NDAS, message)
/**
 * @brief Asserts that two values are approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon.
 *  Required operators: <, >, -, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param epsilon The epsilon
 */
#define UNITTEST_ASSERT_APPROX_EQUAL(expected, actual, epsilon) \
unittest::assertions::assert_approx_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon))
/**
 * @brief Asserts that two values are approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon.
 *  Required operators: <, >, -, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_APPROX_EQUAL_MSG(expected, actual, epsilon, message) \
unittest::assertions::assert_approx_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon, message), message)
/**
 * @brief Asserts that two values are approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon (non-deadly assertions).
 *  Required operators: <, >, -, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param epsilon The epsilon
 */
#define UNITTEST_NDASSERT_APPROX_EQUAL(expected, actual, epsilon) \
unittest::assertions::assert_approx_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon), UNITTEST_NDAS)
/**
 * @brief Asserts that two values are approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon (non-deadly assertions).
 *  Required operators: <, >, -, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_APPROX_EQUAL_MSG(expected, actual, epsilon, message) \
unittest::assertions::assert_approx_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon, message), UNITTEST_NDAS, message)
/**
 * @brief Asserts that two values are not approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon is false.
 *  Required operators: <, >, -, <<
 * @param first The first value
 * @param second The second value
 * @param epsilon The epsilon
 */
#define UNITTEST_ASSERT_APPROX_NOT_EQUAL(first, second, epsilon) \
unittest::assertions::assert_approx_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon))
/**
 * @brief Asserts that two values are not approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon is false.
 *  Required operators: <, >, -, <<
 * @param first The first value
 * @param second The second value
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_APPROX_NOT_EQUAL_MSG(first, second, epsilon, message) \
unittest::assertions::assert_approx_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon, message), message)
/**
 * @brief Asserts that two values are not approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon is false (non-deadly assertion).
 *  Required operators: <, >, -, <<
 * @param first The first value
 * @param second The second value
 * @param epsilon The epsilon
 */
#define UNITTEST_NDASSERT_APPROX_NOT_EQUAL(first, second, epsilon) \
unittest::assertions::assert_approx_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon), UNITTEST_NDAS)
/**
 * @brief Asserts that two values are not approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon is false (non-deadly assertion).
 *  Required operators: <, >, -, <<
 * @param first The first value
 * @param second The second value
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_APPROX_NOT_EQUAL_MSG(first, second, epsilon, message) \
unittest::assertions::assert_approx_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon, message), UNITTEST_NDAS, message)
