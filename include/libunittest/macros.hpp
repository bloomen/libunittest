#pragma once
/**
 * @brief A test run (thread-safe)
 * @param klass The test class
 * @param method The test method
 */
#define UNITTEST_RUN(klass, method) \
        unittest::testrun(&klass::method, #klass, #method);
/**
 * @brief A test run with a test context (thread-safe)
 * @param context The test context
 * @param klass The test class
 * @param method The test method
 */
#define UNITTEST_RUNCXT(context, klass, method) \
        unittest::testrun(context, &klass::method, #klass, #method);
/**
 * @brief Defines a string with info about the current file name
 *  and the current line number
 */
#define UNITTEST_SPOT \
        unittest::join(" @", __FILE__, ":", __LINE__, ". ")
