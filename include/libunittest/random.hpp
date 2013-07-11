#pragma once
#include <string>
#include <vector>
#include <random>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief
 */
template<typename T>
class random_object {
public:

    random_object()
        : seed_(1), generator_(seed_)
    {}

    virtual
    ~random_object()
    {}

    virtual void
    seed(int seed)
    {
        seed_ = seed;
        generator_.seed(seed_);
    }

    virtual T
    value() = 0;

protected:
    int seed_;
    std::mt19937 generator_;

};
/**
 * @brief
 */
template<typename T>
class random_int : public random_object<T> {
public:

    random_int(T maximum)
        : random_object<T>(), uniform_(0, maximum)
    {}

    random_int(T minimum,
               T maximum)
        : random_object<T>(), uniform_(minimum, maximum)
    {}

    T
    value()
    {
        return uniform_(this->generator_);
    }

private:
    std::uniform_int_distribution<T> uniform_;

};
/**
 * @brief
 */
template<typename T>
class random_real : public random_object<T> {
public:

    random_real(T maximum)
        : random_object<T>(), uniform_(0, maximum)
    {}

    random_real(T minimum,
                T maximum)
        : random_object<T>(), uniform_(minimum, maximum)
    {}

    T
    value()
    {
        return uniform_(this->generator_);
    }

private:
    std::uniform_real_distribution<T> uniform_;

};
/**
 * @brief
 */
template<typename T,
         typename Container>
class random_choice : public random_object<T> {
public:

    random_choice(const Container& container)
        : random_object<T>(), container_(container),
          uniform_(0, container_.size() - 1)
    {}

    T
    value()
    {
        const auto index = uniform_(this->generator_);
        long long count = 0;
        T result;
        for (auto& value : container_) {
            if (count==index) {
                result = value;
                break;
            }
            ++count;
        }
        return result;
    }

private:
    Container container_;
    std::uniform_int_distribution<long long> uniform_;

};
/**
 * @brief
 */
template<typename T,
         typename Container>
class random_container : public random_object<Container> {
public:

    random_container(random_choice<T, Container>& rand,
                     long long length)
        : random_object<Container>(),
          rand_(&rand),
          uniform_(length, length)
    {}

    random_container(random_choice<T, Container>& rand,
                     long long min_length,
                     long long max_length)
        : random_object<Container>(),
          rand_(&rand),
          uniform_(min_length, max_length)
    {}

    Container
    value()
    {
        const auto length = uniform_(this->generator_);
        std::vector<T> result;
        result.reserve(length);
        for (long long i=0; i<length; ++i)
            result.push_back(rand_->value());
        return {result.begin(), result.end()};
    }

private:
    random_choice<T, Container>* rand_;
    std::uniform_int_distribution<long long> uniform_;

};
/**
 * @brief
 */
template<typename Container>
class random_permutation : public random_object<Container> {
public:

    random_permutation(const Container& container)
        : random_object<Container>(),
          container_(container)
    {}

    Container
    value()
    {
        std::shuffle(std::begin(container_), std::end(container_), this->generator_);
        return container_;
    }

private:
    Container container_;

};

} // unittest
