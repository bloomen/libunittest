#include <libunittest/all.hpp>
#include <list>
#include <mutex>
using namespace unittest::assertions;

template<typename RandomCont,
         typename OrigContainer,
         typename T>
void assert_random_container_fixed(RandomCont& random_object,
                                   const OrigContainer& container,
                                   const T& length,
                                   const std::string& spot)
{
    for (int i=0; i<100; ++i) {
        const auto rand_cont = random_object->get();
        assert_equal(length, rand_cont.size(), spot);
        for (auto& value : rand_cont)
            assert_in_container(value, container, spot);
    }
}

template<typename RandomCont,
         typename OrigContainer,
         typename T>
void assert_random_container_range(RandomCont& random_object,
                                   const OrigContainer& container,
                                   const T& min_length,
                                   const T& max_length,
                                   const std::string& spot)
{
    for (int i=0; i<100; ++i) {
        const auto rand_cont = random_object->get();
        assert_in_range(rand_cont.size(), min_length, max_length, spot);
        for (auto& value : rand_cont)
            assert_in_container(value, container, spot);
    }
}

struct test_random : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_random)
        UNITTEST_RUN(test_random_int)
        UNITTEST_RUN(test_random_int_throw)
        UNITTEST_RUN(test_random_bool)
        UNITTEST_RUN(test_random_real)
        UNITTEST_RUN(test_random_real_throw)
        UNITTEST_RUN(test_random_choice_string)
        UNITTEST_RUN(test_random_choice_vector)
        UNITTEST_RUN(test_random_choice_list)
        UNITTEST_RUN(test_random_container_string)
        UNITTEST_RUN(test_random_container_list)
        UNITTEST_RUN(test_random_container_vector)
        UNITTEST_RUN(test_random_container_throw)
        UNITTEST_RUN(test_random_tuple)
        UNITTEST_RUN(test_random_pair)
        UNITTEST_RUN(test_random_shuffle_vector)
        UNITTEST_RUN(test_random_shuffle_list)
        UNITTEST_RUN(test_random_shuffle_throw)
        UNITTEST_RUN(test_random_combination_vector)
        UNITTEST_RUN(test_random_combination_list)
        UNITTEST_RUN(test_random_combination_throw)
        UNITTEST_RUN(test_random_value_copy_constructor)
        UNITTEST_RUN(test_random_value_assignment_operator)
        UNITTEST_RUN(test_random_value_clone)
        UNITTEST_RUN(test_random_value_thread_safety)
    }

    void test_random_int()
    {
        auto randomA = unittest::make_random_value(3);
        auto randomB = unittest::make_random_value<long>(2, 4);
        auto randomC = unittest::make_random_value<long long>(-9, -2);
        for (int i=0; i<100; ++i) {
            assert_in_range(randomA->get(), 0, 3, SPOT);
            assert_in_range(randomB->get(), 2, 4, SPOT);
            assert_in_range(randomC->get(), -9, -2, SPOT);
        }
    }

    void test_random_int_throw()
    {
        auto functor1 = [](){ unittest::make_random_value(-1); };
        assert_throw<std::invalid_argument>(functor1, SPOT);
        auto functor2 = [](){ unittest::make_random_value(1, 1); };
        assert_throw<std::invalid_argument>(functor2, SPOT);
        auto functor3 = [](){ unittest::make_random_value(9, 1); };
        assert_throw<std::invalid_argument>(functor3, SPOT);
    }

    void test_random_bool()
    {
        auto random = unittest::make_random_bool();
        const std::vector<bool> container = {true, false};
        for (int i=0; i<100; ++i) {
            assert_in_container(random->get(), container, SPOT);
        }
    }

    void test_random_real()
    {
        auto randomA = unittest::make_random_value(3.);
        auto randomB = unittest::make_random_value(1.5, 4.2);
        for (int i=0; i<100; ++i) {
            assert_in_range(randomA->get(), 0, 3+1e-6, SPOT);
            assert_in_range(randomB->get(), 1.5, 4.2+1e-6, SPOT);
        }
    }

    void test_random_real_throw()
    {
        auto functor1 = [](){ unittest::make_random_value(-1.); };
        assert_throw<std::invalid_argument>(functor1, SPOT);
        auto functor2 = [](){ unittest::make_random_value(1., 1.); };
        assert_throw<std::invalid_argument>(functor2, SPOT);
        auto functor3 = [](){ unittest::make_random_value(9., 1.); };
        assert_throw<std::invalid_argument>(functor3, SPOT);
    }

    void test_random_choice_string()
    {
        const std::string characters("abc");
        auto random = unittest::make_random_choice(characters);
        for (int i=0; i<100; ++i) {
            assert_in_container(random->get(), characters, SPOT);
        }
    }

    void test_random_choice_vector()
    {
        const std::vector<double> vector = {1, 2, 3};
        auto random = unittest::make_random_choice(vector);
        for (int i=0; i<100; ++i) {
            assert_in_container(random->get(), vector, SPOT);
        }
    }

    void test_random_choice_list()
    {
        const std::list<int> a_list = {1, 2, 3};
        auto random = unittest::make_random_choice(a_list);
        for (int i=0; i<100; ++i) {
            assert_in_container(random->get(), a_list, SPOT);
        }
    }

    void test_random_container_string()
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

    void test_random_container_list()
    {
        auto random = unittest::make_random_value(1, 3);
        const unsigned length = 5;
        const unsigned min_length = 3;
        auto random_contA = unittest::make_random_container<std::list<int>>(random, length);
        auto random_contB = unittest::make_random_container<std::list<int>>(random, min_length, length);
        const std::list<int> a_list = {1, 2, 3};
        assert_random_container_fixed(random_contA, a_list, length, SPOT);
        assert_random_container_range(random_contB, a_list, min_length, length, SPOT);
    }

    void test_random_container_vector()
    {
        auto random = unittest::make_random_value(1, 3);
        const unsigned length = 5;
        const unsigned min_length = 3;
        auto random_contA = unittest::make_random_vector(random, length);
        auto random_contB = unittest::make_random_vector(random, min_length, length);
        const std::vector<int> vector = {1, 2, 3};
        assert_random_container_fixed(random_contA, vector, length, SPOT);
        assert_random_container_range(random_contB, vector, min_length, length, SPOT);
    }

    void test_random_container_throw()
    {
        auto random = unittest::make_random_value(1, 3);
        auto functor1 = [&](){ unittest::make_random_container<std::list<int>>(random, 1, 1); };
        assert_throw<std::invalid_argument>(functor1, SPOT);
        auto functor2 = [&](){ unittest::make_random_container<std::list<int>>(random, 3, 1); };
        assert_throw<std::invalid_argument>(functor2, SPOT);
    }

    void test_random_tuple()
    {
        auto rand_float = unittest::make_random_value<double>(2.0, 3.0);
        auto rand_int   = unittest::make_random_value<int>(4, 8);
        auto rand_bool  = unittest::make_random_value<bool>();
        auto random = unittest::make_random_tuple(rand_float, rand_int, rand_bool);
        const std::vector<bool> container = {true, false};
        for (int i=0; i<100; ++i) {
            const auto rand_tuple = random->get();
            assert_equal<unsigned>(3, std::tuple_size<std::tuple<float, int, bool>>::value, SPOT);
            assert_in_range(std::get<0>(rand_tuple), 2.0, 3.0, SPOT);
            assert_in_range(std::get<1>(rand_tuple), 4, 8, SPOT);
            assert_in_container(std::get<2>(rand_tuple), container, SPOT);
        }
    }

    void test_random_pair()
    {
        auto rand_float = unittest::make_random_value<double>(2.0, 3.0);
        auto rand_int   = unittest::make_random_value<int>(4, 8);
        auto random = unittest::make_random_pair(rand_float, rand_int);
        for (int i=0; i<100; ++i) {
            const auto rand_pair = random->get();
            assert_in_range(rand_pair.first, 2.0, 3.0, SPOT);
            assert_in_range(rand_pair.second, 4, 8, SPOT);
        }
    }

    void test_random_shuffle_vector()
    {
        const std::vector<int> vector = {1, 2, 3};
        auto random = unittest::make_random_shuffle(vector);
        for (int i=0; i<100; ++i) {
            const auto perm_vector = random->get();
            assert_in_container(perm_vector[0], vector, SPOT);
            assert_in_container(perm_vector[1], vector, SPOT);
            assert_in_container(perm_vector[2], vector, SPOT);
            assert_equal(6, perm_vector[0] + perm_vector[1] + perm_vector[2], SPOT);
        }
    }

    void test_random_shuffle_list()
    {
        const std::list<double> a_list = {1, 2, 3};
        auto random = unittest::make_random_shuffle(a_list, 2);
        for (int i=0; i<100; ++i) {
            const auto perm_list = random->get();
            auto first = std::begin(perm_list);
            auto sum = *first;
            assert_in_container(*first, a_list, SPOT);
            ++first;
            sum += *first;
            assert_in_container(*first, a_list, SPOT);
            assert_in_range(sum, 3, 5, SPOT);
        }
    }

    void test_random_shuffle_throw()
    {
        const std::list<int> a_list = {1, 2, 3};
        auto functor1 = [&](){ unittest::make_random_shuffle(a_list, 0); };
        assert_throw<std::invalid_argument>(functor1, SPOT);
        auto functor2 = [&](){ unittest::make_random_shuffle(a_list, 4); };
        assert_throw<std::invalid_argument>(functor2, SPOT);
    }

    void test_random_combination_vector()
    {
        const std::vector<int> vector1 = {1, 2, 3};
        const std::vector<double> vector2 = {5, 6};
        auto rand_combo = unittest::make_random_combination(vector1, vector2, 4);
        for (int i=0; i<100; ++i) {
            const auto combo = rand_combo->get();
            assert_equal<unsigned>(4, combo.size(), SPOT);
            for (auto& value : combo) {
                assert_in_container(value.first, vector1, SPOT);
                assert_in_container(value.second, vector2, SPOT);
            }
        }
    }

    void test_random_combination_list()
    {
        const std::list<int> list1 = {1, 2, 3};
        const std::list<double> list2 = {5, 6};
        auto rand_combo = unittest::make_random_combination(list1, list2, 3);
        for (int i=0; i<100; ++i) {
            const auto combo = rand_combo->get();
            assert_equal<unsigned>(3, combo.size(), SPOT);
            for (auto& value : combo) {
                assert_in_container(value.first, list1, SPOT);
                assert_in_container(value.second, list2, SPOT);
            }
        }
    }

    void test_random_combination_throw()
    {
        const std::list<int> list1 = {1, 2, 3};
        const std::list<double> list2 = {5, 6};
        auto functor1 = [&]() { unittest::make_random_combination(list1, list2, 0); };
        assert_throw<std::invalid_argument>(functor1, SPOT);
        auto functor2 = [&]() { unittest::make_random_combination(list1, list2, 7); };
        assert_throw<std::invalid_argument>(functor2, SPOT);
    }

    void test_random_value_copy_constructor()
    {
        unittest::random_value<double> random1;
        random1.get();
        unittest::random_value<double> random2(random1);
        assert_equal(random1.get(), random2.get(), SPOT);
    }

    void test_random_value_assignment_operator()
    {
        unittest::random_value<double> random1;
        random1.get();
        random1.get();
        unittest::random_value<double> random2 = random1;
        assert_equal(random1.get(), random2.get(), SPOT);
    }

    void test_random_value_clone()
    {
        auto random1 = unittest::make_random_value<double>();
        random1->get();
        auto random2 = random1->clone();
        assert_equal(random1->get(), random2->get(), SPOT);
    }

    void test_random_value_thread_safety()
    {
        auto random1 = unittest::make_random_value<double>();
        auto random2 = unittest::make_random_value<int>(0, 1000);
        std::vector<std::function<void()>> functions(100);
        std::exception_ptr ptr;
        std::mutex except_mutex;
        for (auto& function : functions)
            function = std::move([&]() {
            try {
                auto seed = random2->get();
                assert_in_range(seed, 0, 1000, SPOT);
                random1->seed(seed);
                assert_in_range(random1->get(), 0, 1, SPOT);
                auto random3 = random1->clone();
                assert_in_range(random3->get(), 0, 1, SPOT);
                auto random4 = random2->clone();
                assert_in_range(random4->get(), 0, 1000, SPOT);
            } catch (...) {
                std::lock_guard<std::mutex> lock(except_mutex);
                ptr = std::current_exception();
            }
        });
        unittest::core::call_functions(functions, 100);
        if (ptr)
            std::rethrow_exception(ptr);
    }

};

REGISTER(test_random)
