/**
 * @brief A collection of classes and factory functions for random functionality
 * @file random.hpp
 */
#pragma once
#include <vector>
#include <random>
#include <stdexcept>
#include <type_traits>
#include <libunittest/tuplemap.hpp>
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
     * @brief Destructor
     */
    virtual
    ~random_object()
    {}
    /**
     * @brief Supposed to return a random object
     * @returns A random object
     */
    virtual T
    get() = 0;
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
     * @brief Constructor initializing the Mersenne-Twister generator
     *  with a default random seed of one
     */
    random_object()
        : generator_(1)
    {}
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
 * @brief Internal functionality, not relevant for most users
 */
namespace internals {
/**
 * @brief Container of the distribution type used in random_value
 */
template<typename T,
         bool is_integral>
struct distribution;
/**
 * @brief The distribution type container for integral types
 */
template<typename T>
struct distribution<T, true> final {
    /**
     * @brief The distribution type for integral types
     */
    typedef typename std::uniform_int_distribution<T> type;
};
/**
 * @brief The distribution type container for non-integral types
 */
template<typename T>
struct distribution<T, false> final {
  /**
   * @brief The distribution type for non-integral types
   */
  typedef typename std::uniform_real_distribution<T> type;
};

} // internals

/**
 * @brief A random value. The lower bounds are including. The upper bounds are
 *  including for integral types and excluding for real types
 */
template<typename T>
class random_value final : public random_object<T> {
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
    get() override
    {
        return distribution_(this->gen());
    }

private:
    typename internals::distribution<T, std::is_integral<T>::value>::type distribution_;

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
class random_value<bool> final : public random_object<bool> {
public:
    /**
     * @brief Constructor
     */
    random_value()
        : random_object<bool>(), distribution_(0, 1)
    {}
    /**
     * @brief Returns a random bool (true, false)
     * @returns A random bool
     */
    bool
    get() override
    {
        return distribution_(this->gen()) == 1;
    }

private:
    std::uniform_int_distribution<int> distribution_;

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
class random_choice final : public random_object<typename Container::value_type> {
    /**
     * @brief The type of the container elements
     */
    typedef typename Container::value_type element_type;

public:
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
    get() override
    {
        const unsigned int index = distribution_(this->gen());
        unsigned int count = 0;
        element_type result(*std::begin(container_));
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
    std::uniform_int_distribution<unsigned int> distribution_;

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
class random_container final : public random_object<Container> {
    /**
     * @brief The type of the container elements
     */
    typedef typename Container::value_type element_type;

public:
    /**
     * @brief Constructor
     * @param rand The random object used to fill the container
     * @param size The container size
     */
    random_container(random_object<element_type>& rand,
                     unsigned int size)
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
                     unsigned int min_size,
                     unsigned int max_size)
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
    seed(int seed) override
    {
        rand_->seed(seed);
        this->gen().seed(seed);
    }
    /**
     * @brief Returns a random container
     * @returns A random container
     */
    Container
    get() override
    {
        const unsigned int size = distribution_(this->gen());
        std::vector<element_type> result(size);
        for (unsigned int i=0; i<size; ++i)
            result[i] = rand_->get();
        Container container(result.begin(), result.end());
        return std::move(container);
    }

private:
    random_object<element_type>* rand_;
    std::uniform_int_distribution<unsigned int> distribution_;

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
                      unsigned int size)
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
                      unsigned int min_size,
                      unsigned int max_size)
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
                   unsigned int size)
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
                   unsigned int min_size,
                   unsigned int max_size)
{
    return random_container<std::vector<T>>(rand, min_size, max_size);
}
/**
 * @brief A random tuple
 */
template<typename ...Args>
class random_tuple final : public random_object<std::tuple<Args...>> {
public:
    /**
     * @brief Constructor
     * @param rands Random objects used to fill the tuple
     */
    random_tuple(random_object<Args>&... rands)
        : random_object<std::tuple<Args...>>(),
          rand_tuple_(&rands...)
    {}
    /**
     * @brief Sets a new random seed
     * @param seed The random seed
     */
    void
    seed(int seed) override
    {
        internals::tuple_for_each(seed_func(), rand_tuple_, seed);
    }
    /**
     * @brief Returns a random tuple
     * @returns A random tuple
     */
    std::tuple<Args...>
    get() override
    {
        std::tuple<Args...> result;
        internals::tuple_transform(get_func(), rand_tuple_, result);
        return std::move(result);
    }

private:

