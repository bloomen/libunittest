#include <libunittest/all.hpp>
using namespace unittest::assertions;
using namespace unittest::core;

struct test_formatting : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_formatting)
        UNITTEST_RUN(test_str)
    }

    void test_str()
    {
        assert_equal("1", str(1), SPOT);
        assert_equal("-197", str(-197), SPOT);
        assert_equal("'albert'", str("albert"), SPOT);
        assert_equal("''", str(""), SPOT);
        assert_equal("0", str(0), SPOT);
        assert_equal("3.1415", str(3.1415), SPOT);
        assert_equal("'blöd'", str("blöd"), SPOT);
        assert_equal("true", str(true), SPOT);
        assert_equal("false", str(false), SPOT);
    }

};

REGISTER(test_formatting)
