#include <libunittest/all.hpp>
using namespace unittest::assertions;

template<typename T, typename U>
struct templates_flexible : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(templates_flexible)
        UNITTEST_RUN(test_me<long>)
        UNITTEST_RUN(test_me<long long>)
    }

    template<typename V>
    void test_me()
    {
        T a = 1;
        U b = 2;
        V c = a + b;
        assert_equal(3, c, SPOT);
    }

};

REGISTER(templates_flexible<int, short>)
REGISTER(templates_flexible<int, int>)
REGISTER(templates_flexible<int, long>)
