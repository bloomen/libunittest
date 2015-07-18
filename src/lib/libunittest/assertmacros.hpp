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
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value));
/**
 * @brief Asserts that a value is true.
 * @param value A value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_TRUE_MSG(value, message) \
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value), message);
/**
 * @brief Asserts that a value is true (non-deadly assertion).
 * @param value A value
 */
#define UNITTEST_NDASSERT_TRUE(value) \
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value), UNITTEST_NDAS);
/**
 * @brief Asserts that a value is true (non-deadly assertion).
 * @param value A value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_TRUE_MSG(value, message) \
unittest::assertions::assert_true(value, UNITTEST_SPOT, UNITTEST_CALL(value), UNITTEST_NDAS, message);
/**
 * @brief Asserts that a value is false.
 * @param value A value
 */
#define UNITTEST_ASSERT_FALSE(value) \
unittest::assertions::assert_false(value, UNITTEST_SPOT, UNITTEST_CALL(value));
/**
 * @brief Asserts that a value is false.
 * @param value A value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_FALSE_MSG(value, message) \
unittest::assertions::assert_false(value, UNITTEST_SPOT, UNITTEST_CALL(value), message);
/**
 * @brief Asserts that a value is false (non-deadly assertion).
 * @param value A value
 */
#define UNITTEST_NDASSERT_FALSE(value) \
unittest::assertions::assert_false(value, UNITTEST_SPOT, UNITTEST_CALL(value), UNITTEST_NDAS);
/**
 * @brief Asserts that a value is false (non-deadly assertion).
 * @param value A value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_FALSE_MSG(value, message) \
unittest::assertions::assert_false(value, UNITTEST_SPOT, UNITTEST_CALL(value), UNITTEST_NDAS, message);
/**
 * @brief Asserts that two values are equal.
 *  Required operators: ==, <<
 * @param expected The expected value
 * @param actual The actual value
 */
#define UNITTEST_ASSERT_EQUAL(expected, actual) \
unittest::assertions::assert_equal(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual));
/**
 * @brief Asserts that two values are equal.
 *  Required operators: ==, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_EQUAL_MSG(expected, actual, message) \
unittest::assertions::assert_equal(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual), message);
/**
 * @brief Asserts that two values are equal (non-deadly assertion).
 *  Required operators: ==, <<
 * @param expected The expected value
 * @param actual The actual value
 */
#define UNITTEST_NDASSERT_EQUAL(expected, actual) \
unittest::assertions::assert_equal(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual), UNITTEST_NDAS);
/**
 * @brief Asserts that two values are equal (non-deadly assertion).
 *  Required operators: ==, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_EQUAL_MSG(expected, actual, message) \
unittest::assertions::assert_equal(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual), UNITTEST_NDAS, message);
/**
 * @brief Asserts that two values are not equal.
 *  Required operators: ==, <<
 * @param first The first value
 * @param second The second value
 */
#define UNITTEST_ASSERT_NOT_EQUAL(first, second) \
unittest::assertions::assert_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second));
/**
 * @brief Asserts that two values are not equal.
 *  Required operators: ==, <<
 * @param first The first value
 * @param second The second value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_NOT_EQUAL_MSG(first, second, message) \
unittest::assertions::assert_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), message);
/**
 * @brief Asserts that two values are not equal (non-deadly assertion).
 *  Required operators: ==, <<
 * @param first The first value
 * @param second The second value
 */
#define UNITTEST_NDASSERT_NOT_EQUAL(first, second) \
unittest::assertions::assert_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS);
/**
 * @brief Asserts that two values are not equal (non-deadly assertion).
 *  Required operators: ==, <<
 * @param first The first value
 * @param second The second value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_NOT_EQUAL_MSG(first, second, message) \
unittest::assertions::assert_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS, message);
/**
 * @brief Asserts that two values are approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon.
 *  Required operators: <, >, -, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param epsilon The epsilon
 */
#define UNITTEST_ASSERT_APPROX_EQUAL(expected, actual, epsilon) \
unittest::assertions::assert_approx_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon));
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
unittest::assertions::assert_approx_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon), message);
/**
 * @brief Asserts that two values are approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon (non-deadly assertions).
 *  Required operators: <, >, -, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param epsilon The epsilon
 */
