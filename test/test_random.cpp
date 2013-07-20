#include "test_random.h"
#include <list>
#define SPOT UNITTEST_SPOT

void test_random::test_random_int()
{
    auto randomA = unittest::make_random_int(3);
    auto randomB = unittest::make_random_int<long>(2, 4);
    auto randomC = unittest::make_random_int<long long>(-9, -2);
    for (int i=0; i<100; ++i) {
        assert_in_range(randomA.value(), -1, 4, SPOT);
        assert_in_range(randomB.value(), 1, 5, SPOT);
        assert_in_range(randomC.value(), -10, -1, SPOT);
    }
}

void test_random::test_random_int_throw()
{
    auto functor1 = [](){ unittest::make_random_int(-1); };
    assert_throw<std::invalid_argument>(functor1, SPOT);
    auto functor2 = [](){ unittest::make_random_int(1, 1); };
    assert_throw<std::invalid_argument>(functor2, SPOT);
    auto functor3 = [](){ unittest::make_random_int(9, 1); };
    assert_throw<std::invalid_argument>(functor3, SPOT);
}

void test_random::test_random_bool()
{
    auto random = unittest::make_random_bool();
    const std::vector<bool> container = {true, false};
    for (int i=0; i<100; ++i) {
        assert_in_container(random.value(), container, SPOT);
    }
}

void test_random::test_random_real()
{
    auto randomA = unittest::make_random_real(3.);
    auto randomB = unittest::make_random_real<float>(1.5, 4.2);
    for (int i=0; i<100; ++i) {
        assert_in_range(randomA.value(), -0.01, 3, SPOT);
        assert_in_range(randomB.value(), 1.49, 4.2, SPOT);
    }
}

void test_random::test_random_real_throw()
{
    auto functor1 = [](){ unittest::make_random_real(-1.); };
    assert_throw<std::invalid_argument>(functor1, SPOT);
    auto functor2 = [](){ unittest::make_random_real(1., 1.); };
    assert_throw<std::invalid_argument>(functor2, SPOT);
    auto functor3 = [](){ unittest::make_random_real(9., 1.); };
    assert_throw<std::invalid_argument>(functor3, SPOT);
}

void test_random::test_random_choice_string()
{
    const std::string characters("abc");
    auto random = unittest::make_random_choice(characters);
    for (int i=0; i<100; ++i) {
        assert_in_container(random.value(), characters, SPOT);
    }
}

void test_random::test_random_choice_vector()
{
    const std::vector<double> vector = {1, 2, 3};
    auto random = unittest::make_random_choice(vector);
    for (int i=0; i<100; ++i) {
        assert_in_container(random.value(), vector, SPOT);
    }
}

void test_random::test_random_choice_list()
{
    const std::list<int> a_list = {1, 2, 3};
    auto random = unittest::make_random_choice(a_list);
    for (int i=0; i<100; ++i) {
        assert_in_container(random.value(), a_list, SPOT);
    }
}

void test_random::test_random_container_string()
{
    const std::string characters("abc");
    auto random = unittest::make_random_choice(characters);
    const unsigned length = 5;
    const unsigned min_length = 3;
    auto random_contA = unittest::make_random_container<std::string>(random, length);
    auto random_contB = unittest::make_random_container<std::string>(random, min_length, length);
    assert_random_container_fixed(random_contA, characters, length, SPOT);
    assert_random_container_range(random_contB, characters, min_length, length, SPOT);
}

void test_random::test_random_container_list()
{
    auto random = unittest::make_random_int(1, 3);
    const unsigned length = 5;
    const unsigned min_length = 3;
    auto random_contA = unittest::make_random_container<std::list<int>>(random, length);
    auto random_contB = unittest::make_random_container<std::list<int>>(random, min_length, length);
    const std::list<int> a_list = {1, 2, 3};
    assert_random_container_fixed(random_contA, a_list, length, SPOT);
    assert_random_container_range(random_contB, a_list, min_length, length, SPOT);
}

