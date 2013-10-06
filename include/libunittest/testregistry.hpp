/**
 * @brief Registering test runs
 * @file testregistry.hpp
 */
#pragma once
#include <libunittest/testsuite.hpp>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Registers the static run method of a test class at the testsuite
 */
template<typename TestCase>
class testregistry {
public:
    /**
     * @brief Constructor
     */
    testregistry()
    {
        testsuite::instance()->add_test_run(TestCase::run);
    }

};

} // unittest
