/**
 * @brief Functionality for compatibility between different compilers
 * @file compatibility.hpp
 */
#pragma once
/**
 * @brief Making __func__ available on visual studio
 */
#ifdef _MSC_VER
#define __func__ __FUNCTION__
#endif
