/**
 * @brief A collection of type traits
 * @file formatting.hpp
 */
#pragma once
#include "noexcept.hpp"
#include <type_traits>
#include <iostream>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief A utility class to indicate 'no type' property
 */
class notype {
	notype() {}
	virtual ~notype() UNITTEST_NOEXCEPT_FALSE {}
};
/**
 * @brief A utility class to indicate 'some type' property
 */
struct sometype {
	sometype() {}
	virtual ~sometype() UNITTEST_NOEXCEPT_FALSE {}
};
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace core {
/**
 * @brief Used to indicate yes in conjunction with sizeof
 */
typedef char yes;
/**
 * @brief Used to indicate no in conjunction with sizeof
 */
typedef char (&no)[2];
/**
 * @brief Overload for when a type supports a certain operation
 * @return The yes type
 */
template<typename T>
unittest::core::yes static_check(T const&);
/**
 * @brief Overload for when a type does not support a certain operation
 * @return The no type
 */
unittest::core::no static_check(unittest::sometype);
/**
 * @brief Removes cv-qualifiers and reference
 */
template<typename T>
struct remove_cv_ref {
	/**
	 * @brief The result type
	 */
    typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
};
/**
 * A type for implicit conversions accepting any type
 */
struct convert_any {
	/**
	 * @brief Constructor
	 */
    template<typename T>
    convert_any(T const&);
};
/**
 * @brief Fallback operator for types that do not support <<
 * @return Some type
 */
unittest::sometype
operator<<(std::ostream&,
		   unittest::core::convert_any const&);
/**
 * @brief Evaluates whether type T is output streamable, i.e. implements
 * 	operator <<
 */
template<typename T>
class is_output_streamable {
    typedef typename unittest::core::remove_cv_ref<T>::type value_type;
    static value_type const& a;
    static value_type & b;
public:
	/**
	 * @brief The result value
	 */
    static const bool value = sizeof(unittest::core::static_check(std::cout << a)) == sizeof(unittest::core::yes) ||
    						  sizeof(unittest::core::static_check(std::cout << b)) == sizeof(unittest::core::yes);
};
/**
 * @brief Evaluates whether type T is output streamable, i.e. implements
 * 	operator <<. Spec. for void
 */
template<>
class is_output_streamable<void> {
public:
	/**
	 * @brief The result value
	 */
	static const bool value = false;
};

} // core
} // unittest
