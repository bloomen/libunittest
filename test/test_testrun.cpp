#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>
using namespace unittest::assertions;

struct test_testrun : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_testrun)
        UNITTEST_RUN(test_make_method_id)
        UNITTEST_RUN(test_update_local_timeout)
        UNITTEST_RUN(test_update_class_name)
        UNITTEST_RUN(test_update_test_name)
        UNITTEST_RUN(test_update_class_name_key_not_found)
        UNITTEST_RUN(test_update_test_name_key_not_found)
    }

    void test_make_method_id()
    {
        const std::string id = typeid(double).name();
        assert_equal(id + "_m", unittest::core::make_method_id<double>("_m"));
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

    void test_update_class_name()
    {
        auto function = unittest::core::update_class_name;
        std::map<std::string, std::string> maps;
        maps["a"] = "A";
        maps["b"] = "B";
        std::string name;
        name = "AA";
        function(name, "a", maps);
        assert_equal("AA", name, SPOT);
        name = "";
        function(name, "a", maps);
        assert_equal("A", name, SPOT);
        name = unittest::core::testcollection::inactive_name();
        function(name, "a", maps);
        assert_equal("", name, SPOT);
    }

    void test_update_test_name()
    {
        auto function = unittest::core::update_test_name;
        std::map<std::string, std::string> maps;
        maps["a"] = "A";
        maps["b"] = "B";
        std::string name;
        name = "AA";
        function(name, "a", maps);
        assert_equal("AA", name, SPOT);
        name = "";
        function(name, "a", maps);
        assert_equal("A::test", name, SPOT);
    }

    void test_update_class_name_key_not_found()
    {
        std::map<std::string, std::string> maps;
        maps["a"] = "A";
        std::string name = "";
        auto functor = [&](){ unittest::core::update_test_name(name, "b", maps); };
        assert_throw<std::runtime_error>(functor, SPOT);
    }

    void test_update_test_name_key_not_found()
    {
        std::map<std::string, std::string> maps;
        maps["a"] = "A";
        std::string name = "";
        auto functor = [&](){ unittest::core::update_test_name(name, "b", maps); };
        assert_throw<std::runtime_error>(functor, SPOT);
    }

};

REGISTER(test_testrun)