#define UNITTEST_NDASSERT_APPROX_EQUAL(expected, actual, epsilon) \
unittest::assertions::assert_approx_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon), UNITTEST_NDAS);
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
unittest::assertions::assert_approx_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon), UNITTEST_NDAS, message);
/**
 * @brief Asserts that two values are not approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon is false.
 *  Required operators: <, >, -, <<
 * @param first The first value
 * @param second The second value
 * @param epsilon The epsilon
 */
#define UNITTEST_ASSERT_APPROX_NOT_EQUAL(first, second, epsilon) \
unittest::assertions::assert_approx_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon));
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
unittest::assertions::assert_approx_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon), message);
/**
 * @brief Asserts that two values are not approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon is false
 *  (non-deadly assertion).
 *  Required operators: <, >, -, <<
 * @param first The first value
 * @param second The second value
 * @param epsilon The epsilon
 */
#define UNITTEST_NDASSERT_APPROX_NOT_EQUAL(first, second, epsilon) \
unittest::assertions::assert_approx_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon), UNITTEST_NDAS);
/**
 * @brief Asserts that two values are not approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon is false
 *  (non-deadly assertion).
 *  Required operators: <, >, -, <<
 * @param first The first value
 * @param second The second value
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_APPROX_NOT_EQUAL_MSG(first, second, epsilon, message) \
unittest::assertions::assert_approx_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon), UNITTEST_NDAS, message);
/**
 * @brief Asserts that two values are relatively approx. equal up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon.
 *  Required operators: <, >, -, *, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param epsilon The epsilon
 */
#define UNITTEST_ASSERT_APPROXREL_EQUAL(expected, actual, epsilon) \
unittest::assertions::assert_approxrel_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon));
/**
 * @brief Asserts that two values are relatively approx. equal up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon.
 *  Required operators: <, >, -, *, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_APPROXREL_EQUAL_MSG(expected, actual, epsilon, message) \
unittest::assertions::assert_approxrel_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon), message);
/**
 * @brief Asserts that two values are relatively approx. equal up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon
 *  (non-deadly assertion).
 *  Required operators: <, >, -, *, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param epsilon The epsilon
 */
#define UNITTEST_NDASSERT_APPROXREL_EQUAL(expected, actual, epsilon) \
unittest::assertions::assert_approxrel_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon), UNITTEST_NDAS);
/**
 * @brief Asserts that two values are relatively approx. equal up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon
 *  (non-deadly assertion).
 *  Required operators: <, >, -, *, <<
 * @param expected The expected value
 * @param actual The actual value
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_APPROXREL_EQUAL_MSG(expected, actual, epsilon, message) \
unittest::assertions::assert_approxrel_equal(expected, actual, epsilon, UNITTEST_SPOT, UNITTEST_CALL(expected, actual, epsilon), UNITTEST_NDAS, message);
/**
 * @brief Asserts that two values are not relatively approx. equal up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon is false
 *  Required operators: <, >, -, *, <<
 * @param first The first value
 * @param second The second value
 * @param epsilon The epsilon
 */
#define UNITTEST_ASSERT_APPROXREL_NOT_EQUAL(first, second, epsilon) \
unittest::assertions::assert_approxrel_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon));
/**
 * @brief Asserts that two values are not relatively approx. equal up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon is false
 *  Required operators: <, >, -, *, <<
 * @param first The first value
 * @param second The second value
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_APPROXREL_NOT_EQUAL_MSG(first, second, epsilon, message) \
unittest::assertions::assert_approxrel_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon), message);
/**
 * @brief Asserts that two values are not relatively approx. equal up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon is false
 *  (non-deadly assertion).
 *  Required operators: <, >, -, *, <<
 * @param first The first value
 * @param second The second value
 * @param epsilon The epsilon
 */
