/**
 * @brief The assertions class providing a collection of test assertions
 * @file assertions.hpp
 */
#pragma once
#include <libunittest/utilities.hpp>
#include <libunittest/formatting.hpp>
#include <libunittest/testsuite.hpp>
#include <string>
#include <regex>
#include <typeinfo>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace internals {
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
    virtual
    ~assertions();
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
        fail(join(make_displayed_fail_message(assertion, text), args...));
    }
    /**
     * @brief Asserts that a value is true.
     *  Operators needed: None
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
     * @brief Asserts that a value is false.
     *  Operators needed: None
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
     * @brief Asserts that two values are equal.
     *  Operators needed: ==, <<
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
            const std::string text = str(expected) + " not equal to " + str(actual);
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that two values are not equal.
     *  Operators needed: ==, <<
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
            const std::string text = str(first) + " equal to " + str(second);
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Checks if an epsilon is valid
     * @param epsilon The epsilon
     * @param caller The name of the caller
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename... Args>
    void
    check_epsilon(const T& epsilon,
                  const std::string& caller,
                  const Args&... message) const
    {
        if (!(epsilon > 0)) {
            const std::string text = "epsilon not greater than zero";
            fail(caller, text, message...);
        }
    }
    /**
     * @brief Asserts that two values are approximately equal up to some
     *  epsilon. The assertion succeeds if |a - b| < epsilon.
     *  Operators needed: <, >, <<
     * @param expected The expected value
     * @param actual The actual value
     * @param epsilon The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename V,
             typename... Args>
    void
    assert_approx_equal(const T& expected,
                        const U& actual,
                        const V& epsilon,
                        const Args&... message) const
    {
        check_epsilon(epsilon, __func__, message...);
        if (!is_approx_equal(expected, actual, epsilon)) {
            const std::string text = str(expected) + " not approx. equal to " + str(actual) + " with epsilon = " + str(epsilon);
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that two values are not approximately equal up to some
     *  epsilon. The assertion succeeds if |a - b| < epsilon is false.
     *  Operators needed: <, >, <<
     * @param first A value
     * @param second Another value
     * @param epsilon The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename V,
             typename... Args>
    void
    assert_approx_not_equal(const T& first,
                            const U& second,
                            const V& epsilon,
                            const Args&... message) const
    {
        check_epsilon(epsilon, __func__, message...);
        if (is_approx_equal(first, second, epsilon)) {
            const std::string text = str(first) + " approx. equal to " + str(second) + " with epsilon = " + str(epsilon);
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that the first value is greater than the second.
     *  Operators needed: >, <<
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
            const std::string text = str(first) + " not greater than " + str(second);
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that the first value is greater than or equal to the second.
     *  Operators needed: <, <<
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
            const std::string text = str(first) + " not greater than or equal to " + str(second);
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that the first value is lesser than the second.
     *  Operators needed: <, <<
     * @param first A value
     * @param second Another value
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename... Args>
    void
    assert_lesser(const T& first,
                  const U& second,
                  const Args&... message) const
    {
        if (!(first < second)) {
            const std::string text = str(first) + " not lesser than " + str(second);
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that the first value is lesser than or equal to the second.
     *  Operators needed: >, <<
     * @param first A value
     * @param second Another value
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename... Args>
    void
    assert_lesser_equal(const T& first,
                        const U& second,
                        const Args&... message) const
    {
        if (first > second) {
            const std::string text = str(first) + " not lesser than or equal to " + str(second);
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Checks if the range bounds are valid
     * @param lower The lower bound
     * @param upper The upper bound
     * @param caller The name of the caller
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename U,
             typename... Args>
    void
    check_range_bounds(const T& lower,
                       const U& upper,
                       const std::string& caller,
                       const Args&... message) const
    {
        if (lower > upper) {
            const std::string text = "lower bound cannot be greater than upper bound";
            fail(caller, text, message...);
        }
    }
    /**
     * @brief Asserts that a value is in a given range with included bounds.
     *  Operators needed: <, >, <<
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
        check_range_bounds(lower, upper, __func__, message...);
        if (!is_in_range(value, lower, upper)) {
            const std::string text = str(value) + " not in range [" + str(lower) + ", " + str(upper) + "]";
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that a value is not in a given range with included bounds.
     *  Operators needed: <, >, <<
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
        check_range_bounds(lower, upper, __func__, message...);
        if (is_in_range(value, lower, upper)) {
            const std::string text = str(value) + " in range [" + str(lower) + ", " + str(upper) + "]";
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that a value is in a container.
     *  Operators needed: ==
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
            const std::string text = "value not in container";
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that a value is not in a container.
     *  Operators needed: ==
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
            const std::string text = "value in container";
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that a value is approx. in a container up to some epsilon.
     *  The assertion succeeds if |a - b| < epsilon for at least one element.
     *  Operators needed: <, >
     * @param value A value
     * @param container A container
     * @param epsilon The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename Container,
             typename U,
             typename... Args>
    void
    assert_approx_in_container(const T& value,
                               const Container& container,
                               const U& epsilon,
                               const Args&... message) const
    {
        check_epsilon(epsilon, __func__, message...);
        if (!is_approx_contained(value, container, epsilon)) {
            const std::string text = "value not approx. in container";
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that a value is not approx. in a container up to some
     *  epsilon. The assertion succeeds if |a - b| < epsilon is false for all elements.
     *  Operators needed: <, >
     * @param value A value
     * @param container A container
     * @param epsilon The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename T,
             typename Container,
             typename U,
             typename... Args>
    void
    assert_approx_not_in_container(const T& value,
                                   const Container& container,
                                   const U& epsilon,
                                   const Args&... message) const
    {
        check_epsilon(epsilon, __func__, message...);
        if (is_approx_contained(value, container, epsilon)) {
            const std::string text = "value approx. in container";
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that two containers are equal.
     *  Operators needed: ==
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
     * @brief Asserts that two containers are not equal.
     *  Operators needed: ==
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
     *  The assertion succeeds if |a - b| < epsilon for all pairs of elements.
     *  Operators needed: <, >
     * @param expected The expected container
     * @param actual The actual container
     * @param epsilon The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename Container1,
             typename Container2,
             typename V,
             typename... Args>
    void
    assert_approx_equal_containers(const Container1& expected,
                                   const Container2& actual,
                                   const V& epsilon,
                                   const Args&... message) const
    {
        check_epsilon(epsilon, __func__, message...);
        if (!is_containers_approx_equal(expected, actual, epsilon)) {
            const std::string text = "containers are not approx. equal";
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that two containers are not approx. equal up to some
     *  epsilon. The assertion succeeds if |a - b| < epsilon is false for at
     *  least one pair of elements.
     *  Operators needed: <, >
     * @param first A container
     * @param second Another container
     * @param epsilon The epsilon
     * @param message If given, is appended to the default fail message
     */
    template<typename Container1,
             typename Container2,
             typename V,
             typename... Args>
    void
    assert_approx_not_equal_containers(const Container1& first,
                                       const Container2& second,
                                       const V& epsilon,
                                       const Args&... message) const
    {
        check_epsilon(epsilon, __func__, message...);
        if (is_containers_approx_equal(first, second, epsilon)) {
            const std::string text = "containers are approx. equal";
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that all container elements match a given condition.
     *  Operators needed: None
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
     * @brief Asserts that not all container elements match a given condition.
     *  Operators needed: None
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
     * @brief Asserts that any container element matches a given condition.
     *  Operators needed: None
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
     * @brief Asserts that none of the container elements match a given condition.
     *  Operators needed: None
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
     * @brief Asserts that a string matches a regular expression.
     *  Operators needed: <<
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
            const std::string text = str(string) + " does not match the pattern " + str(regex);
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that a string matches a regular expression.
     *  Operators needed: <<
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
            const std::string text = str(string) + " does not match the given pattern";
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that a string does not match a regular expression.
     *  Operators needed: <<
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
            const std::string text = str(string) + " matches the pattern " + str(regex);
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that a string does not match a regular expression.
     *  Operators needed: <<
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
            const std::string text = str(string) + " matches the given pattern";
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that a functor throws Exception.
     *  Operators needed: None
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
        if (testsuite::instance()->get_arguments().handle_exceptions()) {
            try {
                functor();
            } catch (const Exception&) {
                caught = true;
            } catch (const std::exception& e) {
                const std::string text = join("An unexpected exception was thrown: ", typeid(e).name(), ": '", e.what(), "'");
                fail(__func__, text, message...);
            } catch (...) {
                const std::string text = "An unexpected, unknown exception was thrown";
                fail(__func__, text, message...);
            }
        } else {
            try {
                functor();
            } catch (const Exception&) {
                caught = true;
            }
        }
        if (!caught) {
            const std::string text = join("The exception was not thrown: ", typeid(Exception).name());
            fail(__func__, text, message...);
        }
    }
    /**
     * @brief Asserts that a functor does not throw any exception.
     *  Operators needed: None
     * @param functor The functor
     * @param message If given, is appended to the default fail message
     */
    template<typename Functor,
             typename... Args>
    void
    assert_no_throw(Functor functor,
                    const Args&... message) const
    {
        if (testsuite::instance()->get_arguments().handle_exceptions()) {
            try {
                functor();
            } catch (const std::exception& e) {
                const std::string text = join("An exception was thrown: ", typeid(e).name(), ": '", e.what(), "'");
                fail(__func__, text, message...);
            } catch (...) {
                const std::string text = "An unknown exception was thrown";
                fail(__func__, text, message...);
            }
        } else {
            functor();
        }
    }

};

