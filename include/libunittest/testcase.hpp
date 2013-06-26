#pragma once
#include <libunittest/testassertions.hpp>
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
class testcase : public testassertions {
public:
    /**
     * @brief Constructor
     */
    testcase()
        : testassertions(), context_(nullptr)
    {}
    /**
     * @brief Destructor
     */
    virtual ~testcase()
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
     * @brief Returns the maximum displayed string length of a single object
     *  that is passed to any of the assertions
     * @returns The maximum displayed string length
     */
    virtual int
    max_displayed_string_length() const
    {
        return 100;
    }
    /**
     * @brief Returns the maximum displayed precision of numerical values that
     *  are passed to any of the assertions
     * @returns The maximum displayed value precision
     */
    virtual int
    max_displayed_value_precision() const
    {
        return 10;
    }
    /**
     * @brief Generates a fail message from an assertion name and text
     * @param assertion The name of the assertion
     * @param text The assertion text
     */
    virtual std::string
    make_fail_message(const std::string& assertion,
    				  const std::string& text) const
    {
    	return join(text, " (", assertion, ") ");
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
