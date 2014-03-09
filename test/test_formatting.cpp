#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>
using unittest::internals::formatting;

struct new_form : formatting {
    virtual int
    max_displayed_value_precision() const
    {
        return 2;
    }

    virtual int
    max_displayed_string_length() const
    {
        return 4;
    }
};

struct test_formatting : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_formatting)
        UNITTEST_RUN(test_max_displayed_string_length)
        UNITTEST_RUN(test_max_displayed_value_precision)
        UNITTEST_RUN(test_make_displayed_fail_message)
        UNITTEST_RUN(test_str)
        UNITTEST_RUN(test_str_changed_defaults)
    }

    void test_max_displayed_string_length()
    {
        formatting form;
        assert_equal(500, form.max_displayed_string_length(), SPOT);
    }

    void test_max_displayed_value_precision()
    {
        formatting form;
        assert_equal(10, form.max_displayed_value_precision(), SPOT);
    }

    void test_make_displayed_fail_message()
    {
        formatting form;
        const std::string message = form.make_displayed_fail_message("assert_me", "text");
        assert_equal("text  (assert_me) ", message, SPOT);
    }

    void test_str()
    {
        formatting form;
        assert_equal("'1'", form.str(1), SPOT);
        assert_equal("'albert'", form.str("albert"), SPOT);
        assert_equal("''", form.str(""), SPOT);
        assert_equal("'0'", form.str(0), SPOT);
        assert_equal("'3.1415'", form.str(3.1415), SPOT);
        assert_equal("'blöd'", form.str("blöd"), SPOT);
    }

    void test_str_changed_defaults()
    {
        new_form form;
        assert_equal("'1'", form.str(1), SPOT);
        assert_equal("'albe'", form.str("albert"), SPOT);
        assert_equal("''", form.str(""), SPOT);
        assert_equal("'0'", form.str(0), SPOT);
        assert_equal("'3.1'", form.str(3.1415), SPOT);
        assert_equal("'blö'", form.str("blöd"), SPOT);
    }

};

REGISTER(test_formatting)