// Template specializations for the most common assertions

template<> void assertions::assert_true(const bool& value, const std::string& message) const;
template<> void assertions::assert_true(const char& value, const std::string& message) const;
template<> void assertions::assert_true(const short& value, const std::string& message) const;
template<> void assertions::assert_true(const int& value, const std::string& message) const;
template<> void assertions::assert_true(const long& value, const std::string& message) const;
template<> void assertions::assert_true(const long long& value, const std::string& message) const;
template<> void assertions::assert_true(const unsigned char& value, const std::string& message) const;
template<> void assertions::assert_true(const unsigned short& value, const std::string& message) const;
template<> void assertions::assert_true(const unsigned int& value, const std::string& message) const;
template<> void assertions::assert_true(const unsigned long& value, const std::string& message) const;
template<> void assertions::assert_true(const unsigned long long& value, const std::string& message) const;
template<> void assertions::assert_true(const float& value, const std::string& message) const;
template<> void assertions::assert_true(const double& value, const std::string& message) const;
template<> void assertions::assert_true(const long double& value, const std::string& message) const;

template<> void assertions::assert_true(const bool& value) const;
template<> void assertions::assert_true(const char& value) const;
template<> void assertions::assert_true(const short& value) const;
template<> void assertions::assert_true(const int& value) const;
template<> void assertions::assert_true(const long& value) const;
template<> void assertions::assert_true(const long long& value) const;
template<> void assertions::assert_true(const unsigned char& value) const;
template<> void assertions::assert_true(const unsigned short& value) const;
template<> void assertions::assert_true(const unsigned int& value) const;
template<> void assertions::assert_true(const unsigned long& value) const;
template<> void assertions::assert_true(const unsigned long long& value) const;
template<> void assertions::assert_true(const float& value) const;
template<> void assertions::assert_true(const double& value) const;
template<> void assertions::assert_true(const long double& value) const;