void test_random::test_random_container_vector()
{
    auto random = unittest::make_random_int(1, 3);
    const unsigned length = 5;
    const unsigned min_length = 3;
    auto random_contA = unittest::make_random_vector(random, length);
    auto random_contB = unittest::make_random_vector(random, min_length, length);
    const std::vector<int> vector = {1, 2, 3};
    assert_random_container_fixed(random_contA, vector, length, SPOT);
    assert_random_container_range(random_contB, vector, min_length, length, SPOT);
}

void test_random::test_random_container_throw()
{
    auto functor1 = [](){
        auto random = unittest::make_random_int(1, 3);
        unittest::make_random_container<std::list<int>>(random, 1, 1);
    };
    assert_throw<std::invalid_argument>(functor1, SPOT);
    auto functor2 = [](){
        auto random = unittest::make_random_int(1, 3);
        unittest::make_random_container<std::list<int>>(random, 3, 1);
    };
    assert_throw<std::invalid_argument>(functor2, SPOT);
}

void test_random::test_random_shuffle_vector()
{
    const std::vector<int> vector = {1, 2, 3};
    auto random = unittest::make_random_shuffle(vector);
    for (int i=0; i<100; ++i) {
        const auto perm_vector = random.value();
        assert_in_container(perm_vector[0], vector, SPOT);
        assert_in_container(perm_vector[1], vector, SPOT);
        assert_in_container(perm_vector[2], vector, SPOT);
        assert_equal(6, perm_vector[0] + perm_vector[1] + perm_vector[2], SPOT);
    }
}

void test_random::test_random_shuffle_list()
{
    const std::list<double> a_list = {1, 2, 3};
    auto random = unittest::make_random_shuffle(a_list, 2);
    for (int i=0; i<100; ++i) {
        const auto perm_list = random.value();
        auto first = std::begin(perm_list);
        auto sum = *first;
        assert_in_container(*first, a_list, SPOT);
        ++first;
        sum += *first;
        assert_in_container(*first, a_list, SPOT);
        assert_in_range(sum, 2, 6, SPOT);
    }
}

void test_random::test_random_shuffle_throw()
{

    auto functor1 = [](){
        const std::list<int> a_list = {1, 2, 3};
        unittest::make_random_shuffle(a_list, 0);
    };
    assert_throw<std::invalid_argument>(functor1, SPOT);
    auto functor2 = [](){
        const std::list<int> a_list = {1, 2, 3};
        unittest::make_random_shuffle(a_list, 4);
    };
    assert_throw<std::invalid_argument>(functor2, SPOT);
}

void test_random::test_random_combination_vector()
{
    const std::vector<int> vector1 = {1, 2, 3};
    const std::vector<double> vector2 = {5, 6};
    auto rand_combo = unittest::make_random_combination(vector1, vector2, 4);
    for (int i=0; i<100; ++i) {
        const auto combo = rand_combo.value();
        assert_equal<unsigned>(4, combo.size(), SPOT);
        for (auto& value : combo) {
            assert_in_container(value.first, vector1, SPOT);
            assert_in_container(value.second, vector2, SPOT);
        }
    }
}

void test_random::test_random_combination_list()
{
    const std::list<int> list1 = {1, 2, 3};
    const std::list<double> list2 = {5, 6};
    auto rand_combo = unittest::make_random_combination(list1, list2, 3);
    for (int i=0; i<100; ++i) {
        const auto combo = rand_combo.value();
        assert_equal<unsigned>(3, combo.size(), SPOT);
        for (auto& value : combo) {
            assert_in_container(value.first, list1, SPOT);
            assert_in_container(value.second, list2, SPOT);
        }
    }
}

void test_random::test_random_combination_throw()
{
    auto functor1 = []() {
        const std::list<int> list1 = {1, 2, 3};
        const std::list<double> list2 = {5, 6};
        unittest::make_random_combination(list1, list2, 0);
    };
    assert_throw<std::invalid_argument>(functor1, SPOT);
    auto functor2 = []() {
        const std::list<int> list1 = {1, 2, 3};
        const std::list<double> list2 = {5, 6};
        unittest::make_random_combination(list1, list2, 7);
    };
    assert_throw<std::invalid_argument>(functor2, SPOT);
}