#define UNITTEST_NDASSERT_APPROXREL_NOT_EQUAL(first, second, epsilon) \
unittest::assertions::assert_approxrel_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon), UNITTEST_NDAS);
/**
 * @brief Asserts that two values are not relatively approx. equal up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon is false
 *  (non-deadly assertion).
 *  Required operators: <, >, -, *, <<
 * @param first The first value
 * @param second The second value
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_APPROXREL_NOT_EQUAL_MSG(first, second, epsilon, message) \
unittest::assertions::assert_approxrel_equal(first, second, epsilon, UNITTEST_SPOT, UNITTEST_CALL(first, second, epsilon), UNITTEST_NDAS, message);
/**
 * @brief Asserts that the first value is greater than the second.
 *  Required operators: >, <<
 * @param first A value
 * @param second Another value
 */
#define UNITTEST_ASSERT_GREATER(first, second) \
unittest::assertions::assert_greater(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second));
/**
 * @brief Asserts that the first value is greater than the second.
 *  Required operators: >, <<
 * @param first A value
 * @param second Another value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_GREATER_MSG(first, second, message) \
unittest::assertions::assert_greater(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), message);
/**
 * @brief Asserts that the first value is greater than the second
 *  (non-deadly assertion).
 *  Required operators: >, <<
 * @param first A value
 * @param second Another value
 */
#define UNITTEST_NDASSERT_GREATER(first, second) \
unittest::assertions::assert_greater(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS);
/**
 * @brief Asserts that the first value is greater than the second
 *  (non-deadly assertion).
 *  Required operators: >, <<
 * @param first A value
 * @param second Another value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_GREATER_MSG(first, second, message) \
unittest::assertions::assert_greater(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS, message);
/**
 * @brief Asserts that the first value is greater than or equal to the second.
 *  Required operators: <, <<
 * @param first A value
 * @param second Another value
 */
#define UNITTEST_ASSERT_GREATER_EQUAL(first, second) \
unittest::assertions::assert_greater_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second));
/**
 * @brief Asserts that the first value is greater than or equal to the second.
 *  Required operators: <, <<
 * @param first A value
 * @param second Another value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_GREATER_EQUAL_MSG(first, second, message) \
unittest::assertions::assert_greater_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), message);
/**
 * @brief Asserts that the first value is greater than or equal
 *  to the second (non-deadly assertion).
 *  Required operators: <, <<
 * @param first A value
 * @param second Another value
 */
#define UNITTEST_NDASSERT_GREATER_EQUAL(first, second) \
unittest::assertions::assert_greater_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS);
/**
 * @brief Asserts that the first value is greater than or equal
 *  to the second (non-deadly assertion).
 *  Required operators: <, <<
 * @param first A value
 * @param second Another value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_GREATER_EQUAL_MSG(first, second, message) \
unittest::assertions::assert_greater_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS, message);
/**
 * @brief Asserts that the first value is greater than the second.
 *  Required operators: <, <<
 * @param first A value
 * @param second Another value
 */
#define UNITTEST_ASSERT_LESSER(first, second) \
unittest::assertions::assert_lesser(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second));
/**
 * @brief Asserts that the first value is lesser than the second.
 *  Required operators: <, <<
 * @param first A value
 * @param second Another value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_LESSER_MSG(first, second, message) \
unittest::assertions::assert_lesser(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), message);
/**
 * @brief Asserts that the first value is lesser than the second
 *  (non-deadly assertion).
 *  Required operators: <, <<
 * @param first A value
 * @param second Another value
 */
#define UNITTEST_NDASSERT_LESSER(first, second) \
unittest::assertions::assert_lesser(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS);
/**
 * @brief Asserts that the first value is lesser than the second
 *  (non-deadly assertion).
 *  Required operators: <, <<
 * @param first A value
 * @param second Another value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_LESSER_MSG(first, second, message) \
unittest::assertions::assert_lesser(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS, message);
/**
 * @brief Asserts that the first value is lesser than or equal to the second.
 *  Required operators: >, <<
 * @param first A value
 * @param second Another value
 */
#define UNITTEST_ASSERT_LESSER_EQUAL(first, second) \
unittest::assertions::assert_lesser_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second));
/**
 * @brief Asserts that the first value is lesser than or equal to the second.
 *  Required operators: >, <<
 * @param first A value
 * @param second Another value
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_LESSER_EQUAL_MSG(first, second, message) \
unittest::assertions::assert_lesser_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), message);
/**
 * @brief Asserts that the first value is lesser than or equal
 *  to the second (non-deadly assertion).
 *  Required operators: >, <<
 * @param first A value
 * @param second Another value
 */
