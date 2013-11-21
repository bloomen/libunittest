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
 * @brief Stores the test to be run and an optional test context.
 *  By using the ()-operator the test is executed.
 */
template<typename TestCase>
struct testfunctor;

} // internals

/**
 * @brief The class from which to derive when implementing a test case. The
 *  test context is optional
 */
template<typename TestContext=internals::notype>
class testcase : public internals::assertions {
public:
    /**
     * @brief The type of the optional test context
     */
    typedef TestContext context_type;
    /**
     * @brief Constructor
     */
    testcase()
        : context_(nullptr)
    {}
    /**
     * @brief This is called before each test run.
     */
    virtual void
    set_up()
    {}
    /**
     * @brief This is called after each test run. Called if set-up and
     *  actual test were successful.
     */
    virtual void
    tear_down()
    {}
    /**
     * @brief Destructor. Called after each test even in case of error in
     *  set-up or actual test.
     */
    virtual
    ~testcase()
    {}
    /**
     * @brief Returns a pointer to the optional test context
     * @returns A pointer to the test context, nullptr if not defined
     */
    virtual context_type*
    get_test_context() const final
    {
        return context_;
    }

private:

    template<typename TestCase>
    friend struct internals::testfunctor;

    void
    set_test_context(context_type *context)
    {
        context_ = context;
    }

    context_type *context_;
};

} // unittest
