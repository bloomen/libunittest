#include <libunittest/all.hpp>
using namespace unittest::assertions;

template<typename T, typename U> // use as many types as desired
struct templates_explicit : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(templates_explicit)
        UNITTEST_RUN(test_me<long>)
        UNITTEST_RUN(test_me<long long>)
    }

    template<typename V> // only one type can be used here
    void test_me()
    {
        T a = 1;
        U b = 2;
        V c = a + b;
        assert_equal(3, c, SPOT);
    }

};

REGISTER(templates_explicit<int, short>)
REGISTER(templates_explicit<int, int>)
REGISTER(templates_explicit<int, long>)
