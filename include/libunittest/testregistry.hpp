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
 * @brief Internal functionality, not relevant for most users
 */
namespace internals {
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
        internals::testsuite::instance()->add_class_run(TestCase::run);
    }

};

} // internals
} // unittest
