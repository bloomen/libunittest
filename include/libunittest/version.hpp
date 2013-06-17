#pragma once
#include <tuple>
#include <string>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Returns the libunittest version as a tuple
 * @returns The version as a tuple
 */
std::tuple<int,int,int>
get_version_tuple();
/**
 * @brief Returns the libunittest version as a string
 * @returns The version as a string
 */
std::string
get_version_string();

} // unittest
