/**
 * @brief A collection of classes and factory functions to create random objects
 * @file random.hpp
 */
#pragma once
#include <vector>
#include <random>
#include <stdexcept>
#include <type_traits>
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
    virtual void
    seed(int seed)
    {
        gen().seed(seed);
    }

protected:
    /**
     * @brief Returns a reference to the random generator
     * @returns A reference to the random generator
     */
    std::mt19937&
    gen()
    {
        return generator_;
    }

private:
    std::mt19937 generator_;

};
/**
 * @brief The distribution type container
 */
template<typename T,
         bool is_integral>
struct distribution;
/**
 * @brief The distribution type container for integral types
 */
template<typename T>
struct distribution<T, true> {
    /**
     * @brief The distribution type for integral types
     */
    typedef typename std::uniform_int_distribution<T> type;
};
/**
 * @brief The distribution type container for non-integral types
 */
template<typename T>
struct distribution<T, false> {
  /**
   * @brief The distribution type for non-integral types
   */
  typedef typename std::uniform_real_distribution<double> type;
};
/**
 * @brief A random value. The lower bounds are including. The upper bounds are
 *  including for integral types and excluding for real types
 */
template<typename T>
class random_value : public random_object<T> {
public:
    /**
     * @brief Constructor, range: [0, 1]
     */
    random_value()
        : random_object<T>(), distribution_(0, 1)
    {}
    /**
     * @brief Constructor, range: [0, maximum]
     * @param maximum The upper bound
     */
    random_value(const T& maximum)
        : random_object<T>(), distribution_(0, maximum)
    {
        if (!(maximum>0))
            throw std::invalid_argument("maximum must be greater than zero");
    }
    /**
     * @brief Constructor, range: [minimum, maximum]
     * @param minimum The lower bound
     * @param maximum The upper bound
     */
    random_value(const T& minimum,
                 const T& maximum)
        : random_object<T>(), distribution_(minimum, maximum)
    {
        if (!(minimum<maximum))
            throw std::invalid_argument("minimum must be lesser than maximum");
    }
    /**
     * @brief Returns a random value
     * @returns A random value
     */
    T
    value()
    {
        return distribution_(this->gen());
    }

private:
    typename distribution<T, std::is_integral<T>::value>::type distribution_;

};
/**
 * @brief Factory function for random_value, range: [0, 1]
 * @returns An instance of random_value
 */
template<typename T>
random_value<T>
make_random_value()
{
    return random_value<T>();
}
/**
 * @brief Factory function for random_value, range: [0, maximum]
 * @param maximum The upper bound
 * @returns An instance of random_value
 */
template<typename T>
random_value<T>
make_random_value(const T& maximum)
{
    return random_value<T>(maximum);
}
/**
 * @brief Factory function for random_value, range: [minimum, maximum]
 * @param minimum The lower bound
 * @param maximum The upper bound
 * @returns An instance of random_value
 */
template<typename T>
random_value<T>
make_random_value(const T& minimum,
                  const T& maximum)
{
    return random_value<T>(minimum, maximum);
}
/**
 * @brief A random bool
 */
template<>
class random_value<bool> : public random_object<bool> {
public:
    /**
     * @brief Constructor
     */
    random_value()
        : random_object<bool>()
    {}
    /**
     * @brief Returns a random bool (true, false)
     * @returns A random bool
     */
    bool
    value()
    {
        return distribution_(this->gen()) & 1;
    }

private:
    std::uniform_int_distribution<char> distribution_;

};
/**
 * @brief Factory function for random_value<bool> (true, false)
 * @returns An instance of random_value<bool>
 */
random_value<bool>
make_random_bool();
/**
 * @brief A random choice from a given container
 */
