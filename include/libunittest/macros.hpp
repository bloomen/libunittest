/**
 * @brief A collection of helper macros
 * @file macros.hpp
 */
#pragma once
/**
 * @brief Registers a test class within TestCase::run().
 *  To be called prior to UNITTEST_RUN
 * @param test_class The test class
 */
#define UNITTEST_CLASS(test_class) \
typedef test_class __test_class__;
/**
 * @brief A test run
 * @param test_method The test method
 */
#define UNITTEST_RUN(test_method) \
UNITTEST_RUN_TIME(test_method, -1.)
/**
 * @brief A test run
 * @param test_method The test method
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_RUN_SKIP(test_method, skip_message) \
UNITTEST_RUN_TIME_SKIP(test_method, -1., skip_message)
/**
 * @brief A test run
 * @param test_method The test methodmessage
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define UNITTEST_RUN_TIME(test_method, timeout) \
unittest::testrun(&__test_class__::test_method, "", #test_method, timeout, false, "");
/**
 * @brief A test run
 * @param test_method The test methodmessage
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_RUN_TIME_SKIP(test_method, timeout, skip_message) \
unittest::testrun(&__test_class__::test_method, "", #test_method, timeout, true, skip_message);
/**
 * @brief A test run with a test context
 * @param test_context The test context
 * @param test_method The test method
 */
#define UNITTEST_RUNCXT(test_context, test_method) \
UNITTEST_RUNCXT_TIME(test_context, test_method, -1.)
/**
 * @brief A skipped test run with a test context
 * @param test_context The test context
 * @param test_method The test method
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_RUNCXT_SKIP(test_context, test_method, skip_message) \
UNITTEST_RUNCXT_TIME_SKIP(test_context, test_method, -1., skip_message)
/**
 * @brief A test run with a test context
 * @param test_context The test context
 * @param test_method The test method
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define UNITTEST_RUNCXT_TIME(test_context, test_method, timeout) \
unittest::testrun(test_context, &__test_class__::test_method, "", #test_method, timeout, false, "");
/**
 * @brief A skipped test run with a test context
 * @param test_context The test context
 * @param test_method The test method
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_RUNCXT_TIME_SKIP(test_context, test_method, timeout, skip_message) \
unittest::testrun(test_context, &__test_class__::test_method, "", #test_method, timeout, true, skip_message);
/**
 * @brief Defines a string with info about the current file name
 *  and the current line number
 */
#define UNITTEST_SPOT \
unittest::internals::string_of_file_and_line(__FILE__, __LINE__)
/**
 * @brief Logs info for the current test
 */
#define UNITTEST_TESTINFO(...) \
unittest::internals::testsuite::instance()->log_text(this->get_test_id(), unittest::join(__VA_ARGS__));
/**
 * @brief Joins two symbols. Just for internals
 * @param symbol1 A symbol
 * @param symbol2 Another symbol
 */
#define __UNITTEST_JOIN(symbol1, symbol2) \
__UNITTEST_DO_JOIN(symbol1, symbol2)
/**
 * @brief Joins two symbols. Just for internals
 * @param symbol1 A symbol
 * @param symbol2 Another symbol
 */
#define __UNITTEST_DO_JOIN(symbol1, symbol2) \
symbol1##symbol2
/**
 * @brief Registers a test class at the global registry
 */
#define UNITTEST_REGISTER(...) \
static unittest::internals::testregistry<__VA_ARGS__> __UNITTEST_JOIN(__registered_at_, __LINE__)(#__VA_ARGS__);
/**
 * @brief A test collection
 * @param name The name of the test collection
 */
#define UNITTEST_COLLECTION(name) \
namespace collection_##name { \
    struct collection_child final : unittest::internals::testcollection { \
        std::string \
        get_name() const override \
        { \
            return #name; \
        } \
    }; \
    typedef collection_child __testcollection_type__; \
} \
namespace collection_##name
/**
 * @brief Sets up a plain test
 * @param test_name The name of the test
 */
#define UNITTEST_TEST(test_name) \
UNITTEST_TEST_TIME(test_name, -1.)
/**
 * @brief Sets up a plain test
 * @param test_name The name of the test
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_TEST_SKIP(test_name, skip_message) \
UNITTEST_TEST_TIME_SKIP(test_name, -1., skip_message)
/**
 * @brief Sets up a plain test with a timeout
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define UNITTEST_TEST_TIME(test_name, timeout) \
__UNITTEST_TEST_PLAIN(unittest::internals::sometype, test_name, timeout, false, "")
/**
 * @brief Sets up a plain test with a timeout
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_TEST_TIME_SKIP(test_name, timeout, skip_message) \
__UNITTEST_TEST_PLAIN(unittest::internals::sometype, test_name, timeout, true, skip_message)
/**
 * @brief Sets up a plain test with a test fixture
 * @param fixture The test fixture
 * @param test_name The name of the test
 */