#define UNITTEST_NDASSERT_LESSER_EQUAL(first, second) \
unittest::assertions::assert_lesser_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS);
/**
 * @brief Asserts that the first value is lesser than or equal
 *  to the second (non-deadly assertion).
 *  Required operators: >, <<
 * @param first A value
 * @param second Another value
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_LESSER_EQUAL_MSG(first, second, message) \
unittest::assertions::assert_lesser_equal(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS, message);
/**
 * @brief Asserts that a value is in a given range with included bounds.
 *  Required operators: <, >, <<
 * @param value A value
 * @param lower The lower bound
 * @param upper The upper bound
 */
#define UNITTEST_ASSERT_IN_RANGE(value, lower, upper) \
unittest::assertions::assert_in_range(value, lower, upper, UNITTEST_SPOT, UNITTEST_CALL(value, lower, upper));
/**
 * @brief Asserts that a value is in a given range with included bounds.
 *  Required operators: <, >, <<
 * @param value A value
 * @param lower The lower bound
 * @param upper The upper bound
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_IN_RANGE_MSG(value, lower, upper, message) \
unittest::assertions::assert_in_range(value, lower, upper, UNITTEST_SPOT, UNITTEST_CALL(value, lower, upper), message);
/**
 * @brief Asserts that a value is in a given range with included bounds
 *  (non-deadly assertion).
 *  Required operators: <, >, <<
 * @param value A value
 * @param lower The lower bound
 * @param upper The upper bound
 */
#define UNITTEST_NDASSERT_IN_RANGE(value, lower, upper) \
unittest::assertions::assert_in_range(value, lower, upper, UNITTEST_SPOT, UNITTEST_CALL(value, lower, upper), UNITTEST_NDAS);
/**
 * @brief Asserts that a value is in a given range with included bounds
 *  (non-deadly assertion).
 *  Required operators: <, >, <<
 * @param value A value
 * @param lower The lower bound
 * @param upper The upper bound
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_IN_RANGE_MSG(value, lower, upper, message) \
unittest::assertions::assert_in_range(value, lower, upper, UNITTEST_SPOT, UNITTEST_CALL(value, lower, upper), UNITTEST_NDAS, message);
/**
 * @brief Asserts that a value is not in a given range with included bounds.
 *  Required operators: <, >, <<
 * @param value A value
 * @param lower The lower bound
 * @param upper The upper bound
 */
#define UNITTEST_ASSERT_NOT_IN_RANGE(value, lower, upper) \
unittest::assertions::assert_not_in_range(value, lower, upper, UNITTEST_SPOT, UNITTEST_CALL(value, lower, upper));
/**
 * @brief Asserts that a value is not in a given range with included bounds.
 *  Required operators: <, >, <<
 * @param value A value
 * @param lower The lower bound
 * @param upper The upper bound
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_NOT_IN_RANGE_MSG(value, lower, upper, message) \
unittest::assertions::assert_not_in_range(value, lower, upper, UNITTEST_SPOT, UNITTEST_CALL(value, lower, upper), message);
/**
 * @brief Asserts that a value is not in a given range with included bounds
 *  (non-deadly assertion).
 *  Required operators: <, >, <<
 * @param value A value
 * @param lower The lower bound
 * @param upper The upper bound
 */
#define UNITTEST_NDASSERT_NOT_IN_RANGE(value, lower, upper) \
unittest::assertions::assert_not_in_range(value, lower, upper, UNITTEST_SPOT, UNITTEST_CALL(value, lower, upper), UNITTEST_NDAS);
/**
 * @brief Asserts that a value is not in a given range with included bounds
 *  (non-deadly assertion).
 *  Required operators: <, >, <<
 * @param value A value
 * @param lower The lower bound
 * @param upper The upper bound
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_NOT_IN_RANGE_MSG(value, lower, upper, message) \
unittest::assertions::assert_not_in_range(value, lower, upper, UNITTEST_SPOT, UNITTEST_CALL(value, lower, upper), UNITTEST_NDAS, message);
/**
 * @brief Asserts that a value is in a container.
 *  Required operators: ==
 * @param value A value
 * @param container A container
 */
