#pragma once
#include <libunittest/testfailure.hpp>
#include <libunittest/utilities.hpp>
#include <string>
#include <regex>
#include <typeinfo>
#include <algorithm>
#include <functional>
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
class testcase {
public:
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

protected:
    /**
     * @brief Constructor
     */
    testcase()
        : context_(nullptr)
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
     * @brief Throws exception testfailure when called
     * @param message The exception message
     */
    virtual void
    fail(const std::string& message) const
    {
        throw testfailure(message);
    }
    /**
     * @brief Throws exception testfailure when called
     * @param assertion The name of the assertion
     * @param default_msg The default exception message
     * @param args An arbitrary number of arguments that are concatenated to a
     *  single string and are appended to the default message
     */
    template<typename... Args>
    void
    fail(const std::string& assertion,
         const std::string& default_msg,
         const Args&... args) const
    {
        fail(join(default_msg, " (", assertion, ") ", args...));
    }
    /**
     * @brief Asserts that a value is true
     * @param value A value
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename... Args>
    void
    assert_true(const T& value,
                const Args&... message) const
    {
        if (!value) {
            const std::string msg = "false is not true";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a value is false
     * @param value A value
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename... Args>
    void
    assert_false(const T& value,
                 const Args&... message) const
    {
        if (value) {
            const std::string msg = "true is not false";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that two values are equal
     * @param expected The expected value
     * @param actual The actual value
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename... Args>
    void
    assert_equal(const T& expected,
                 const U& actual,
                 const Args&... message) const
    {
        if (!(expected == actual)) {
            const std::string msg = _(expected) + " not equal to " + _(actual);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that two values are not equal
     * @param first A value
     * @param second Another value
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename... Args>
    void
    assert_not_equal(const T& first,
                     const U& second,
                     const Args&... message) const
    {
        if (first == second) {
            const std::string msg = _(first) + " equal to " + _(second);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that two values are approximately equal up to some
     *  epsilon. The assertions succeeds if |a - b| < epsilon
     * @param expected The expected value
     * @param actual The actual value
     * @param eps The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename V,
             typename... Args>
    void
    assert_approx_equal(const T& expected,
                        const U& actual,
                        const V& eps,
                        const Args&... message) const
    {
        if (!is_approx_equal(expected, actual, eps)) {
            const std::string msg = _(expected) + " not approx. equal to " + _(actual) + " with eps=" + _(eps);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that two values are not approximately equal up to some
     *  epsilon. The assertions succeeds if |a - b| < epsilon is false
     * @param first A value
     * @param second Another value
     * @param eps The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename V,
             typename... Args>
    void
    assert_approx_not_equal(const T& first,
                            const U& second,
                            const V& eps,
                            const Args&... message) const
    {
        if (is_approx_equal(first, second, eps)) {
            const std::string msg = _(first) + " approx. equal to " + _(second) + " with eps=" + _(eps);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that the first value is greater than the second
     * @param first A value
     * @param second Another value
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename... Args>
    void
    assert_greater(const T& first,
                   const U& second,
                   const Args&... message) const
    {
        if (!(first > second)) {
            const std::string msg = _(first) + " not greater than " + _(second);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that the first value is greater than or equal to the second
     * @param first A value
     * @param second Another value
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename... Args>
    void
    assert_greater_equal(const T& first,
                         const U& second,
                         const Args&... message) const
    {
        if (!(first >= second)) {
            const std::string msg = _(first) + " not greater than or equal to " + _(second);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that the first value is smaller than the second
     * @param first A value
     * @param second Another value
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename... Args>
    void
    assert_smaller(const T& first,
                   const U& second,
                   const Args&... message) const
    {
        if (!(first < second)) {
            const std::string msg = _(first) + " not smaller than " + _(second);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that the first value is smaller than or equal to the second
     * @param first A value
     * @param second Another value
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename... Args>
    void
    assert_smaller_equal(const T& first,
                         const U& second,
                         const Args&... message) const
    {
        if (!(first <= second)) {
            const std::string msg = _(first) + " not smaller than or equal to " + _(second);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a value is in a given range with excluding bounds
     * @param value A value
     * @param lower The lower bound
     * @param upper The upper bound
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename V,
             typename... Args>
    void
    assert_in_range(const T& value,
                    const U& lower,
                    const V& upper,
                    const Args&... message) const
    {
        if (!is_in_range(value, lower, upper)) {
            const std::string msg = _(value) + " not in range (" + _(lower) + ", " + _(upper) + ")";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a value is not in a given range with excluding bounds
     * @param value A value
     * @param lower The lower bound
     * @param upper The upper bound
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename V,
             typename... Args>
    void
    assert_not_in_range(const T& value,
                        const U& lower,
                        const V& upper,
                        const Args&... message) const
    {
        if (is_in_range(value, lower, upper)) {
            const std::string msg = _(value) + " in range (" + _(lower) + ", " + _(upper) + ")";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a value is in a container
     * @param value A value
     * @param container A container
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename Container,
             typename... Args>
    void
    assert_in_container(const T& value,
                        const Container& container,
                        const Args&... message) const
    {
        if (!is_contained(value, container)) {
            const std::string msg = _(value) + " not in container";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a value is not in a container
     * @param value A value
     * @param container A container
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename Container,
             typename... Args>
    void
    assert_not_in_container(const T& value,
                            const Container& container,
                            const Args&... message) const
    {
        if (is_contained(value, container)) {
            const std::string msg = _(value) + " in container";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a value is approx. in a container up to some epsilon.
     *  The assertion succeeds if |a - b| < epsilon for at least one element
     * @param value A value
     * @param container A container
     * @param eps The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename Container,
             typename U,
             typename... Args>
    void
    assert_approx_in_container(const T& value,
                               const Container& container,
                               const U& eps,
                               const Args&... message) const
    {
        if (!is_approx_contained(value, container, eps)) {
            const std::string msg = _(value) + " not approx. in container with eps=" + _(eps);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a value is not approx. in a container up to some
     *  epsilon. The assertion succeeds if |a - b| < epsilon is false for all elements
     * @param value A value
     * @param container A container
     * @param eps The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename Container,
             typename U,
             typename... Args>
    void
    assert_approx_not_in_container(const T& value,
                                   const Container& container,
                                   const U& eps,
                                   const Args&... message) const
    {
        if (is_approx_contained(value, container, eps)) {
            const std::string msg = _(value) + " approx. in container with eps=" + _(eps);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that two containers are equal
     * @param expected The expected container
     * @param actual The actual container
     * @param message If given, is appended to the default fail message
     */
    template<typename Container1,
             typename Container2,
             typename... Args>
    void
    assert_equal_containers(const Container1& expected,
                            const Container2& actual,
                            const Args&... message) const
    {
        if (!is_containers_equal(expected, actual)) {
            const std::string msg = "containers are not equal";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that two containers are not equal
     * @param first A container
     * @param second Another container
     * @param message If given, is appended to the default fail message
     */
    template<typename Container1,
             typename Container2,
             typename... Args>
    void
    assert_not_equal_containers(const Container1& first,
                                const Container2& second,
                                const Args&... message) const
    {
        if (is_containers_equal(first, second)) {
            const std::string msg = "containers are equal";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that two containers are approx. equal up to some epsilon.
     *  The assertion succeeds if |a - b| < epsilon for all pairs of elements
     * @param expected The expected container
     * @param actual The actual container
     * @param eps The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename Container1,
             typename Container2,
             typename V,
             typename... Args>
    void
    assert_approx_equal_containers(const Container1& expected,
                                   const Container2& actual,
                                   const V& eps,
                                   const Args&... message) const
    {
        if (!is_containers_approx_equal(expected, actual, eps)) {
            const std::string msg = "containers are not approx. equal with eps=" + _(eps);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that two containers are not approx. equal up to some
     *  epsilon. The assertion succeeds if |a - b| < epsilon is false for at least one
     *  pair of elements
     * @param expected The expected container
     * @param actual The actual container
     * @param eps The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename Container1,
             typename Container2,
             typename V,
             typename... Args>
    void
    assert_approx_not_equal_containers(const Container1& expected,
                                       const Container2& actual,
                                       const V& eps,
                                       const Args&... message) const
    {
        if (is_containers_approx_equal(expected, actual, eps)) {
            const std::string msg = "containers are approx. equal with eps=" + _(eps);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that all container elements match a given condition
     * @param container A container
     * @param condition A condition returning a boolean that can be applied to
     *  each container element
     * @param message If given, is appended to the default fail message
     */
    template<typename Container,
             typename Functor,
             typename... Args>
    void
    assert_all_of(const Container& container,
                  Functor condition,
                  const Args&... message) const
    {
        if (!std::all_of(std::begin(container), std::end(container), condition)) {
            const std::string msg = "Not all elements match the condition";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that not all container elements match a given condition
     * @param container A container
     * @param condition A condition returning a boolean that can be applied to
     *  each container element
     * @param message If given, is appended to the default fail message
     */
    template<typename Container,
             typename Functor,
             typename... Args>
    void
    assert_not_all_of(const Container& container,
                      Functor condition,
                      const Args&... message) const
    {
        if (std::all_of(std::begin(container), std::end(container), condition)) {
            const std::string msg = "All elements match the condition";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that any container element matches a given condition
     * @param container A container
     * @param condition A condition returning a boolean that can be applied to
     *  each container element
     * @param message If given, is appended to the default fail message
     */
    template<typename Container,
             typename Functor,
             typename... Args>
    void
    assert_any_of(const Container& container,
                  Functor condition,
                  const Args&... message) const
    {
        if (!std::any_of(std::begin(container), std::end(container), condition)) {
            const std::string msg = "No element matches the condition";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that none of the container elements match a given condition
     * @param container A container
     * @param condition A condition returning a boolean that can be applied to
     *  each container element
     * @param message If given, is appended to the default fail message
     */
    template<typename Container,
             typename Functor,
             typename... Args>
    void
    assert_none_of(const Container& container,
                   Functor condition,
                   const Args&... message) const
    {
        if (!std::none_of(std::begin(container), std::end(container), condition)) {
            const std::string msg = "At least one element matches the condition";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a string matches a regular expression
     * @param string A string
     * @param regex The regular expression
     * @param message If given, is appended to the default fail message
     */
    template<typename... Args>
    void
    assert_regex_match(const std::string& string,
                       const std::string& regex,
                       const Args&... message) const
    {
        if (!is_regex_matched(string, regex)) {
            const std::string msg = _(string) + " does not match the pattern " + _(regex);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a string matches a regular expression
     * @param string A string
     * @param regex The regular expression
     * @param message If given, is appended to the default fail message
     */
    template<typename... Args>
    void
    assert_regex_match(const std::string& string,
                       const std::regex& regex,
                       const Args&... message) const
    {
        if (!is_regex_matched(string, regex)) {
            const std::string msg = _(string) + " does not match the given pattern";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a string does not match a regular expression
     * @param string A string
     * @param regex The regular expression
     * @param message If given, is appended to the default fail message
     */
    template<typename... Args>
    void
    assert_not_regex_match(const std::string& string,
                           const std::string& regex,
                           const Args&... message) const
    {
        if (is_regex_matched(string, regex)) {
            const std::string msg = _(string) + " matches the pattern " + _(regex);
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a string does not match a regular expression
     * @param string A string
     * @param regex The regular expression
     * @param message If given, is appended to the default fail message
     */
    template<typename... Args>
    void
    assert_not_regex_match(const std::string& string,
                           const std::regex& regex,
                           const Args&... message) const
    {
        if (is_regex_matched(string, regex)) {
            const std::string msg = _(string) + " matches the given pattern";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a functor throws Exception
     * @param functor The functor
     * @param message If given, is appended to the default fail message
     */
    template<typename Exception,
             typename Functor,
             typename... Args>
    void
    assert_throw(Functor functor,
                 const Args&... message) const
    {
        bool caught = false;
        try {
            functor();
        } catch (const Exception&) {
            caught = true;
        }
        if (!caught) {
            const std::string msg = join("The exception was not thrown: ", typeid(Exception).name());
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Asserts that a functor does not throw any exception
     * @param functor The functor
     * @param message If given, is appended to the default fail message
     */
    template<typename Functor,
             typename... Args>
    void
    assert_no_throw(Functor functor,
                    const Args&... message) const
    {
        try {
            functor();
        } catch (const std::exception& e) {
            const std::string msg = join("An exception was thrown: ", typeid(e).name(), ": ", e.what());
            fail(__func__, msg, message...);
        } catch (...) {
            const std::string msg = "An unknown exception was thrown";
            fail(__func__, msg, message...);
        }
    }
    /**
     * @brief Utility function: Checks if two values are equal up to some epsilon
     * @param first A value
     * @param second Another value
     * @param eps The epsilon
     * @returns Whether the values are equal up to some epsilon
     */
    template<typename T,
             typename U,
             typename V>
    static bool
    is_approx_equal(const T& first,
                    const U& second,
                    const V& eps)
    {
        V diff = 0;
        if (first>second)
            diff = static_cast<V>(first - second);
        else if (first<second)
            diff = static_cast<V>(second - first);
        return diff < eps;
    }
    /**
     * @brief Checks whether the elements in two ranges are approx. equal
     *  up to some epsilon
     * @param first1 An input iterator
     * @param last1 An input iterator
     * @param first2 An input iterator
     * @param eps The epsilon
     * @returns Whether the elements in the two ranges are approx. equal
     */
    template <typename InputIterator1,
              typename InputIterator2,
              typename T>
    static bool
    is_approx_equal(InputIterator1 first1,
                    InputIterator1 last1,
                    InputIterator2 first2,
                    const T& eps)
    {
      while (first1!=last1) {
          if (!is_approx_equal(*first1, *first2, eps))
              return false;
          ++first1; ++first2;
      }
      return true;
    }
    /**
     * @brief Utility function: Checks if a value is in a given range.
     *  The bounds are excluding
     * @param value A value
     * @param lower The lower bound
     * @param upper The upper bound
     * @returns Whether the value is in a given range
     */
    template<typename T,
             typename U,
             typename V>
    static bool
    is_in_range(const T& value,
                const U& lower,
                const V& upper)
    {
        return value>lower && value<upper;
    }
    /**
     * @brief Utility function: Checks if a value is in a container
     * @param value A value
     * @param container A container
     * @returns Whether the value is in the container
     */
    template<typename T,
             typename Container>
    static bool
    is_contained(const T& value,
                 const Container& container)
    {
        auto first = std::begin(container);
        auto last = std::end(container);
        return std::find(first, last, value) != last;
    }
    /**
     * @brief Utility function: Checks if a value is approx. in a container
     *  up to some epsilon
     * @param value A value
     * @param container A container
     * @param eps The epsilon
     * @returns Whether the value is approx. in the container
     */
    template<typename T,
             typename Container,
             typename U>
    static bool
    is_approx_contained(const T& value,
                        const Container& container,
                        const U& eps)
    {
        auto first = std::begin(container);
        auto last = std::end(container);
        while (first!=last) {
            if (is_approx_equal(*first, value, eps)) return true;
            ++first;
        }
        return false;
    }
    /**
     * @brief Utility function: Checks if two containers are equal
     * @param first A container
     * @param second Another container
     * @returns Whether the containers are equal
     */
    template<typename Container1,
             typename Container2>
    static bool
    is_containers_equal(const Container1& first,
                        const Container2& second)
    {
        const bool equal_first = std::equal(std::begin(first), std::end(first),
                                            std::begin(second));
        const bool equal_second = std::equal(std::begin(second), std::end(second),
                                             std::begin(first));
        return equal_first && equal_second;
    }
    /**
     * @brief Utility function: Checks if two containers are approx. equal
     *  up to some epsilon
     * @param first A container
     * @param second Another container
     * @param eps The epsilon
     * @returns Whether the two containers are approx. equal
     */
    template<typename Container1,
             typename Container2,
             typename V>
    static bool
    is_containers_approx_equal(const Container1& first,
                               const Container2& second,
                               const V& eps)
    {
        const bool equal_first = is_approx_equal(std::begin(first), std::end(first),
                                                 std::begin(second), eps);
        const bool equal_second = is_approx_equal(std::begin(second), std::end(second),
                                                  std::begin(first), eps);
        return equal_first && equal_second;
    }
    /**
     * @brief Utility function: Checks if a value matches a regular expression
     * @param value A value
     * @param regex A regular expression
     * @returns Whether a value matches the regular expression
     */
    static bool
    is_regex_matched(const std::string& value,
                     const std::string& regex)
    {
        return std::regex_match(value, std::regex(regex));
    }
    /**
     * @brief Utility function: Checks if a value matches a regular expression
     * @param value A value
     * @param regex A regular expression
     * @returns Whether a value matches the regular expression
     */
    static bool
    is_regex_matched(const std::string& value,
                     const std::regex& regex)
    {
        return std::regex_match(value, regex);
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

    template<typename T>
    std::string
    _(const T& value) const
    {
        std::ostringstream stream;
        stream.precision(max_displayed_value_precision());
        stream << value;
        std::string result(stream.str());
        if (int(result.size())>max_displayed_string_length()) {
            result = result.substr(0, max_displayed_string_length());
        }
        return std::move("'" + result + "'");
    }

    TestContext *context_;
};

} // unittest
