#include "test_random.h"
#define SPOT UNITTEST_SPOT

void test_random::test_random_int()
{
    auto random = unittest::make_random_value<int>(10);
    random.seed(42); // let's you set the random seed (default is 1)
    auto rand_value1 = random.value(); // a random int in [0, 10]
    auto rand_value2 = random.value(); // another random int [0, 10]
}

void test_random::test_random_bool()
{
    auto random = unittest::make_random_bool();
    auto rand_value1 = random.value(); // a random bool in [true, false]
    auto rand_value2 = random.value(); // another random bool in [true, false]
}

void test_random::test_random_double()
{
    auto random = unittest::make_random_value<double>(2, 5);
    auto rand_value1 = random.value(); // a random double in [2, 5)
    auto rand_value2 = random.value(); // another random double in [2, 5)
}

void test_random::test_random_choice()
{
    auto random = unittest::make_random_choice(unittest::letters_lower);
    auto rand_value = random.value(); // a random, lower-case letter
}

void test_random::test_random_vector()
{
    auto random1 = unittest::make_random_value<double>();
    auto random2 = unittest::make_random_vector(random1, 10);
    auto rand_vector = random2.value(); // a vector of size 10 filled with
                                        // random doubles from the interval of [0, 1)
}

void test_random::test_random_shuffle()
{
    const std::vector<int> container = {1, 2, 3, 4};
    auto random = unittest::make_random_shuffle(container, 2);
    auto rand_vector = random.value(); // a randomly shuffled vector of size 2
}
