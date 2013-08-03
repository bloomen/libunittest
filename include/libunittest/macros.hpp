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
unittest::testrun(&__test_class__::test_method, __test_class_name__, #test_method, 0);
/**
 * @brief A test run (thread-safe)
 * @param test_method The test method
 * @param time_out The maximum allowed run time in seconds (ignored if <= 0)
 */
#define UNITTEST_RUN_TIME(test_method, time_out) \
unittest::testrun(&__test_class__::test_method, __test_class_name__, #test_method, time_out);
/**
 * @brief A test run with a test context (thread-safe)
 * @param test_context The test context
 * @param test_method The test method
 */
#define UNITTEST_RUNCXT(test_context, test_method) \
unittest::testrun(test_context, &__test_class__::test_method, __test_class_name__, #test_method, 0);
/**
 * @brief A test run with a test context (thread-safe)
 * @param test_context The test context
 * @param test_method The test method
 * @param time_out The maximum allowed run time in seconds (ignored if <= 0)
 */
#define UNITTEST_RUNCXT_TIME(test_context, test_method, time_out) \
unittest::testrun(test_context, &__test_class__::test_method, __test_class_name__, #test_method, time_out);
/**
 * @brief Defines a string with info about the current file name
 *  and the current line number
 */
#define UNITTEST_SPOT \
unittest::join(" @", __FILE__, ":", __LINE__, ". ")