#define UNITTEST_ASSERT_IN_CONTAINER(value, container) \
unittest::assertions::assert_in_container(value, container, UNITTEST_SPOT, UNITTEST_CALL(value, container));
/**
 * @brief Asserts that a value is in a container.
 *  Required operators: ==
 * @param value A value
 * @param container A container
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_IN_CONTAINER_MSG(value, container, message) \
unittest::assertions::assert_in_container(value, container, UNITTEST_SPOT, UNITTEST_CALL(value, container), message);
/**
 * @brief Asserts that a value is in a container (non-deadly assertion).
 *  Required operators: ==
 * @param value A value
 * @param container A container
 */
#define UNITTEST_NDASSERT_IN_CONTAINER(value, container) \
unittest::assertions::assert_in_container(value, container, UNITTEST_SPOT, UNITTEST_CALL(value, container), UNITTEST_NDAS);
/**
 * @brief Asserts that a value is in a container (non-deadly assertion).
 *  Required operators: ==
 * @param value A value
 * @param container A container
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_IN_CONTAINER_MSG(value, container, message) \
unittest::assertions::assert_in_container(value, container, UNITTEST_SPOT, UNITTEST_CALL(value, container), UNITTEST_NDAS, message);
/**
 * @brief Asserts that a value is not in a container.
 *  Required operators: ==
 * @param value A value
 * @param container A container
 */
#define UNITTEST_ASSERT_NOT_IN_CONTAINER(value, container) \
unittest::assertions::assert_not_in_container(value, container, UNITTEST_SPOT, UNITTEST_CALL(value, container));
/**
 * @brief Asserts that a value is not in a container.
 *  Required operators: ==
 * @param value A value
 * @param container A container
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_NOT_IN_CONTAINER_MSG(value, container, message) \
unittest::assertions::assert_not_in_container(value, container, UNITTEST_SPOT, UNITTEST_CALL(value, container), message);
/**
 * @brief Asserts that a value is not in a container (non-deadly assertion).
 *  Required operators: ==
 * @param value A value
 * @param container A container
 */
#define UNITTEST_NDASSERT_NOT_IN_CONTAINER(value, container) \
unittest::assertions::assert_not_in_container(value, container, UNITTEST_SPOT, UNITTEST_CALL(value, container), UNITTEST_NDAS);
/**
 * @brief Asserts that a value is not in a container (non-deadly assertion).
 *  Required operators: ==
 * @param value A value
 * @param container A container
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_NOT_IN_CONTAINER_MSG(value, container, message) \
unittest::assertions::assert_not_in_container(value, container, UNITTEST_SPOT, UNITTEST_CALL(value, container), UNITTEST_NDAS, message);
/**
 * @brief Asserts that a value is approx. in a container up to some epsilon.
 *  The assertion succeeds if |a - b| < epsilon for at least one element.
 *  Required operators: <, >, -
 * @param value A value
 * @param container A container
 * @param epsilon The epsilon
 */
#define UNITTEST_ASSERT_APPROX_IN_CONTAINER(value, container, epsilon) \
unittest::assertions::assert_approx_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon));
/**
 * @brief Asserts that a value is approx. in a container up to some epsilon.
 *  The assertion succeeds if |a - b| < epsilon for at least one element.
 *  Required operators: <, >, -
 * @param value A value
 * @param container A container
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_APPROX_IN_CONTAINER_MSG(value, container, epsilon, message) \
unittest::assertions::assert_approx_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), message);
/**
 * @brief Asserts that a value is approx. in a container up to some epsilon.
 *  The assertion succeeds if |a - b| < epsilon for at least one element (non-deadly assertion).
 *  Required operators: <, >, -
 * @param value A value
 * @param container A container
 * @param epsilon The epsilon
 */