template<typename Container>
class random_choice : public random_object<typename Container::value_type> {
public:
    /**
     * @brief The type of the container elements
     */
    typedef typename Container::value_type element_type;
    /**
     * @brief Constructor
     * @param container The container to choose from
     */
    random_choice(const Container& container)
        : random_object<element_type>(), container_(container),
          distribution_(0, container_.size() - 1)
    {}
    /**
     * @brief Returns a random choice
     * @returns A random choice
     */
    element_type
    value()
    {
        const auto index = distribution_(this->gen());
        long long count = 0;
        element_type result(*std::begin(container_));
        for (auto& value : container_) {
            if (count==index) {
                return value;
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
 * @brief Factory function for random_choice
 * @param container A container
 * @returns An instance of random_choice
 */
template<typename Container>
random_choice<Container>
make_random_choice(const Container& container)
{
    return random_choice<Container>(container);
}
/**
 * @brief A random container
 */
template<typename Container>
class random_container : public random_object<Container> {
public:
    /**
     * @brief The type of the container elements
     */
    typedef typename Container::value_type element_type;
    /**
     * @brief Constructor
     * @param rand The random object used to fill the container
     * @param size The container size
     */
    random_container(random_object<element_type>& rand,
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
    random_container(random_object<element_type>& rand,
                     long long min_size,
                     long long max_size)
        : random_object<Container>(),
          rand_(&rand),
          distribution_(min_size, max_size)
    {
        if (!(min_size<max_size))
            throw std::invalid_argument("min_size must be lesser than max_size");
    }
    /**
     * @brief Sets a new random seed
     * @param seed The random seed
     */
    void
    seed(int seed)
    {
        rand_->seed(seed);
        this->gen().seed(seed);
    }
    /**
     * @brief Returns a random container
     * @returns A random container
     */
    Container
    value()
    {
        const auto size = distribution_(this->gen());
        std::vector<element_type> result(size);
        for (long long i=0; i<size; ++i)
            result[i] = rand_->value();
        return {result.begin(), result.end()};
    }

private:
    random_object<element_type>* rand_;
    std::uniform_int_distribution<long long> distribution_;

};
/**
 * @brief Factory function for random_container
 * @param rand The random object used to fill the container
 * @param size The container size
 * @returns An instance of random_container
 */
template<typename Container>
random_container<Container>
make_random_container(random_object<typename Container::value_type>& rand,
                      long long size)
{
    return random_container<Container>(rand, size);
}
/**
 * @brief Factory function for random_container
 * @param rand The random object used to fill the container
 * @param min_size The minimum container size (including)
 * @param max_size The maximum container size (including)
 * @returns An instance of random_container
 */
template<typename Container>
random_container<Container>
make_random_container(random_object<typename Container::value_type>& rand,
                      long long min_size,
                      long long max_size)
{
    return random_container<Container>(rand, min_size, max_size);
}
/**
 * @brief Factory function for random_container<vector>
 * @param rand The random object used to fill the vector
 * @param size The vector size
 * @returns An instance of random_container<vector>
 */
template<typename T>
random_container<std::vector<T>>
make_random_vector(random_object<T>& rand,
                   long long size)
{
    return random_container<std::vector<T>>(rand, size);
}
/**
 * @brief Factory function for random_container<vector>
 * @param rand The random object used to fill the vector
 * @param min_size The minimum vector size (including)
 * @param max_size The maximum vector size (including)
 * @returns An instance of random_container<vector>
 */
template<typename T>
random_container<std::vector<T>>
make_random_vector(random_object<T>& rand,
                   long long min_size,
                   long long max_size)
{
    return random_container<std::vector<T>>(rand, min_size, max_size);
}
/**
 * @brief A random shuffle of a given container
 */
template<typename Container>
class random_shuffle : public random_object<Container> {
public:
    /**
     * @brief Constructor
     * @param container The container
     */
    random_shuffle(const Container& container)
        : random_object<Container>(),
          vector_(std::begin(container), std::end(container)),
          size_(container.size())
    {}
    /**
     * @brief Constructor
     * @param container The container
     * @param size The size of the shuffled container
     */
    random_shuffle(const Container& container,
                   long long size)
        : random_object<Container>(),
          vector_(std::begin(container), std::end(container)),
          size_(size)
    {
        long long max_size = container.size();
        if (size<1 || size>max_size)
            throw std::invalid_argument("size out of range");
    }
    /**
     * @brief Returns a random shuffle
     * @returns A random shuffle
     */
    Container
    value()
    {
        auto first = vector_.begin();
        shuffle(first, vector_.end(), this->gen());
        return {first, first + size_};
    }

private:
    std::vector<typename Container::value_type> vector_;
    long long size_;

};
/**
 * @brief Factory function for random_shuffle
 * @param container A container
 * @returns An instance of random_shuffle
 */
template<typename Container>
random_shuffle<Container>
make_random_shuffle(const Container& container)
{
    return random_shuffle<Container>(container);
}
/**
 * @brief Factory function for random_shuffle
 * @param container A container
 * @param size The size of the shuffled container
 * @returns An instance of random_shuffle
 */
template<typename Container>
random_shuffle<Container>
make_random_shuffle(const Container& container,
                    long long size)
{
    return random_shuffle<Container>(container, size);
}
/**
 * @brief Container for the combination type used in random_combination
 */
template<typename Container1,
         typename Container2>
struct combo {
    /**
     * @brief The type of the random combination
     */
    typedef
    std::vector<
        std::pair<
                  typename Container1::value_type,
                  typename Container2::value_type
                 >
               >
    type;
};
/**
 * @brief A random combination of two containers
 */
template<typename Container1,
         typename Container2>
class random_combination : public random_object<typename combo<Container1, Container2>::type> {

    typedef typename combo<Container1, Container2>::type combo_type;
public:
    /**
     * @brief Constructor
     * @param container1 A container
     * @param container2 Another container
     * @param size The number of combinations
     */
    random_combination(const Container1& container1,
                       const Container2& container2,
                       long long size)
        : random_object<combo_type>(),
          container1_(container1),
          container2_(container2),
          granter_(container1.size() * container2.size(), false),
          size_(size)
    {
        long long max_size = granter_.size();
        if (size<1 || size>max_size)
            throw std::invalid_argument("size out of range");
        for (long long i=0; i<size_; ++i)
            granter_[i] = true;
    }
    /**
     * @brief Returns a random combination
     * @returns A random combination
     */
    combo_type
    value()
    {
        long long index = 0;
        combo_type combination;
        combination.reserve(size_);
        shuffle(granter_.begin(), granter_.end(), this->gen());
        for (auto& value1 : container1_) {
            for (auto& value2 : container2_) {
                if (granter_[index])
                    combination.push_back(std::make_pair(value1, value2));
                ++index;
            }
        }
        return std::move(combination);
    }

private:
    Container1 container1_;
    Container2 container2_;
    std::vector<bool> granter_;
    long long size_;

};
/**
 * @brief Factory function for random_combination
 * @param container1 A container
 * @param container2 Another container
 * @param size The number of combinations
 * @returns An instance of random_combination
 */
template<typename Container1,
         typename Container2>
random_combination<Container1, Container2>
make_random_combination(const Container1& container1,
                        const Container2& container2,
                        long long size)
{
    return random_combination<Container1, Container2>(container1, container2, size);
}

} // unittest
