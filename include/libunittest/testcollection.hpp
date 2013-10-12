/**
 * @brief A test collection
 * @file testcollection.hpp
 */
#pragma once
#include <string>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace internals {
/**
 * @brief A test collection
 */
class testcollection {
public:
    /**
     * @brief Constructor
     */
    testcollection();
    /**
     * @brief Destructor
     */
    virtual
    ~testcollection();
    /**
     * @brief Returns the collection name
     * @returns The collection name
     */
    virtual std::string
    get_name() const;
};

} // internals
} // unittest

/**
 * @brief The test collection type
 */
typedef unittest::internals::testcollection __testcollection_type__;