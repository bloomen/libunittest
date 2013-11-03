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
     * @param class_name The name of the test class
     */
    testregistry(const std::string& class_name)
    {
        auto suite = internals::testsuite::instance();
        suite->add_class_run(TestCase::run);
        suite->add_class_map(typeid(TestCase).name(), class_name);
    }

};

} // internals
} // unittest
