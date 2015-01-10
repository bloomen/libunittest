/**
 * @brief A collection of type traits
 * @file formatting.hpp
 */
#pragma once
#include <type_traits>
#include <iostream>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace core {

// A tag type returned by operator == for the any struct in this namespace
// when T does not support ==.
struct tag {};

// This type soaks up any implicit conversions and makes the following operator ==
// less preferred than any other such operator found via ADL.
struct any {
    // Conversion constructor for any type.
    template <class T>
    any(T const&);
};

// Fallback operator == for types T that don't support ==.
tag operator == (any const&, any const&);
tag operator > (any const&, any const&);
tag operator < (any const&, any const&);
tag operator << (std::ostream&, any const&);

// Two overloads to distinguish whether T supports a certain operator expression.
// The first overload returns a reference to a two-element character array and is chosen if
// T does not support the expression, such as ==, whereas the second overload returns a char
// directly and is chosen if T supports the expression. So using sizeof(check(<expression>))
// returns 2 for the first overload and 1 for the second overload.
typedef char yes;
typedef char (&no)[2];

no check(tag);

template <class T>
yes check(T const&);

template<typename T>
struct remove_cv_ref {
    typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
};

template<typename T>
struct is_equality_comparable {
    typedef typename remove_cv_ref<T>::type value_type;
    static value_type const& a;
    static value_type & b;
    static const bool value = sizeof(check(a == a)) == sizeof(yes) || sizeof(check(b == b)) == sizeof(yes);
};

template<typename T>
struct is_lesser_comparable {
    typedef typename remove_cv_ref<T>::type value_type;
    static value_type const& a;
    static value_type & b;
    static const bool value = sizeof(check(a < a)) == sizeof(yes) || sizeof(check(b < b)) == sizeof(yes);
};

template<typename T>
struct is_greater_comparable {
    typedef typename remove_cv_ref<T>::type value_type;
    static value_type const& a;
    static value_type & b;
    static const bool value = sizeof(check(a > a)) == sizeof(yes) || sizeof(check(b > b)) == sizeof(yes);
};

template<typename T>
struct is_output_streamable {
    typedef typename remove_cv_ref<T>::type value_type;
    static value_type const& a;
    static value_type & b;
    static const bool value = sizeof(check(std::cout << a)) == sizeof(yes) || sizeof(check(std::cout << b)) == sizeof(yes);
};

} // core
} // unittest
