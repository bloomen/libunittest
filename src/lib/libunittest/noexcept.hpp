/**
 * @brief Compiler specific definitions of noexcept
 * @file noexcept.hpp
 */
#pragma once

#ifdef _MSC_VER
#define UNITTEST_NOEXCEPT throw()
#define UNITTEST_NOEXCEPT_FALSE
#else
#define UNITTEST_NOEXCEPT noexcept
#define UNITTEST_NOEXCEPT_FALSE noexcept(false)
#endif