template<> void assertions::assert_false(const bool& value, const std::string& message) const;
template<> void assertions::assert_false(const char& value, const std::string& message) const;
template<> void assertions::assert_false(const short& value, const std::string& message) const;
template<> void assertions::assert_false(const int& value, const std::string& message) const;
template<> void assertions::assert_false(const long& value, const std::string& message) const;
template<> void assertions::assert_false(const long long& value, const std::string& message) const;
template<> void assertions::assert_false(const unsigned char& value, const std::string& message) const;
template<> void assertions::assert_false(const unsigned short& value, const std::string& message) const;
template<> void assertions::assert_false(const unsigned int& value, const std::string& message) const;
template<> void assertions::assert_false(const unsigned long& value, const std::string& message) const;
template<> void assertions::assert_false(const unsigned long long& value, const std::string& message) const;
template<> void assertions::assert_false(const float& value, const std::string& message) const;
template<> void assertions::assert_false(const double& value, const std::string& message) const;
template<> void assertions::assert_false(const long double& value, const std::string& message) const;

template<> void assertions::assert_false(const bool& value) const;
template<> void assertions::assert_false(const char& value) const;
template<> void assertions::assert_false(const short& value) const;
template<> void assertions::assert_false(const int& value) const;
template<> void assertions::assert_false(const long& value) const;
template<> void assertions::assert_false(const long long& value) const;
template<> void assertions::assert_false(const unsigned char& value) const;
template<> void assertions::assert_false(const unsigned short& value) const;
template<> void assertions::assert_false(const unsigned int& value) const;
template<> void assertions::assert_false(const unsigned long& value) const;
template<> void assertions::assert_false(const unsigned long long& value) const;
template<> void assertions::assert_false(const float& value) const;
template<> void assertions::assert_false(const double& value) const;
template<> void assertions::assert_false(const long double& value) const;