#define UNITTEST_NDASSERT_APPROX_IN_CONTAINER(value, container, epsilon) \
unittest::assertions::assert_approx_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), UNITTEST_NDAS);
/**
 * @brief Asserts that a value is approx. in a container up to some epsilon.
 *  The assertion succeeds if |a - b| < epsilon for at least one element (non-deadly assertion).
 *  Required operators: <, >, -
 * @param value A value
 * @param container A container
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_APPROX_IN_CONTAINER_MSG(value, container, epsilon, message) \
unittest::assertions::assert_approx_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), UNITTEST_NDAS, message);
/**
 * @brief Asserts that a value is not approx. in a container up to some epsilon.
 *  The assertion succeeds if |a - b| < epsilon is false for all elements.
 *  Required operators: <, >, -
 * @param value A value
 * @param container A container
 * @param epsilon The epsilon
 */
#define UNITTEST_ASSERT_APPROX_NOT_IN_CONTAINER(value, container, epsilon) \
unittest::assertions::assert_approx_not_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon));
/**
 * @brief Asserts that a value is not approx. in a container up to some epsilon.
 *  The assertion succeeds if |a - b| < epsilon is false for all elements.
 *  Required operators: <, >, -
 * @param value A value
 * @param container A container
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_APPROX_NOT_IN_CONTAINER_MSG(value, container, epsilon, message) \
unittest::assertions::assert_approx_not_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), message);
/**
 * @brief Asserts that a value is not approx. in a container up to some epsilon.
 *  The assertion succeeds if |a - b| < epsilon is false for all elements (non-deadly assertion).
 *  Required operators: <, >, -
 * @param value A value
 * @param container A container
 */
#define UNITTEST_NDASSERT_APPROX_NOT_IN_CONTAINER(value, container, epsilon) \
unittest::assertions::assert_approx_not_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), UNITTEST_NDAS);
/**
 * @brief Asserts that a value is not approx. in a container up to some epsilon.
 *  The assertion succeeds if |a - b| < epsilon is false for all elements (non-deadly assertion).
 *  Required operators: <, >, -
 * @param value A value
 * @param container A container
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_APPROX_NOT_IN_CONTAINER_MSG(value, container, epsilon, message) \
unittest::assertions::assert_approx_not_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), UNITTEST_NDAS, message);
/**
 * @brief Asserts that a value is relatively approx. in a container up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon for at least one
 *  element. Required operators: <, >, -, *
 * @param value A value
 * @param container A container
 * @param epsilon The epsilon
 */
#define UNITTEST_ASSERT_APPROXREL_IN_CONTAINER(value, container, epsilon) \
unittest::assertions::assert_approxrel_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon));
/**
 * @brief Asserts that a value is relatively approx. in a container up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon for at least one
 *  element. Required operators: <, >, -, *
 * @param value A value
 * @param container A container
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_APPROXREL_IN_CONTAINER_MSG(value, container, epsilon, message) \
unittest::assertions::assert_approxrel_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), message);
/**
 * @brief Asserts that a value is relatively approx. in a container up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon for at least one
 *  element (non-deadly assertion). Required operators: <, >, -, *
 * @param value A value
 * @param container A container
 * @param epsilon The epsilon
 */
#define UNITTEST_NDASSERT_APPROXREL_IN_CONTAINER(value, container, epsilon) \
unittest::assertions::assert_approxrel_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), UNITTEST_NDAS);
/**
 * @brief Asserts that a value is relatively approx. in a container up to some
 *  epsilon. The assertion succeeds if |a - b| < |a| * epsilon for at least one
 *  element (non-deadly assertion). Required operators: <, >, -, *
 * @param value A value
 * @param container A container
 * @param epsilon The epsilon
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_APPROXREL_IN_CONTAINER_MSG(value, container, epsilon, message) \
unittest::assertions::assert_approxrel_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), UNITTEST_NDAS, message);
/**
 * @brief Asserts that a value is not relatively approx. in a container up to
 *  some epsilon. The assertion succeeds if |a - b| < |a| * epsilon is false for
 *  all elements. Required operators: <, >, -, *
 * @param value A value
 * @param container A container
 * @param epsilon The epsilon
 */
