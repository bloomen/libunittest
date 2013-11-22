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
 * @brief Registers a test class at the testsuite
 * @param class_name The name of the test class
 */
template<typename TestCase>
void
register_class(const std::string& class_name)
{
    auto suite = internals::testsuite::instance();
    suite->add_class_run(TestCase::run);
    suite->add_class_map(internals::get_type_id<TestCase>(), class_name);
}
/**
 * @brief Registers a test class at the testsuite
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
        register_class<TestCase>(class_name);
    }
};

} // internals
} // unittest
