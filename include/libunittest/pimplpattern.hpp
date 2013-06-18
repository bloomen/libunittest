#pragma once
#include <memory>
/**
 * @brief Unit testing in C++
 */
namespace unittest {

template<typename T>
struct implementation;

template<typename T>
class pimplpattern {
protected:
	std::unique_ptr<implementation<T>> impl_;

public:
	explicit pimplpattern(implementation<T> *imp);
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
