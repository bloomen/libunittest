/**
 * @brief Compiler specifics to get the current function name
 * @file func.hpp
 */
#pragma once

#if defined(_MSC_FULL_VER) && _MSC_FULL_VER < 180021114
/**
 * @brief Compiler specifics to get the current function name
 */
#define UNITTEST_FUNC __FUNCTION__
#else
/**
 * @brief Compiler specifics to get the current function name
 */
#define UNITTEST_FUNC __func__
#endif
