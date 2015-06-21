#include <libunittest/all.hpp>
using namespace unittest::assertions;

struct test_testrun : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_testrun)
        UNITTEST_RUN(test_make_method_id)
        UNITTEST_RUN(test_update_local_timeout)
    }

    void test_make_method_id()
    {
        const std::string id = typeid(double).name();
        assert_equal(id + "_m", unittest::core::make_method_id(id, "_m"));
    }

    void test_update_local_timeout()
    {
        auto function = unittest::core::update_local_timeout;
        double local_timeout = 1;
        double global_timeout = 2;
        function(local_timeout, global_timeout);
        assert_equal(1, local_timeout, SPOT);
        local_timeout = 0;
        function(local_timeout, global_timeout);
        assert_equal(2, local_timeout, SPOT);
    }

};

REGISTER(test_testrun)
