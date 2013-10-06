#include "test_random.h"
#define SPOT UNITTEST_SPOT

UNITTEST_REGISTER(test_random)

void test_random::test_random_int()
{
    auto random = unittest::make_random_value<int>(10);
    random.seed(42); // let's you set the random seed (default is 1)
    auto rand_value1 = random.get(); // a random int in [0, 10]
    auto rand_value2 = random.get(); // another random int in [0, 10]
    assert_in_range(rand_value1, 0, 10, SPOT);
    assert_in_range(rand_value2, 0, 10, SPOT);
}

void test_random::test_random_bool()
{
    auto random = unittest::make_random_bool();
    auto rand_value1 = random.get(); // a random bool in [true, false]
    auto rand_value2 = random.get(); // another random bool in [true, false]
    const std::vector<bool> container = {true, false};
    assert_in_container(rand_value1, container, SPOT);
    assert_in_container(rand_value2, container, SPOT);
}

void test_random::test_random_double()
{
    auto random = unittest::make_random_value<double>(2, 5);
    auto rand_value1 = random.get(); // a random double in [2, 5)
    auto rand_value2 = random.get(); // another random double in [2, 5)
    assert_in_range(rand_value1, 2, 5, SPOT);
    assert_in_range(rand_value2, 2, 5, SPOT);
}

void test_random::test_random_choice()
{
    auto random = unittest::make_random_choice(unittest::strings::letters_lower);
    auto rand_value = random.get(); // a random, lower-case letter
    assert_in_container(rand_value, unittest::strings::letters_lower, SPOT);
}

void test_random::test_random_vector()
{
    auto random1 = unittest::make_random_value<double>();
    auto random2 = unittest::make_random_vector(random1, 10);
    auto rand_vector = random2.get(); // a vector of size 10 filled with
                                      // random doubles from the interval of [0, 1)
    assert_equal<unsigned>(10, rand_vector.size(), SPOT);
    for (auto& value : rand_vector) {
        assert_in_range(value, 0, 1, SPOT);
    }
}

void test_random::test_random_shuffle()
{
    const std::vector<int> container = {1, 2, 3, 4};
    auto random = unittest::make_random_shuffle(container, 2);
    auto rand_vector = random.get(); // a randomly shuffled vector of size 2
    assert_equal<unsigned>(2, rand_vector.size(), SPOT);
    for (auto& value : rand_vector) {
        assert_in_container(value, container, SPOT);
    }
}
