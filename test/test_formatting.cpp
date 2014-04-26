#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>
using unittest::internals::formatting;

struct new_form : formatting {
    virtual int
    __max_displayed_value_precision() const
    {
        return 2;
    }

    virtual int
    __max_displayed_string_length() const
    {
        return 4;
    }
};

struct test_formatting : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_formatting)
        UNITTEST_RUN(test___max_displayed___string_length)
        UNITTEST_RUN(test___max_displayed_value_precision)
        UNITTEST_RUN(test___displayed_fail_message)
        UNITTEST_RUN(test___str)
        UNITTEST_RUN(test___str_changed_defaults)
    }

    void test___max_displayed___string_length()
    {
        formatting form;
        assert_equal(500, form.__max_displayed_string_length(), SPOT);
    }

    void test___max_displayed_value_precision()
    {
        formatting form;
        assert_equal(10, form.__max_displayed_value_precision(), SPOT);
    }

    void test___displayed_fail_message()
    {
        formatting form;
        const std::string message = form.__displayed_fail_message("assert_me", "text");
        assert_equal("text", message, SPOT);
    }

    void test___str()
    {
        formatting form;
        assert_equal("'1'", form.__str(1), SPOT);
        assert_equal("'albert'", form.__str("albert"), SPOT);
        assert_equal("''", form.__str(""), SPOT);
        assert_equal("'0'", form.__str(0), SPOT);
        assert_equal("'3.1415'", form.__str(3.1415), SPOT);
        assert_equal("'blöd'", form.__str("blöd"), SPOT);
    }

    void test___str_changed_defaults()
    {
        new_form form;
        assert_equal("'1'", form.__str(1), SPOT);
        assert_equal("'albe'", form.__str("albert"), SPOT);
        assert_equal("''", form.__str(""), SPOT);
        assert_equal("'0'", form.__str(0), SPOT);
        assert_equal("'3.1'", form.__str(3.1415), SPOT);
        assert_equal("'blö'", form.__str("blöd"), SPOT);
    }

};

REGISTER(test_formatting)