#define UNITTEST_ASSERT_APPROXREL_NOT_IN_CONTAINER(value, container, epsilon) \
unittest::assertions::assert_approxrel_not_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon));
/**
 * @brief Asserts that a value is not relatively approx. in a container up to
 *  some epsilon. The assertion succeeds if |a - b| < |a| * epsilon is false for
 *  all elements. Required operators: <, >, -, *
 * @param value A value
 * @param container A container
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_APPROXREL_NOT_IN_CONTAINER_MSG(value, container, epsilon, message) \
unittest::assertions::assert_approxrel_not_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), message);
/**
 * @brief Asserts that a value is not relatively approx. in a container up to
 *  some epsilon. The assertion succeeds if |a - b| < |a| * epsilon is false for
 *  all elements (non-deadly assertion). Required operators: <, >, -, *
 * @param value A value
 * @param container A container
 */
#define UNITTEST_NDASSERT_APPROXREL_NOT_IN_CONTAINER(value, container, epsilon) \
unittest::assertions::assert_approxrel_not_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), UNITTEST_NDAS);
/**
 * @brief Asserts that a value is not relatively approx. in a container up to
 *  some epsilon. The assertion succeeds if |a - b| < |a| * epsilon is false for
 *  all elements (non-deadly assertion). Required operators: <, >, -, *
 * @param value A value
 * @param container A container
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_APPROXREL_NOT_IN_CONTAINER_MSG(value, container, epsilon, message) \
unittest::assertions::assert_approxrel_not_in_container(value, container, epsilon, UNITTEST_SPOT, UNITTEST_CALL(value, container, epsilon), UNITTEST_NDAS, message);


/**
 * @brief Asserts that two containers are equal.
 *  Required operators: ==
 * @param expected The expected container
 * @param actual The actual container
 */
#define UNITTEST_ASSERT_EQUAL_CONTAINERS(expected, actual) \
unittest::assertions::assert_equal_containers(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual));
/**
 * @brief Asserts that two containers are equal.
 *  Required operators: ==
 * @param expected The expected container
 * @param actual The actual container
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_EQUAL_CONTAINERS_MSG(expected, actual, message) \
unittest::assertions::assert_equal_containers(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual), message);
/**
 * @brief Asserts that two containers are equal (non-deadly assertion).
 *  Required operators: ==
 * @param expected The expected container
 * @param actual The actual container
 */
#define UNITTEST_NDASSERT_EQUAL_CONTAINERS(expected, actual) \
unittest::assertions::assert_equal_containers(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual), UNITTEST_NDAS);
/**
 * @brief Asserts that two containers are equal (non-deadly assertion).
 *  Required operators: ==
 * @param expected The expected container
 * @param actual The actual container
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_EQUAL_CONTAINERS_MSG(expected, actual, message) \
unittest::assertions::assert_equal_containers(expected, actual, UNITTEST_SPOT, UNITTEST_CALL(expected, actual), UNITTEST_NDAS, message);
/**
 * @brief Asserts that two containers are not equal.
 *  Required operators: ==
 * @param first A container
 * @param second Another container
 */
#define UNITTEST_ASSERT_NOT_EQUAL_CONTAINERS(first, second) \
unittest::assertions::assert_not_equal_containers(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second));
/**
 * @brief Asserts that two containers are not equal.
 *  Required operators: ==
 * @param first A container
 * @param second Another container
 * @param message A user defined message
 */
#define UNITTEST_ASSERT_NOT_EQUAL_CONTAINERS_MSG(first, second, message) \
unittest::assertions::assert_not_equal_containers(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), message);
/**
 * @brief Asserts that two containers are not equal (non-deadly assertion).
 *  Required operators: ==
 * @param first A container
 * @param second Another container
 */
#define UNITTEST_NDASSERT_NOT_EQUAL_CONTAINERS(first, second) \
unittest::assertions::assert_not_equal_containers(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS);
/**
 * @brief Asserts that two containers are not equal (non-deadly assertion).
 *  Required operators: ==
 * @param first A container
 * @param second Another container
 * @param message A user defined message
 */
#define UNITTEST_NDASSERT_NOT_EQUAL_CONTAINERS_MSG(first, second, message) \
unittest::assertions::assert_not_equal_containers(first, second, UNITTEST_SPOT, UNITTEST_CALL(first, second), UNITTEST_NDAS, message);