#define UNITTEST_TEST_FIXTURE(fixture, test_name) \
UNITTEST_TEST_FIXTURE_TIME(fixture, test_name, -1.)
/**
 * @brief Sets up a plain test with a test fixture
 * @param fixture The test fixture
 * @param test_name The name of the test
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_TEST_FIXTURE_SKIP(fixture, test_name, skip_message) \
UNITTEST_TEST_FIXTURE_TIME_SKIP(fixture, test_name, -1., skip_message)
/**
 * @brief Sets up a plain test with a test fixture and timeout
 * @param fixture The test fixture
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define UNITTEST_TEST_FIXTURE_TIME(fixture, test_name, timeout) \
__UNITTEST_TEST_PLAIN(fixture, test_name, timeout, false, "")
/**
 * @brief Sets up a skipped plain test with a test fixture and timeout
 * @param fixture The test fixture
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_TEST_FIXTURE_TIME_SKIP(fixture, test_name, timeout, skip_message) \
__UNITTEST_TEST_PLAIN(fixture, test_name, timeout, true, skip_message)
/**
 * @brief Sets up a generic plain test. Only for internals
 * @param fixture The test fixture
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @param skipped Whether this test run is skipped
 * @param skip_message A message explaining why the test is skipped
 */
#define __UNITTEST_TEST_PLAIN(fixture, test_name, timeout, skipped, skip_message) \
struct test_name : unittest::testcase<>, fixture { \
    test_name() : fixture() {} \
    static void run() \
    { \
        __testcollection_type__ collection; \
        unittest::testrun(&test_name::test, collection.get_name(), "", timeout, skipped, skip_message); \
    } \
    void test(); \
}; \
UNITTEST_REGISTER(test_name) \
void test_name::test()
/**
 * @brief Sets up a templated test
 * @param test_name The name of the test
 */
#define UNITTEST_TEST_TPL(test_name) \
UNITTEST_TEST_TPL_TIME(test_name, -1.)
/**
 * @brief Sets up a skipped templated test
 * @param test_name The name of the test
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_TEST_TPL_SKIP(test_name, skip_message) \
UNITTEST_TEST_TPL_TIME_SKIP(test_name, -1., skip_message)
/**
 * @brief Sets up a templated test with a timeout
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define UNITTEST_TEST_TPL_TIME(test_name, timeout) \
__UNITTEST_TEST_TPL(unittest::internals::sometype, test_name, timeout, false, "")
/**
 * @brief Sets up a skipped templated test with a timeout
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_TEST_TPL_TIME_SKIP(test_name, timeout, skip_message) \
__UNITTEST_TEST_TPL(unittest::internals::sometype, test_name, timeout, true, skip_message)
/**
 * @brief Sets up a templated test with a test fixture
 * @param fixture The test fixture
 * @param test_name The name of the test
 */
#define UNITTEST_TEST_TPL_FIXTURE(fixture, test_name) \
UNITTEST_TEST_TPL_FIXTURE_TIME(fixture, test_name, -1.)
/**
 * @brief Sets up a skipped templated test with a test fixture
 * @param fixture The test fixture
 * @param test_name The name of the test
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_TEST_TPL_FIXTURE_SKIP(fixture, test_name, skip_message) \
UNITTEST_TEST_TPL_FIXTURE_TIME_SKIP(fixture, test_name, -1., skip_message)
/**
 * @brief Sets up a templated test with a test fixture and timeout
 * @param fixture The test fixture
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 */
#define UNITTEST_TEST_TPL_FIXTURE_TIME(fixture, test_name, timeout) \
__UNITTEST_TEST_TPL(fixture, test_name, timeout, false, "")
/**
 * @brief Sets up a skipped templated test with a test fixture and timeout
 * @param fixture The test fixture
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @param skip_message A message explaining why the test is skipped
 */
#define UNITTEST_TEST_TPL_FIXTURE_TIME_SKIP(fixture, test_name, timeout, skip_message) \
__UNITTEST_TEST_TPL(fixture, test_name, timeout, true, skip_message)
/**
 * @brief Sets up a generic templated test. Only for internals
 * @param fixture The test fixture
 * @param test_name The name of the test
 * @param timeout The maximum allowed run time in seconds (ignored if <= 0)
 * @param skipped Whether this test run is skipped
 * @param skip_message A message explaining why the test is skipped
 */
#define __UNITTEST_TEST_TPL(fixture, test_name, timeout, skipped, skip_message) \
template<typename Type1, typename Type2=unittest::internals::notype, typename Type3=unittest::internals::notype, typename Type4=unittest::internals::notype, typename Type5=unittest::internals::notype> \
struct test_name : unittest::testcase<>, fixture { \
    test_name() : fixture() {} \
    static void run() \
    { \
        __testcollection_type__ collection; \
        unittest::testrun(&test_name::test, collection.get_name(), "", timeout, skipped, skip_message); \
    } \
    void test(); \
}; \
template<typename Type1, typename Type2, typename Type3, typename Type4, typename Type5> \
void test_name<Type1,Type2,Type3,Type4,Type5>::test()
