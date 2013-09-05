#pragma once
#include "libunittest/unittest.hpp"

struct test_random final : unittest::testcase<> {

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
        UNITTEST_RUN(test_random_shuffle_vector)
        UNITTEST_RUN(test_random_shuffle_list)
        UNITTEST_RUN(test_random_shuffle_throw)
        UNITTEST_RUN(test_random_combination_vector)
        UNITTEST_RUN(test_random_combination_list)
        UNITTEST_RUN(test_random_combination_throw)
    }

    void test_random_int();
    void test_random_int_throw();
    void test_random_bool();
    void test_random_real();
    void test_random_real_throw();

    void test_random_choice_string();
    void test_random_choice_vector();
    void test_random_choice_list();

    void test_random_container_string();
    void test_random_container_list();
    void test_random_container_vector();
    void test_random_container_throw();

    void test_random_shuffle_vector();
    void test_random_shuffle_list();
    void test_random_shuffle_throw();

    void test_random_combination_vector();
    void test_random_combination_list();
    void test_random_combination_throw();

private:

    template<typename RandomCont,
             typename OrigContainer,
             typename T>
    void assert_random_container_fixed(RandomCont& random_object,
                                       const OrigContainer& container,
                                       const T& length,
                                       const std::string& spot)
    {
        for (int i=0; i<100; ++i) {
            const auto rand_cont = random_object.get();
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
            const auto rand_cont = random_object.get();
            assert_in_range(rand_cont.size(), min_length, max_length, spot);
            for (auto& value : rand_cont)
                assert_in_container(value, container, spot);
        }
    }

};
