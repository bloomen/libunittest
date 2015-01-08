#include <libunittest/all.hpp>
using namespace unittest::assertions;

TEST(test_random_int)
{
    auto random = unittest::make_random_value<int>(10);
    random->seed(42); // let's you set the random seed (default is 1)
    auto rand_value1 = random->get(); // a random int in [0, 10]
    auto rand_value2 = random->get(); // another random int in [0, 10]
    assert_in_range(rand_value1, 0, 10, SPOT);
    assert_in_range(rand_value2, 0, 10, SPOT);
}

TEST(test_random_bool)
{
    auto random = unittest::make_random_bool();
    auto rand_value1 = random->get(); // a random bool in [true, false]
    auto rand_value2 = random->get(); // another random bool in [true, false]
    const std::vector<bool> container = {true, false};
    assert_in_container(rand_value1, container, SPOT);
    assert_in_container(rand_value2, container, SPOT);
}

TEST(test_random_double)
{
    auto random = unittest::make_random_value<double>(2, 5);
    auto rand_value1 = random->get(); // a random double in [2, 5)
    auto rand_value2 = random->get(); // another random double in [2, 5)
    assert_in_range(rand_value1, 2, 5, SPOT);
    assert_in_range(rand_value2, 2, 5, SPOT);
}

TEST(test_random_choice)
{
    auto random = unittest::make_random_choice(unittest::strings::letters_lower);
    auto rand_value = random->get(); // a random, lower-case letter
    assert_in_container(rand_value, unittest::strings::letters_lower, SPOT);
}

TEST(test_random_vector)
{
    auto random1 = unittest::make_random_value<double>();
    auto random2 = unittest::make_random_vector(random1, 10);
    auto rand_vector = random2->get(); // a vector of size 10 filled with
                                      // random doubles from the interval of [0, 1)
    assert_equal<unsigned>(10, rand_vector.size(), SPOT);
    for (auto& value : rand_vector) {
        assert_in_range(value, 0, 1, SPOT);
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
    assert_equal<unsigned>(3, std::tuple_size<decltype(rand_tuple)>::value, SPOT);
    assert_equal<unsigned>(0, std::tuple_size<decltype(empty_tuple)>::value, SPOT);
    const std::vector<bool> container = {true, false};
    assert_in_range(std::get<0>(rand_tuple), 2.0, 3.0, SPOT);
    assert_in_range(std::get<1>(rand_tuple), 4, 8, SPOT);
    assert_in_container(std::get<2>(rand_tuple), container, SPOT);
}

TEST(test_random_pair)
{
    auto random1 = unittest::make_random_value<double>(2.0, 3.0);
    auto random2 = unittest::make_random_value<int>(4, 8);
    auto random3 = unittest::make_random_pair(random1, random2);
    auto rand_pair = random3->get();
    assert_in_range(rand_pair.first, 2.0, 3.0, SPOT);
    assert_in_range(rand_pair.second, 4, 8, SPOT);
}

TEST(test_random_shuffle)
{
    const std::vector<int> container = {1, 2, 3, 4};
    auto random = unittest::make_random_shuffle(container, 2);
    auto rand_vector = random->get(); // a randomly shuffled vector of size 2
    assert_equal<unsigned>(2, rand_vector.size(), SPOT);
    for (auto& value : rand_vector) {
        assert_in_container(value, container, SPOT);
    }
}
