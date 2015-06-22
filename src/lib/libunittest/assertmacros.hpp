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
