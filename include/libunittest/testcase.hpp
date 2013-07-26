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
 * @brief A placeholder for the absent of a test context
 */
class nocontext {};
/**
 * @brief The class from which to derive when implementing a test case. The
 *  test context is optional
 */
template<typename TestContext=nocontext>
class testcase : public assertions {
public:
    /**
     * @brief Constructor
     */
    testcase()
        : assertions(), context_(nullptr)
    {}
    /**
     * @brief Destructor
     */
    virtual
    ~testcase()
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
     * @brief Generates a displayed fail message from assertion name and text
     * @param assertion The name of the assertion
     * @param text The assertion text
     * @returns A displayed fail message
     */
    virtual std::string
    make_displayed_fail_message(const std::string& assertion,
                                const std::string& text) const
    {
        return join(text, " (", assertion, ") ");
    }
    /**
     * @brief Returns the maximum displayed string length
     * @returns The maximum displayed string length
     */
    virtual int
    max_displayed_string_length() const
    {
        return 100;
    }
    /**
     * @brief Returns the maximum displayed precision of numerical values
     * @returns The maximum displayed value precision
     */
    virtual int
    max_displayed_value_precision() const
    {
        return 10;
    }

private:

    template<typename ContextClass,
             typename TestCase>
    friend void
    testrun(ContextClass&,
            void (TestCase::*)(),
            const std::string&,
            const std::string&);

    void
    set_test_context(TestContext *context)
    {
        context_ = context;
    }

    TestContext *context_;
};

} // unittest
