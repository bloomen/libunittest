/**
 * @brief A collection of helper macros
 * @file macros.hpp
 */
#pragma once
/**
 * @brief Registers a test class. To be called prior to UNITTEST_RUN
 * @param test_class The test class
 */
#define UNITTEST_CLASS(test_class) \
typedef test_class __test_class__; \
const std::string __test_class_name__ = #test_class;
/**
 * @brief A test run (thread-safe)
 * @param test_method The test method
 */
#define UNITTEST_RUN(test_method) \
unittest::testrun(&__test_class__::test_method, __test_class_name__, #test_method, -1.);
/**
 * @brief A test run (thread-safe)
 * @param test_method The test method
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define UNITTEST_RUN_TIME(test_method, timeout) \
unittest::testrun(&__test_class__::test_method, __test_class_name__, #test_method, timeout);
/**
 * @brief A test run with a test context (thread-safe)
 * @param test_context The test context
 * @param test_method The test method
 */
#define UNITTEST_RUNCXT(test_context, test_method) \
unittest::testrun(test_context, &__test_class__::test_method, __test_class_name__, #test_method, -1.);
/**
 * @brief A test run with a test context (thread-safe)
 * @param test_context The test context
 * @param test_method The test method
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define UNITTEST_RUNCXT_TIME(test_context, test_method, timeout) \
unittest::testrun(test_context, &__test_class__::test_method, __test_class_name__, #test_method, timeout);
/**
 * @brief Defines a string with info about the current file name
 *  and the current line number
 */
#define UNITTEST_SPOT \
unittest::join(" @", __FILE__, ":", __LINE__, ". ")
/**
 * @brief Joins two symbols. Just for internals
 * @param symbol1 A symbol
 * @param symbol2 Another symbol
 */
#define UNITTEST_JOIN(symbol1, symbol2) UNITTEST_DO_JOIN(symbol1, symbol2)
/**
 * @brief Joins two symbols. Just for internals
 * @param symbol1 A symbol
 * @param symbol2 Another symbol
 */
#define UNITTEST_DO_JOIN(symbol1, symbol2) symbol1##symbol2
/**
 * @brief Registers a test class
 * @param test_class The test class
 */
#define UNITTEST_REGISTER(test_class) \
static unittest::testregistry<test_class> UNITTEST_JOIN(registered_##test_class, __LINE__);
