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
    virtual void
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
template<typename Container>
class random_choice : public random_object<typename Container::value_type> {
public:
    typedef typename Container::value_type elem_type;
    /**
     * @brief Constructor
     * @param container The container to choose from
     */
    random_choice(const Container& container)
        : random_object<elem_type>(), container_(container),
          distribution_(0, container_.size() - 1)
    {}
    /**
     * @brief Returns a random choice
     * @returns A random choice
     */
    elem_type
    value()
    {
        const auto index = distribution_(this->gen());
        long long count = 0;
        elem_type result;
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
template<typename Container>
class random_container : public random_object<Container> {
public:
    typedef typename Container::value_type elem_type;
    /**
     * @brief Constructor
     * @param rand The random object used to fill the container
     * @param size The container size
     */
    random_container(random_object<elem_type>& rand,
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
    random_container(random_object<elem_type>& rand,
                     long long min_size,
                     long long max_size)
        : random_object<Container>(),
          rand_(&rand),
          distribution_(min_size, max_size)
    {}
    /**
     * @brief Sets a new random seed
     * @param seed The random seed
     */
    void
    seed(int seed)
    {
        rand_->seed(seed);
        this->generator_.seed(seed);
    }
    /**
     * @brief Returns a random container
     * @returns A random container
     */
    Container
    value()
    {
        const auto size = distribution_(this->gen());
        std::vector<elem_type> result(size);
        for (long long i=0; i<size; ++i)
            result[i] = rand_->value();
        return {result.begin(), result.end()};
    }

private:
    random_object<elem_type>* rand_;
    std::uniform_int_distribution<long long> distribution_;

};
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
          vector_(std::begin(container), std::end(container))
    {}
    /**
     * @brief Returns a random shuffle
     * @returns A random shuffle
     */
    Container
    value()
    {
        std::shuffle(vector_.begin(), vector_.end(), this->gen());
        return {vector_.begin(), vector_.end()};
    }

private:
    std::vector<typename Container::value_type> vector_;

};
/**
 * @brief Defines the combination type used in random_combination
 */
template<typename Container1,
         typename Container2>
struct combo {
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
public:
    typedef typename combo<Container1, Container2>::type combo_type;
    /**
     * @brief Constructor
     * @param container1 A container
     * @param container2 Another container
     */
    random_combination(const Container1& container1,
                       const Container2& container2)
        : random_object<combo_type>(),
          shuffle1_(container1),
          shuffle2_(container2),
          combination_(container1.size() * container2.size())
    {}
    /**
     * @brief Sets a new random seed
     * @param seed The random seed
     */
    void
    seed(int seed)
    {
        shuffle1_.seed(seed);
        shuffle2_.seed(seed);
        this->generator_.seed(seed);
    }
    /**
     * @brief Returns a random combination
     * @returns A random combination
     */
    combo_type
    value()
    {
        auto iter = combination_.begin();
        for (auto& value1 : shuffle1_.value()) {
            for (auto& value2 : shuffle2_.value()) {
                *iter = std::make_pair(value1, value2);
                ++iter;
            }
        }
        std::shuffle(combination_.begin(), combination_.end(), this->gen());
        return combination_;
    }

private:
    random_shuffle<Container1> shuffle1_;
    random_shuffle<Container2> shuffle2_;
    combo_type combination_;

};

} // unittest
