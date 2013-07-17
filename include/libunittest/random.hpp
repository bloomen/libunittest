#pragma once
#include <vector>
#include <random>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief A random object
 */
template<typename T>
class random_object {
public:
    /**
     * @brief Constructor initializing the Mersenne-Twister generator
     *  with a default random seed of one
     */
    random_object()
        : generator_(1)
    {}
    /**
     * @brief Destructor
     */
    virtual
    ~random_object()
    {}
    /**
     * @brief Supposed to return a random value
     * @returns A random value
     */
    virtual T
    value() = 0;
    /**
     * @brief Sets a new random seed
     * @param seed The random seed
     */
    void
    seed(int seed)
    {
        generator_.seed(seed);
    }

protected:
    std::mt19937&
    gen()
    {
        return generator_;
    }

    std::mt19937 generator_;

};
/**
 * @brief A random integer
 */
template<typename T=int>
class random_int : public random_object<T> {
public:
    /**
     * @brief Constructor, range: [0, 1]
     */
    random_int()
        : random_object<T>(), distribution_(0, 1)
    {}
    /**
     * @brief Constructor, range: [0, maximum]
     * @param maximum The upper bound (including)
     */
    random_int(const T& maximum)
        : random_object<T>(), distribution_(0, maximum)
    {}
    /**
     * @brief Constructor, range: [minimum, maximum]
     * @param minimum The lower bound (including)
     * @param maximum The upper bound (including)
     */
    random_int(const T& minimum,
               const T& maximum)
        : random_object<T>(), distribution_(minimum, maximum)
    {}
    /**
     * @brief Returns a random integer
     * @returns A random integer
     */
    T
    value()
    {
        return distribution_(this->gen());
    }

private:
    std::uniform_int_distribution<T> distribution_;

};
/**
 * @brief A random bool
 */
template<>
class random_int<bool> : public random_object<bool> {
public:
    /**
     * @brief Constructor
     */
    random_int()
        : random_object<bool>(), distribution_(0, 1)
    {}
    /**
     * @brief Returns a random bool
     * @returns A random bool
     */
    bool
    value()
    {
        return distribution_(this->gen());
    }

private:
    std::uniform_int_distribution<int> distribution_;

};
/**
 * @brief A random real
 */
template<typename T=double>
class random_real : public random_object<T> {
public:
    /**
     * @brief Constructor, range: [0, 1)
     */
    random_real()
        : random_object<T>(), distribution_(0, 1)
    {}
    /**
     * @brief Constructor, range: [0, maximum)
     * @param maximum The upper bound (excluding)
     */
    random_real(const T& maximum)
        : random_object<T>(), distribution_(0, maximum)
    {}
    /**
     * @brief Constructor, range: [minimum, maximum)
     * @param minimum The lower bound (including)
     * @param maximum The upper bound (excluding)
     */
    random_real(const T& minimum,
                const T& maximum)
        : random_object<T>(), distribution_(minimum, maximum)
    {}
    /**
     * @brief Returns a random real
     * @returns A random real
     */
    T
    value()
    {
        return distribution_(this->gen());
    }

private:
    std::uniform_real_distribution<T> distribution_;

};
/**
 * @brief A random choice from a given container
 */
template<typename Element,
         typename Container>
class random_choice : public random_object<Element> {
public:
    /**
     * @brief Constructor
     * @param container The container to choose from
     */
    random_choice(const Container& container)
        : random_object<Element>(), container_(container),
          distribution_(0, container_.size() - 1)
    {}
    /**
     * @brief Returns a random choice
     * @returns A random choice
     */
    Element
    value()
    {
        const auto index = distribution_(this->gen());
        long long count = 0;
        Element result;
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
    std::uniform_int_distribution<long long> distribution_;

};
/**
 * @brief A random container
 */
template<typename Element,
         typename Container>
class random_container : public random_object<Container> {
public:
    /**
     * @brief Constructor
     * @param rand The random object used to fill the container
     * @param size The container size
     */
    random_container(random_object<Element>& rand,
                     long long size)
        : random_object<Container>(),
          rand_(&rand),
          distribution_(size, size)
    {}
    /**
     * @brief Constructor
     * @param rand The random object used to fill the container
     * @param min_size The minimum container size (including)
     * @param max_size The maximum container size (including)
     */
    random_container(random_object<Element>& rand,
                     long long min_size,
                     long long max_size)
        : random_object<Container>(),
          rand_(&rand),
          distribution_(min_size, max_size)
    {}
    /**
     * @brief Returns a random container
     * @returns A random container
     */
    Container
    value()
    {
        const auto size = distribution_(this->gen());
        std::vector<Element> result;
        result.reserve(size);
        for (long long i=0; i<size; ++i)
            result.push_back(rand_->value());
        return {result.begin(), result.end()};
    }

private:
    random_object<Element>* rand_;
    std::uniform_int_distribution<long long> distribution_;

};
/**
 * @brief A random permutation of a given container
 */
template<typename Container>
class random_permutation : public random_object<Container> {
public:
    /**
     * @brief Constructor
     * @param container The container
     */
    random_permutation(const Container& container)
        : random_object<Container>(),
          container_(container)
    {}
    /**
     * @brief Returns a random permutation
     * @returns A random permutation
     */
    Container
    value()
    {
        std::shuffle(std::begin(container_), std::end(container_), this->gen());
        return container_;
    }

private:
    Container container_;

};
/**
 * @brief A random combination
 */
template<typename Element1,
         typename Container1,
         typename Element2,
         typename Container2>
class random_combination : public random_object<std::vector<std::pair<Element1, Element2>>> {
public:
    /**
     * @brief Constructor
     * @param container1 A container
     * @param container2 Another container
     */
    random_combination(const Container1& container1,
                       const Container2& container2)
        : random_object<std::vector<std::pair<Element1, Element2>>>(),
          permutation1_(container1),
          permutation2_(container2)
    {}
    /**
     * @brief Sets a new random seed
     * @param seed The random seed
     */
    void
    seed(int seed)
    {
        permutation1_.seed(seed);
        permutation2_.seed(seed);
        this->generator_.seed(seed);
    }
    /**
     * @brief Returns a random combination
     * @returns A random combination
     */
    std::vector<std::pair<Element1, Element2>>
    value()
    {
        const auto perm1 = permutation1_.value();
        const auto perm2 = permutation2_.value();
        std::vector<std::pair<Element1, Element2>> combination;
        combination.reserve(perm1.size() * perm2.size());
        for (auto& value1 : perm1) {
            for (auto& value2 : perm2) {
                combination.push_back(std::make_pair(value1, value2));
            }
        }
        std::shuffle(std::begin(combination), std::end(combination), this->gen());
        return std::move(combination);
    }

private:
    random_permutation<Container1> permutation1_;
    random_permutation<Container2> permutation2_;

};

} // unittest
