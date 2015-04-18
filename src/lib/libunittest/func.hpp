/**
 * @brief Compiler specifics to get the current function name
 * @file func.hpp
 */
#pragma once

#ifdef _MSC_VER
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
