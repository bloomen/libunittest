/**
 * @brief Compiler specific definitions of noexcept
 * @file noexcept.hpp
 */
#pragma once

#ifdef _MSC_VER
/**
 * @brief Compiler specific definitions of noexcept
 */
#define UNITTEST_NOEXCEPT throw()
/**
 * @brief Compiler specific definitions of noexcept(false)
 */
#define UNITTEST_NOEXCEPT_FALSE
#else
/**
 * @brief Compiler specific definitions of noexcept
 */
#define UNITTEST_NOEXCEPT noexcept
/**
 * @brief Compiler specific definitions of noexcept(false)
 */
#define UNITTEST_NOEXCEPT_FALSE noexcept(false)
#endif
