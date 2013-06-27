#pragma once
#include <libunittest/utilities.hpp>
#include <libunittest/formatting.hpp>
#include <string>
#include <regex>
#include <typeinfo>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief A collection of assertions
 */
class assertions : public formatting {
public:
    /**
     * @brief Constructor
     */
	assertions();
    /**
     * @brief Destructor
     */
    virtual ~assertions();
    /**
     * @brief Throws exception testfailure with a given message
     * @param message The fail message
     */
    virtual void
    fail(const std::string& message) const;
    /**
     * @brief Builds a fail message from the parameters passed and calls
     * 	the fail(message) overload
     * @param assertion The name of the assertion
     * @param text The assertion text
     * @param args An arbitrary number of arguments that are concatenated
     * 	to a single string and are appended to the base message
     */
    template<typename... Args>
    void
    fail(const std::string& assertion,
         const std::string& text,
         const Args&... args) const
    {
        fail(join(make_fail_message(assertion, text), args...));
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
            const std::string text = "false is not true";
            fail(__func__, text, message...);
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
            const std::string text = "true is not false";
            fail(__func__, text, message...);
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
            const std::string text = _(expected) + " not equal to " + _(actual);
            fail(__func__, text, message...);
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
            const std::string text = _(first) + " equal to " + _(second);
            fail(__func__, text, message...);
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
            const std::string text = _(expected) + " not approx. equal to " + _(actual) + " with eps=" + _(eps);
            fail(__func__, text, message...);
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
            const std::string text = _(first) + " approx. equal to " + _(second) + " with eps=" + _(eps);
            fail(__func__, text, message...);
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
            const std::string text = _(first) + " not greater than " + _(second);
            fail(__func__, text, message...);
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
        if (first < second) {
            const std::string text = _(first) + " not greater than or equal to " + _(second);
            fail(__func__, text, message...);
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
            const std::string text = _(first) + " not smaller than " + _(second);
            fail(__func__, text, message...);
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
        if (first > second) {
            const std::string text = _(first) + " not smaller than or equal to " + _(second);
            fail(__func__, text, message...);
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
            const std::string text = _(value) + " not in range (" + _(lower) + ", " + _(upper) + ")";
            fail(__func__, text, message...);
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
            const std::string text = _(value) + " in range (" + _(lower) + ", " + _(upper) + ")";
            fail(__func__, text, message...);
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
            const std::string text = _(value) + " not in container";
            fail(__func__, text, message...);
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
            const std::string text = _(value) + " in container";
            fail(__func__, text, message...);
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
            const std::string text = _(value) + " not approx. in container with eps=" + _(eps);
            fail(__func__, text, message...);
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
            const std::string text = _(value) + " approx. in container with eps=" + _(eps);
            fail(__func__, text, message...);
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
            const std::string text = "containers are not equal";
            fail(__func__, text, message...);
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
            const std::string text = "containers are equal";
            fail(__func__, text, message...);
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
            const std::string text = "containers are not approx. equal with eps=" + _(eps);
            fail(__func__, text, message...);
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
            const std::string text = "containers are approx. equal with eps=" + _(eps);
            fail(__func__, text, message...);
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
            const std::string text = "Not all elements match the condition";
            fail(__func__, text, message...);
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
            const std::string text = "All elements match the condition";
            fail(__func__, text, message...);
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
            const std::string text = "No element matches the condition";
            fail(__func__, text, message...);
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
            const std::string text = "At least one element matches the condition";
            fail(__func__, text, message...);
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
            const std::string text = _(string) + " does not match the pattern " + _(regex);
            fail(__func__, text, message...);
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
            const std::string text = _(string) + " does not match the given pattern";
            fail(__func__, text, message...);
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
            const std::string text = _(string) + " matches the pattern " + _(regex);
            fail(__func__, text, message...);
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
            const std::string text = _(string) + " matches the given pattern";
            fail(__func__, text, message...);
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
            const std::string text = join("The exception was not thrown: ", typeid(Exception).name());
            fail(__func__, text, message...);
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
            const std::string text = join("An exception was thrown: ", typeid(e).name(), ": ", e.what());
            fail(__func__, text, message...);
        } catch (...) {
            const std::string text = "An unknown exception was thrown";
            fail(__func__, text, message...);
        }
    }

};

} // unittest
