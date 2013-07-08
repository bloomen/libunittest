#pragma once
/**
 * @brief Registers a test class. To be called prior to UNITTEST_RUN
 * @param klass The test class
 */
#define UNITTEST_CLASS(klass) \
typedef klass __unittest_class__; \
const std::string __unittest_class_name__ = #klass;
/**
 * @brief A test run (thread-safe)
 * @param method The test method
 */
#define UNITTEST_RUN(method) \
unittest::testrun(&__unittest_class__::method, __unittest_class_name__, #method);
/**
 * @brief A test run with a test context (thread-safe)
 * @param context The test context
 * @param method The test method
 */
#define UNITTEST_RUNCXT(context, method) \
unittest::testrun(context, &__unittest_class__::method, __unittest_class_name__, #method);
/**
 * @brief Defines a string with info about the current file name
 *  and the current line number
 */
#define UNITTEST_SPOT \
unittest::join(" @", __FILE__, ":", __LINE__, ". ")
