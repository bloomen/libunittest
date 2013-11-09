#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>

struct test_testrun : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_testrun)
        UNITTEST_RUN(test_testfunctor)
        UNITTEST_RUN(test_update_class_name)
        UNITTEST_RUN(test_update_test_name)
        UNITTEST_RUN(test_update_class_name_key_not_found)
        UNITTEST_RUN(test_update_test_name_key_not_found)
    }

    struct some_class {
        bool was_run_;
        some_class()
            : was_run_(false)
        {}
        void method()
        {
            was_run_= true;
        }
    };

    void test_testfunctor()
    {
        some_class object;
        std::atomic<bool> timed_out(false);
        unittest::internals::testfunctor<some_class>
            functor(object, &some_class::method, 3.5, &timed_out);
        functor();
        assert_true(object.was_run_, SPOT);
        assert_equal(3.5, functor.timeout(), SPOT);
        assert_false(functor.has_timed_out(), SPOT);
        timed_out = true;
        assert_true(functor.has_timed_out(), SPOT);
    }

    void test_update_class_name()
    {
        auto function = unittest::internals::update_class_name;
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
        name = unittest::internals::testcollection::inactive_name();
        function(name, "a", maps);
        assert_equal("", name, SPOT);
    }

    void test_update_test_name()
    {
        auto function = unittest::internals::update_test_name;
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
    }

    void test_update_class_name_key_not_found()
    {
        auto functor = [](){
            std::map<std::string, std::string> maps;
            maps["a"] = "A";
            std::string name = "";
            unittest::internals::update_class_name(name, "b", maps);
        };
        assert_throw<std::runtime_error>(functor, SPOT);
    }

    void test_update_test_name_key_not_found()
    {
        auto functor = [](){
            std::map<std::string, std::string> maps;
            maps["a"] = "A";
            std::string name = "";
            unittest::internals::update_test_name(name, "b", maps);
        };
        assert_throw<std::runtime_error>(functor, SPOT);
    }

};

REGISTER(test_testrun)