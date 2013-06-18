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
	std::unique_ptr<implementation<T>> impl_;

public:
	/**
	 * @brief Constructor
	 * @param imp A pointer to the concrete implementation class
	 */
	explicit pimplpattern(implementation<T> *imp);
	/**
	 * @brief Destructor
	 */
	virtual ~pimplpattern();
};

template<typename T>
pimplpattern<T>::pimplpattern(implementation<T> *imp)
	: impl_(imp)
{}

template<typename T>
pimplpattern<T>::~pimplpattern()
{}

} // unittest
