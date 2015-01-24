/**
 * @brief A collection of test assertions
 * @file assertions.hpp
 */
#pragma once
#include "utilities.hpp"
#include "formatting.hpp"
#include "testsuite.hpp"
#include "testfailure.hpp"
#include "checkers.hpp"
#include "typetraits.hpp"
#include <string>
#include <regex>
#include <typeinfo>
#include <utility>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief A collection of assertions
 */
namespace assertions {
/**
 * @brief Asserts that a value is true.
 *  Operators needed: None
 * @param value A value
 * @param message If given, is appended to the default fail message
 */
template<typename T,
         typename... Args>
void
assert_true(T&& value,
            Args&&... message)
{
    if (!value) {
        const std::string text = "false is not true";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_false(T&& value,
             Args&&... message)
{
    if (value) {
        const std::string text = "true is not false";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_equal(T&& expected,
             U&& actual,
             Args&&... message)
{
    if (!(expected == actual)) {
        const std::string text = unittest::core::str(std::forward<T>(expected)) + " not equal to " + unittest::core::str(std::forward<U>(actual));
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_not_equal(T&& first,
                 U&& second,
                 Args&&... message)
{
    if (first == second) {
        const std::string text = unittest::core::str(std::forward<T>(first)) + " equal to " + unittest::core::str(std::forward<U>(second));
        unittest::fail(__func__, text, std::forward<Args>(message)...);
    }
}
/**
 * @brief Asserts that two values are approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon.
 *  Operators needed: <, >, -, <<
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
assert_approx_equal(T&& expected,
                    U&& actual,
                    V&& epsilon,
                    Args&&... message)
{
    unittest::core::check_epsilon(std::forward<V>(epsilon), __func__, std::forward<Args>(message)...);
    if (!unittest::core::is_approx_equal(std::forward<T>(expected), std::forward<U>(actual), std::forward<V>(epsilon))) {
        const std::string text = unittest::core::str(std::forward<T>(expected)) + " not approx. equal to " + unittest::core::str(std::forward<U>(actual)) + " with epsilon = " + unittest::core::str(std::forward<V>(epsilon));
        unittest::fail(__func__, text, std::forward<Args>(message)...);
    }
}
/**
 * @brief Asserts that two values are not approximately equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon is false.
 *  Operators needed: <, >, -, <<
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
assert_approx_not_equal(T&& first,
                        U&& second,
                        V&& epsilon,
                        Args&&... message)
{
    unittest::core::check_epsilon(std::forward<V>(epsilon), __func__, std::forward<Args>(message)...);
    if (unittest::core::is_approx_equal(std::forward<T>(first), std::forward<U>(second), std::forward<V>(epsilon))) {
        const std::string text = unittest::core::str(std::forward<T>(first)) + " approx. equal to " + unittest::core::str(std::forward<U>(second)) + " with epsilon = " + unittest::core::str(std::forward<V>(epsilon));
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_greater(T&& first,
               U&& second,
               Args&&... message)
{
    if (!(first > second)) {
        const std::string text = unittest::core::str(std::forward<T>(first)) + " not greater than " + unittest::core::str(std::forward<U>(second));
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_greater_equal(T&& first,
                     U&& second,
                     Args&&... message)
{
    if (first < second) {
        const std::string text = unittest::core::str(std::forward<T>(first)) + " not greater than or equal to " + unittest::core::str(std::forward<U>(second));
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_lesser(T&& first,
              U&& second,
              Args&&... message)
{
    if (!(first < second)) {
        const std::string text = unittest::core::str(std::forward<T>(first)) + " not lesser than " + unittest::core::str(std::forward<U>(second));
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_lesser_equal(T&& first,
                    U&& second,
                    Args&&... message)
{
    if (first > second) {
        const std::string text = unittest::core::str(std::forward<T>(first)) + " not lesser than or equal to " + unittest::core::str(std::forward<U>(second));
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_in_range(T&& value,
                U&& lower,
                V&& upper,
                Args&&... message)
{
    unittest::core::check_range_bounds(std::forward<U>(lower), std::forward<V>(upper), __func__, std::forward<Args>(message)...);
    if (!unittest::core::is_in_range(std::forward<T>(value), std::forward<U>(lower), std::forward<V>(upper))) {
        const std::string text = unittest::core::str(std::forward<T>(value)) + " not in range [" + unittest::core::str(std::forward<U>(lower)) + ", " + unittest::core::str(std::forward<V>(upper)) + "]";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_not_in_range(T&& value,
                    U&& lower,
                    V&& upper,
                    Args&&... message)
{
    unittest::core::check_range_bounds(std::forward<U>(lower), std::forward<V>(upper), __func__, std::forward<Args>(message)...);
    if (unittest::core::is_in_range(std::forward<T>(value), std::forward<U>(lower), std::forward<V>(upper))) {
        const std::string text = unittest::core::str(std::forward<T>(value)) + " in range [" + unittest::core::str(std::forward<U>(lower)) + ", " + unittest::core::str(std::forward<V>(upper)) + "]";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_in_container(T&& value,
                    Container&& container,
                    Args&&... message)
{
    if (!unittest::core::is_contained(std::forward<T>(value), std::forward<Container>(container))) {
        const std::string text = "value not in container";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_not_in_container(T&& value,
                        Container&& container,
                        Args&&... message)
{
    if (unittest::core::is_contained(std::forward<T>(value), std::forward<Container>(container))) {
        const std::string text = "value in container";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
    }
}
/**
 * @brief Asserts that a value is approx. in a container up to some epsilon.
 *  The assertion succeeds if |a - b| < epsilon for at least one element.
 *  Operators needed: <, >, -
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
assert_approx_in_container(T&& value,
                           Container&& container,
                           U&& epsilon,
                           Args&&... message)
{
    unittest::core::check_epsilon(std::forward<U>(epsilon), __func__, std::forward<Args>(message)...);
    if (!unittest::core::is_approx_contained(std::forward<T>(value), std::forward<Container>(container), std::forward<U>(epsilon))) {
        const std::string text = "value not approx. in container";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
    }
}
/**
 * @brief Asserts that a value is not approx. in a container up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon is false for all elements.
 *  Operators needed: <, >, -
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
assert_approx_not_in_container(T&& value,
                               Container&& container,
                               U&& epsilon,
                               Args&&... message)
{
    unittest::core::check_epsilon(std::forward<U>(epsilon), __func__, std::forward<Args>(message)...);
    if (unittest::core::is_approx_contained(std::forward<T>(value), std::forward<Container>(container), std::forward<U>(epsilon))) {
        const std::string text = "value approx. in container";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_equal_containers(Container1&& expected,
                        Container2&& actual,
                        Args&&... message)
{
    if (!unittest::core::is_containers_equal(std::forward<Container1>(expected), std::forward<Container2>(actual))) {
        const std::string text = "containers are not equal";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_not_equal_containers(Container1&& first,
                            Container2&& second,
                            Args&&... message)
{
    if (unittest::core::is_containers_equal(std::forward<Container1>(first), std::forward<Container2>(second))) {
        const std::string text = "containers are equal";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
    }
}
/**
 * @brief Asserts that two containers are approx. equal up to some epsilon.
 *  The assertion succeeds if |a - b| < epsilon for all pairs of elements.
 *  Operators needed: <, >, -
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
assert_approx_equal_containers(Container1&& expected,
                               Container2&& actual,
                               V&& epsilon,
                               Args&&... message)
{
    unittest::core::check_epsilon(std::forward<V>(epsilon), __func__, std::forward<Args>(message)...);
    if (!unittest::core::is_containers_approx_equal(std::forward<Container1>(expected), std::forward<Container2>(actual), std::forward<V>(epsilon))) {
        const std::string text = "containers are not approx. equal";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
    }
}
/**
 * @brief Asserts that two containers are not approx. equal up to some
 *  epsilon. The assertion succeeds if |a - b| < epsilon is false for at
 *  least one pair of elements.
 *  Operators needed: <, >, -
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
assert_approx_not_equal_containers(Container1&& first,
                                   Container2&& second,
                                   V&& epsilon,
                                   Args&&... message)
{
    unittest::core::check_epsilon(std::forward<V>(epsilon), __func__, std::forward<Args>(message)...);
    if (unittest::core::is_containers_approx_equal(std::forward<Container1>(first), std::forward<Container2>(second), std::forward<V>(epsilon))) {
        const std::string text = "containers are approx. equal";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_all_of(Container&& container,
              Functor&& condition,
              Args&&... message)
{
    if (!std::all_of(std::begin(container), std::end(container), std::forward<Functor>(condition))) {
        const std::string text = "Not all elements match the condition";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_not_all_of(Container&& container,
                  Functor&& condition,
                  Args&&... message)
{
    if (std::all_of(std::begin(container), std::end(container), std::forward<Functor>(condition))) {
        const std::string text = "All elements match the condition";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_any_of(Container&& container,
              Functor&& condition,
              Args&&... message)
{
    if (!std::any_of(std::begin(container), std::end(container), std::forward<Functor>(condition))) {
        const std::string text = "No element matches the condition";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_none_of(Container&& container,
               Functor&& condition,
               Args&&... message)
{
    if (!std::none_of(std::begin(container), std::end(container), std::forward<Functor>(condition))) {
        const std::string text = "At least one element matches the condition";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
                   Args&&... message)
{
    if (!unittest::core::is_regex_matched(string, regex)) {
        const std::string text = unittest::core::str(string) + " does not match the pattern " + unittest::core::str(regex);
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
                   Args&&... message)
{
    if (!unittest::core::is_regex_matched(string, regex)) {
        const std::string text = unittest::core::str(string) + " does not match the given pattern";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
                       Args&&... message)
{
    if (unittest::core::is_regex_matched(string, regex)) {
        const std::string text = unittest::core::str(string) + " matches the pattern " + unittest::core::str(regex);
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
                       Args&&... message)
{
    if (unittest::core::is_regex_matched(string, regex)) {
        const std::string text = unittest::core::str(string) + " matches the given pattern";
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_throw(Functor&& functor,
             Args&&... message)
{
    bool caught = false;
    if (unittest::core::testsuite::instance()->get_arguments().handle_exceptions) {
        try {
            functor();
        } catch (const Exception&) {
            caught = true;
        } catch (const std::exception& e) {
            const std::string text = unittest::join("An unexpected exception was thrown: ", typeid(e).name(), ": '", e.what(), "'");
            unittest::fail(__func__, text, std::forward<Args>(message)...);
        } catch (...) {
            const std::string text = "An unexpected, unknown exception was thrown";
            unittest::fail(__func__, text, std::forward<Args>(message)...);
        }
    } else {
        try {
            functor();
        } catch (const Exception&) {
            caught = true;
        }
    }
    if (!caught) {
        const std::string text = unittest::join("The exception was not thrown: ", typeid(Exception).name());
        unittest::fail(__func__, text, std::forward<Args>(message)...);
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
assert_no_throw(Functor&& functor,
                Args&&... message)
{
    if (unittest::core::testsuite::instance()->get_arguments().handle_exceptions) {
        try {
            functor();
        } catch (const std::exception& e) {
            const std::string text = unittest::join("An exception was thrown: ", typeid(e).name(), ": '", e.what(), "'");
            unittest::fail(__func__, text, std::forward<Args>(message)...);
        } catch (...) {
            const std::string text = "An unknown exception was thrown";
            unittest::fail(__func__, text, std::forward<Args>(message)...);
        }
    } else {
        functor();
    }
}

} // assertions
} // unittest
