/**
 * @brief The private implementation pattern
 * @file pimplpattern.hpp
 */
#pragma once
#include <memory>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Forward declaration of the implementation class
 */
template<typename T>
struct implementation;
/**
 * @brief A class defining the private implementation pattern
 */
template<typename T>
class pimplpattern {
protected:
    /**
     * @brief The pointer to implementation
     */
    std::shared_ptr<implementation<T>> impl_;

public:
    /**
     * @brief Constructor
     * @param imp A pointer to implementation
     */
    explicit
    pimplpattern(implementation<T> *imp);
    /**
     * @brief Destructor
     */
    virtual
    ~pimplpattern();
};

template<typename T>
pimplpattern<T>::pimplpattern(implementation<T> *imp)
    : impl_(imp)
{}

template<typename T>
pimplpattern<T>::~pimplpattern()
{}

} // unittest
