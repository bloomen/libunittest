/**
 * @brief Assertion macros for further convenience
 * @file assertmacros.hpp
 */
#pragma once


#define UNITTEST_ASSERT_TRUE(value) \
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value))
#define UNITTEST_ASSERT_TRUE_MSG(value, message) \
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value, message), message)
#define UNITTEST_NDASSERT_TRUE(value) \
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value), UNITTEST_NDAS)
#define UNITTEST_NDASSERT_TRUE_MSG(value, message) \
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value, message), UNITTEST_NDAS, message)
