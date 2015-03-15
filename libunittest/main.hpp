/**
 * @brief A portable C++ library for unit testing, http://libunittest.net
 *        Include this header to get the full libunittest functionality plus
 *        an automatic main function
 * @file main.hpp
 */
#pragma once
#include "unittest.hpp"
/**
 * @brief The main function
 * @param argc The number of arguments
 * @param argv The arguments
 * @returns A platform dependent program execution status: A success value if
 *  all tests succeed and an error value otherwise
 */
int main(int argc, char **argv);
