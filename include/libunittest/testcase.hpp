/**
 * @brief The testcase class from which to derive when implementing a test class
 * @file testcase.hpp
 */
#pragma once
#include <libunittest/assertions.hpp>
#include <string>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace internals {
/**
 * @brief A test run within a test context providing
 *  the ()-operator to run the test
 */
template<typename TestCase,
         typename ContextClass>
struct testrun_context;

} // internals

/**
 * @brief The class from which to derive when implementing a test case. The
 *  test context is optional
 */
template<typename TestContext=internals::notype>
class testcase : public internals::assertions {
public:
    /**
     * @brief Constructor
     */
    testcase()
        : context_(nullptr)
    {}
    /**
     * @brief Destructor
     */
    virtual
    ~testcase()
    {}
    /**
     * @brief This is called before each test run. By default, it does not do
     *  anything
     */
    virtual void
    set_up()
    {}
    /**
     * @brief This is called after each test run. By default, it does not do
     *  anything
     */
    virtual void
    tear_down()
    {}
    /**
     * @brief Returns a pointer to the optional test context
     * @returns A pointer to the test context, nullptr if not defined
     */
    TestContext*
    get_test_context() const
    {
        return context_;
    }

private:

    template<typename TestCase,
             typename ContextClass>
    friend struct internals::testrun_context;

    void
    set_test_context(TestContext *context)
    {
        context_ = context;
    }

    TestContext *context_;
};

} // unittest
