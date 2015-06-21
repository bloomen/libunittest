/**
 * @brief A portable C++ library for unit testing, http://libunittest.net
 * @file all.hpp
 */
#pragma once

/**
 * @brief Set to 0 to exclude an automatic main function
 */
#define UNITTEST_MAIN_FUNC 1
/**
 * @brief Set to 0 to disable macro shortcuts
 */
#define UNITTEST_MACRO_SHORT 1
/**
 * @brief Set to 0 to disable assert shortcuts
 */
#define UNITTEST_ASSERT_SHORT 1

#if UNITTEST_MAIN_FUNC==1
#include "main.hpp"
#endif

#if UNITTEST_MACRO_SHORT==1
#include "shortcuts.hpp"
#endif

#if UNITTEST_ASSERT_SHORT==1
#include "assertshortcuts.hpp"
#endif