template<> void assertions::assert_equal(const bool& expected, const bool& actual, const std::string& message) const;
template<> void assertions::assert_equal(const char& expected, const char& actual, const std::string& message) const;
template<> void assertions::assert_equal(const short& expected, const short& actual, const std::string& message) const;
template<> void assertions::assert_equal(const int& expected, const int& actual, const std::string& message) const;
template<> void assertions::assert_equal(const long& expected, const long& actual, const std::string& message) const;
template<> void assertions::assert_equal(const long long& expected, const long long& actual, const std::string& message) const;
template<> void assertions::assert_equal(const unsigned char& expected, const unsigned char& actual, const std::string& message) const;
template<> void assertions::assert_equal(const unsigned short& expected, const unsigned short& actual, const std::string& message) const;
template<> void assertions::assert_equal(const unsigned int& expected, const unsigned int& actual, const std::string& message) const;
template<> void assertions::assert_equal(const unsigned long& expected, const unsigned long& actual, const std::string& message) const;
template<> void assertions::assert_equal(const unsigned long long& expected,const unsigned long long& actual, const std::string& message) const;
template<> void assertions::assert_equal(const float& expected, const float& actual, const std::string& message) const;
template<> void assertions::assert_equal(const double& expected, const double& actual, const std::string& message) const;
template<> void assertions::assert_equal(const long double& expected, const long double& actual, const std::string& message) const;
template<> void assertions::assert_equal(const std::string& expected, const std::string& actual, const std::string& message) const;

template<> void assertions::assert_equal(const bool& expected, const bool& actual) const;
template<> void assertions::assert_equal(const char& expected, const char& actual) const;
template<> void assertions::assert_equal(const short& expected, const short& actual) const;
template<> void assertions::assert_equal(const int& expected, const int& actual) const;
template<> void assertions::assert_equal(const long& expected, const long& actual) const;
template<> void assertions::assert_equal(const long long& expected, const long long& actual) const;
template<> void assertions::assert_equal(const unsigned char& expected, const unsigned char& actual) const;
template<> void assertions::assert_equal(const unsigned short& expected, const unsigned short& actual) const;
template<> void assertions::assert_equal(const unsigned int& expected, const unsigned int& actual) const;
template<> void assertions::assert_equal(const unsigned long& expected, const unsigned long& actual) const;
template<> void assertions::assert_equal(const unsigned long long& expected,const unsigned long long& actual) const;
template<> void assertions::assert_equal(const float& expected, const float& actual) const;
template<> void assertions::assert_equal(const double& expected, const double& actual) const;
template<> void assertions::assert_equal(const long double& expected, const long double& actual) const;
template<> void assertions::assert_equal(const std::string& expected, const std::string& actual) const;

template<> void assertions::assert_not_equal(const bool& first, const bool& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const char& first, const char& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const short& first, const short& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const int& first, const int& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const long& first, const long& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const long long& first, const long long& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const unsigned char& first, const unsigned char& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const unsigned short& first, const unsigned short& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const unsigned int& first, const unsigned int& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const unsigned long& first, const unsigned long& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const unsigned long long& first,const unsigned long long& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const float& first, const float& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const double& first, const double& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const long double& first, const long double& second, const std::string& message) const;
template<> void assertions::assert_not_equal(const std::string& first, const std::string& second, const std::string& message) const;

template<> void assertions::assert_not_equal(const bool& first, const bool& second) const;
template<> void assertions::assert_not_equal(const char& first, const char& second) const;
template<> void assertions::assert_not_equal(const short& first, const short& second) const;
template<> void assertions::assert_not_equal(const int& first, const int& second) const;
template<> void assertions::assert_not_equal(const long& first, const long& second) const;
template<> void assertions::assert_not_equal(const long long& first, const long long& second) const;
template<> void assertions::assert_not_equal(const unsigned char& first, const unsigned char& second) const;
template<> void assertions::assert_not_equal(const unsigned short& first, const unsigned short& second) const;
template<> void assertions::assert_not_equal(const unsigned int& first, const unsigned int& second) const;
template<> void assertions::assert_not_equal(const unsigned long& first, const unsigned long& second) const;
template<> void assertions::assert_not_equal(const unsigned long long& first,const unsigned long long& second) const;
template<> void assertions::assert_not_equal(const float& first, const float& second) const;
template<> void assertions::assert_not_equal(const double& first, const double& second) const;
template<> void assertions::assert_not_equal(const long double& first, const long double& second) const;
template<> void assertions::assert_not_equal(const std::string& first, const std::string& second) const;

} // internals
} // unittest
