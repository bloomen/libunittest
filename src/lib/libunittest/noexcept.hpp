/**
 * @brief Compiler specific definitions of noexcept
 * @file noexcept.hpp
 */
#pragma once

#ifdef _MSC_VER
#include <yvals.h>
#define UNITTEST_NOEXCEPT _NOEXCEPT
#define UNITTEST_NOEXCEPT_FALSE
#else
#define UNITTEST_NOEXCEPT noexcept
#define UNITTEST_NOEXCEPT_FALSE noexcept(false)
#endif