    std::tuple<random_object<Args>*...> rand_tuple_;

    struct seed_func {
        template<typename T>
        void operator()(random_object<T>* rand, int seed) const
        {
            rand->seed(seed);
        }
    };

    struct get_func {
        template<typename T>
        T operator()(random_object<T>* rand) const
        {
            return rand->get();
        }
    };

};
/**
 * @brief Factory function for random_tuple
 * @param rands The random objects used to fill the tuple
 * @returns An instance of random_tuple
 */
template<typename ...Args>
random_tuple<Args...>
make_random_tuple(random_object<Args>&... rands)
{
    return random_tuple<Args...>(rands...);
}
/**
 * @brief A random pair
 */
template<typename F,
         typename S>
class random_pair final : public random_object<std::pair<F,S>> {
public:
    /**
     * @brief Constructor
     * @param rand_fst Random object used to fill the first pair element
     * @param rand_snd Random object used to fill the second pair element
     */
    random_pair(random_object<F>& rand_fst,
                random_object<S>& rand_snd)
        : random_object<std::pair<F,S>>(),
          rand_fst_(&rand_fst),
          rand_snd_(&rand_snd)
    {}
    /**
     * @brief Sets a new random seed
     * @param seed The random seed
     */
    void
    seed(int seed) override
    {
        rand_fst_->seed(seed);
        rand_snd_->seed(seed);
    }
    /**
     * @brief Returns a random pair
     * @returns A random pair
     */
    std::pair<F,S>
    get() override
    {
        std::pair<F,S> pair(rand_fst_->get(), rand_snd_->get());
        return std::move(pair);
    }

private:
    random_object<F>* rand_fst_;
    random_object<S>* rand_snd_;
};
/**
 * @brief Factory function for random_pair
 * @param rand_fst The random object used to fill the first pair element
 * @param rand_snd The random object used to fill the second pair element
 * @returns An instance of random_pair
 */
template<typename F,
         typename S>
random_pair<F,S>
make_random_pair(random_object<F>& rand_fst,
                 random_object<S>& rand_snd)
{
    return random_pair<F,S>(rand_fst, rand_snd);
}
/**
 * @brief A random shuffle of a given container
 */
template<typename Container>
class random_shuffle final : public random_object<Container> {
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
                   unsigned int size)
        : random_object<Container>(),
          vector_(std::begin(container), std::end(container)),
          size_(size)
    {
        if (size<1 || size>container.size())
            throw std::invalid_argument("size out of range");
    }
    /**
     * @brief Returns a random shuffle
     * @returns A random shuffle
     */
    Container
    get() override
    {
        auto first = vector_.begin();
        shuffle(first, vector_.end(), this->gen());
        Container container(first, first + size_);
        return std::move(container);
    }

private:
    std::vector<typename Container::value_type> vector_;
    unsigned int size_;

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
                    unsigned int size)
{
    return random_shuffle<Container>(container, size);
}

/**
 * @brief Internal functionality, not relevant for most users
 */
namespace internals {
/**
 * @brief Container for the combination type used in random_combination
 */
template<typename Container1,
         typename Container2>
struct combination final {
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

} // internals

/**
 * @brief A random combination of two containers
 */
template<typename Container1,
         typename Container2>
class random_combination final : public random_object<typename internals::combination<Container1, Container2>::type> {
    /**
     * @brief The type of the random combination
     */
    typedef typename internals::combination<Container1, Container2>::type combination_type;

public:
    /**
     * @brief Constructor
     * @param container1 A container
     * @param container2 Another container
     * @param size The number of combinations
     */
    random_combination(const Container1& container1,
                       const Container2& container2,
                       unsigned int size)
        : random_object<combination_type>(),
          container1_(container1),
          container2_(container2),
          granter_(container1.size() * container2.size(), false),
          size_(size)
    {
        if (size<1 || size>granter_.size())
            throw std::invalid_argument("size out of range");
        for (unsigned int i=0; i<size_; ++i)
            granter_[i] = true;
    }
    /**
     * @brief Returns a random combination
     * @returns A random combination
     */
    combination_type
    get() override
    {
        unsigned int index = 0;
        combination_type combination;
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
    unsigned int size_;

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
                        unsigned int size)
{
    return random_combination<Container1, Container2>(container1, container2, size);
}

} // unittest
