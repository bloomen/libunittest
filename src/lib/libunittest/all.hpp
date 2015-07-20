/**
 * @brief A portable C++ library for unit testing, http://libunittest.net
 * @file all.hpp
 */
#pragma once
#include "unittest.hpp"

/**
 * @brief Set to 0 to not include an automatic main function
 */
#ifndef UNITTEST_MAIN_FUNC
#define UNITTEST_MAIN_FUNC 1
#endif
/**
 * @brief Set to 0 to disable assert shortcuts
 */
#ifndef UNITTEST_ASSERT_SHORT
#define UNITTEST_ASSERT_SHORT 1
#endif
/**
 * @brief Set to 0 to disable miscellaneous macro shortcuts
 */
#ifndef UNITTEST_MACRO_SHORT
#define UNITTEST_MACRO_SHORT 1
#endif

#if UNITTEST_MAIN_FUNC==1
#include "main.hpp"
#endif

#if UNITTEST_ASSERT_SHORT==1
#include "assertshortcuts.hpp"
#endif

#if UNITTEST_MACRO_SHORT==1
#include "shortcuts.hpp"
#endif
