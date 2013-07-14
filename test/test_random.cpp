#include "test_random.h"
#include <list>
#define SPOT UNITTEST_SPOT

void test_random::test_random_int()
{
    unittest::random_int<int> randomA(3);
    unittest::random_int<long> randomB(2, 4);
    for (int i=0; i<100; ++i) {
        assert_in_range(randomA.value(), -1, 4, SPOT);
        assert_in_range(randomB.value(), 1, 5, SPOT);
    }
}

void test_random::test_random_bool()
{
    unittest::random_int<bool> random;
    const std::vector<bool> container = {true, false};
    for (int i=0; i<100; ++i) {
        assert_in_container(random.value(), container, SPOT);
    }
}

void test_random::test_random_real()
{
    unittest::random_real<float> randomA(3);
    unittest::random_real<double> randomB(1.5, 4.2);
    for (int i=0; i<100; ++i) {
        assert_in_range(randomA.value(), -0.01, 3, SPOT);
        assert_in_range(randomB.value(), 1.49, 4.2, SPOT);
    }
}

void test_random::test_random_choice()
{
    const std::string characters("abc");
    unittest::random_choice<char, std::string> random(characters);
    for (int i=0; i<100; ++i) {
        assert_in_container(random.value(), characters, SPOT);
    }
}

void test_random::test_random_container_string()
{
    const std::string characters("abc");
    unittest::random_choice<char, std::string> random(characters);
    const unsigned length = 5;
    const unsigned min_length = 3;
    unittest::random_container<char, std::string> random_contA(random, length);
    unittest::random_container<char, std::string> random_contB(random, min_length, length);
    assert_random_container_fixed(random_contA, characters, length, SPOT);
    assert_random_container_range(random_contB, characters, min_length, length, SPOT);
}

void test_random::test_random_container_list()
{
    const std::list<int> a_list = {1, 2, 3};
    unittest::random_int<> random(1, 3);
    const unsigned length = 5;
    const unsigned min_length = 3;
    unittest::random_container<int, decltype(a_list)> random_contA(random, length);
    unittest::random_container<int, decltype(a_list)> random_contB(random, min_length, length);
    assert_random_container_fixed(random_contA, a_list, length, SPOT);
    assert_random_container_range(random_contB, a_list, min_length, length, SPOT);
}

void test_random::test_random_permutation()
{
    const std::vector<int> vector = {1, 2, 3};
    unittest::random_permutation<std::vector<int>> random(vector);
    for (int i=0; i<100; ++i) {
        const auto perm_vector = random.value();
        assert_in_container(perm_vector[0], vector, SPOT);
        assert_in_container(perm_vector[1], vector, SPOT);
        assert_in_container(perm_vector[2], vector, SPOT);
        assert_equal(6, perm_vector[0] + perm_vector[1] + perm_vector[2], SPOT);
    }
}
