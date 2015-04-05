/**
 * @brief Compiler specifics to get the current function name
 * @file func.hpp
 */
#pragma once

#ifdef _MSC_VER
#define UNITTEST_FUNC __FUNCTION__
#else
#define UNITTEST_FUNC __func__
#endif
