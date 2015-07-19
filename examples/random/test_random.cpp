#include <libunittest/all.hpp>

TEST(test_random_int)
{
    auto random = unittest::make_random_value<int>(10);
    random->seed(42); // let's you set the random seed (default is 1)
    auto rand_value1 = random->get(); // a random int in [0, 10]
    auto rand_value2 = random->get(); // another random int in [0, 10]
    ASSERT_IN_RANGE(rand_value1, 0, 10)
    ASSERT_IN_RANGE(rand_value2, 0, 10)
}

TEST(test_random_bool)
{
    auto random = unittest::make_random_bool();
    auto rand_value1 = random->get(); // a random bool in [true, false]
    auto rand_value2 = random->get(); // another random bool in [true, false]
    const std::vector<bool> container = {true, false};
    ASSERT_IN_CONTAINER(rand_value1, container)
    ASSERT_IN_CONTAINER(rand_value2, container)
}

TEST(test_random_double)
{
    auto random = unittest::make_random_value<double>(2, 5);
    auto rand_value1 = random->get(); // a random double in [2, 5)
    auto rand_value2 = random->get(); // another random double in [2, 5)
    ASSERT_IN_RANGE(rand_value1, 2, 5)
    ASSERT_IN_RANGE(rand_value2, 2, 5)
}

TEST(test_random_choice)
{
    auto random = unittest::make_random_choice(unittest::strings::letters_lower);
    auto rand_value = random->get(); // a random, lower-case letter
    ASSERT_IN_CONTAINER(rand_value, unittest::strings::letters_lower)
}

TEST(test_random_vector)
{
    auto random1 = unittest::make_random_value<double>();
    auto random2 = unittest::make_random_vector(random1, 10);
    auto rand_vector = random2->get(); // a vector of size 10 filled with
                                      // random doubles from the interval of [0, 1)
    ASSERT_EQUAL(10u, rand_vector.size())
    for (auto& value : rand_vector) {
        ASSERT_IN_RANGE(value, 0, 1)
    }
}

TEST(test_random_tuple)
{
    auto random1 = unittest::make_random_value<double>(2.0, 3.0);
    auto random2 = unittest::make_random_value<int>(4, 8);
    auto random3 = unittest::make_random_value<bool>();
    auto random4 = unittest::make_random_tuple(random1, random2, random3);
    // if you have generic code working on arbitrary tuples
    // always test it with empty tuples as well:
    auto random5 = unittest::make_random_tuple();
    auto rand_tuple = random4->get();
    auto empty_tuple = random5->get();
    ASSERT_EQUAL(3u, std::tuple_size<decltype(rand_tuple)>::value)
    ASSERT_EQUAL(0u, std::tuple_size<decltype(empty_tuple)>::value)
    const std::vector<bool> container = {true, false};
    ASSERT_IN_RANGE(std::get<0>(rand_tuple), 2.0, 3.0)
    ASSERT_IN_RANGE(std::get<1>(rand_tuple), 4, 8)
    ASSERT_IN_CONTAINER(std::get<2>(rand_tuple), container)
}

TEST(test_random_pair)
{
    auto random1 = unittest::make_random_value<double>(2.0, 3.0);
    auto random2 = unittest::make_random_value<int>(4, 8);
    auto random3 = unittest::make_random_pair(random1, random2);
    auto rand_pair = random3->get();
    ASSERT_IN_RANGE(rand_pair.first, 2.0, 3.0)
    ASSERT_IN_RANGE(rand_pair.second, 4, 8)
}

TEST(test_random_shuffle)
{
    const std::vector<int> container = {1, 2, 3, 4};
    auto random = unittest::make_random_shuffle(container, 2);
    auto rand_vector = random->get(); // a randomly shuffled vector of size 2
    ASSERT_EQUAL(2u, rand_vector.size())
    for (auto& value : rand_vector) {
        ASSERT_IN_CONTAINER(value, container)
    }
}
