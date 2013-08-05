#include "test_misc.h"
#define SPOT UNITTEST_SPOT

unittest::testresults test_misc::make_sample_results()
{
    unittest::testlog log1;
    log1.class_name = "test_class";
    log1.test_name = "test1";
    log1.successful = true;
    log1.status = unittest::teststatus::success;
    log1.error_type = "";
    log1.message = "message1";
    log1.duration = 1;

    unittest::testlog log2;
    log2.class_name = "test_class";
    log2.test_name = "test2";
    log2.successful = false;
    log2.status = unittest::teststatus::failure;
    log2.error_type = "failure";
    log2.message = "message2";
    log2.duration = 2;

    unittest::testlog log3;
    log3.class_name = "test_class";
    log3.test_name = "test3";
    log3.successful = false;
    log3.status = unittest::teststatus::error;
    log3.error_type = "error";
    log3.message = "message3";
    log3.duration = 3;

    unittest::testresults results;
    results.successful = false;
    results.n_tests = 3;
    results.n_successes = 1;
    results.n_failures = 1;
    results.n_errors = 1;
    results.n_skipped = 2;
    results.duration = 6;
    results.testlogs = {log1, log2, log3};

    return std::move(results);
}

void test_misc::test_get_version_tuple()
{
    const std::tuple<int,int,int,std::string> version(unittest::get_version_tuple());
}

void test_misc::test_get_version_string()
{
    int a, b, c;
    std::string flag;
    std::tie(a, b, c, flag) = unittest::get_version_tuple();
    assert_equal(unittest::join(a, ".", b, ".", c, flag), unittest::get_version_string());
}

void test_misc::test_join()
{
    const std::string value_string("pi");
    assert_equal(value_string, unittest::join(value_string), SPOT);
    const double value_double(3.1415);
    assert_equal("3.1415", unittest::join(value_double), SPOT);
    assert_equal("pi = 3.1415", unittest::join(value_string, " = ", value_double), SPOT);
}

void test_misc::test_write_to_stream()
{
    std::ostringstream stream;
    const std::string value_string("pi");
    const double value_double(3.1415);
    unittest::write_to_stream(stream, value_string, " = ", value_double);
    assert_equal("pi = 3.1415", stream.str(), SPOT);
}

void test_misc::test_write_to_stream_overload()
{
    std::ostringstream stream;
    unittest::write_to_stream(stream);
    assert_equal("", stream.str(), SPOT);
}

void test_misc::test_userargs_defaults()
{
    unittest::userargs args;
    assert_equal(false, args.verbose(), SPOT);
    assert_equal(false, args.failure_stop(), SPOT);
    assert_equal(false, args.generate_xml(), SPOT);
    assert_equal(true, args.handle_exceptions(), SPOT);
    assert_equal("", args.name_filter(), SPOT);
    assert_equal("", args.test_name(), SPOT);
    assert_equal(-1, args.timeout(), SPOT);
    assert_equal("libunittest.xml", args.xml_filename(), SPOT);
}

void test_misc::test_userargs_set_get()
{
    unittest::userargs args;
    args.verbose(true);
    args.failure_stop(true);
    args.generate_xml(true);
    args.handle_exceptions(false);
    args.name_filter("test_me");
    args.test_name("test_me_more");
    args.timeout(10);
    args.xml_filename("awesome_tests.xml");
    assert_equal(true, args.verbose(), SPOT);
    assert_equal(true, args.failure_stop(), SPOT);
    assert_equal(true, args.generate_xml(), SPOT);
    assert_equal(false, args.handle_exceptions(), SPOT);
    assert_equal("test_me", args.name_filter(), SPOT);
    assert_equal("test_me_more", args.test_name(), SPOT);
    assert_equal(10, args.timeout(), SPOT);
    assert_equal("awesome_tests.xml", args.xml_filename(), SPOT);
}

void test_misc::test_write_xml_empty()
{
    const unittest::testresults results;
    std::ostringstream stream;
    const time_t value = 1234567890;
    const auto time_point = std::chrono::system_clock::from_time_t(value);
    unittest::write_xml(stream, results, time_point);
    std::ostringstream expected;
    expected << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    expected << "<testsuite name=\"libunittest\" ";
    expected << "timestamp=\"2009-02-14T00:31:30\" ";
    expected << "tests=\"0\" errors=\"0\" ";
    expected << "failures=\"0\" skipped=\"0\" time=\"0.000000\">\n";
    expected << "</testsuite>\n";
    assert_equal(expected.str(), stream.str(), SPOT);
}

void test_misc::test_write_xml_filled()
{
    const auto results = make_sample_results();
    std::ostringstream stream;
    const time_t value = 1234567890;
    const auto time_point = std::chrono::system_clock::from_time_t(value);
    unittest::write_xml(stream, results, time_point);
    std::ostringstream expected;
    expected << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    expected << "<testsuite name=\"libunittest\" ";
    expected << "timestamp=\"2009-02-14T00:31:30\" ";
    expected << "tests=\"3\" errors=\"1\" ";
    expected << "failures=\"1\" skipped=\"2\" time=\"6.000000\">\n";
    expected << "\t<testcase classname=\"test_class\" name=\"test1\" time=\"1.000000\"/>\n";
    expected << "\t<testcase classname=\"test_class\" name=\"test2\" time=\"2.000000\">\n";
    expected << "\t\t<failure type=\"failure\" message=\"message2\"/>\n";
    expected << "\t</testcase>\n";
    expected << "\t<testcase classname=\"test_class\" name=\"test3\" time=\"3.000000\">\n";
    expected << "\t\t<error type=\"error\" message=\"message3\"/>\n";
    expected << "\t</testcase>\n";
    expected << "</testsuite>\n";
    assert_equal(expected.str(), stream.str(), SPOT);
}

void test_misc::test_write_summary_empty()
{
    const unittest::testresults results;
    std::ostringstream stream;
    unittest::write_summary(stream, results);
    std::ostringstream expected;
    expected << "\n";
    unittest::write_horizontal_bar(expected, '-');
    expected << "\nRan 0 tests in 0s\n\nOK\n";
    assert_equal(expected.str(), stream.str(), SPOT);
}

void test_misc::test_write_summary_filled()
{
    const auto results = make_sample_results();
    std::ostringstream stream;
    unittest::write_summary(stream, results);
    std::ostringstream expected;
    expected << "\n";
    unittest::write_horizontal_bar(expected, '-');
    expected << "\nRan 3 tests in 6s\n\nFAILED (failures=1, errors=1)\n";
    assert_equal(expected.str(), stream.str(), SPOT);
}

void test_misc::test_write_error_info_empty()
{
    const unittest::testresults results;
    std::ostringstream stream;
    unittest::write_error_info(stream, results);
    assert_equal("", stream.str(), SPOT);
}

void test_misc::test_write_error_info_filled()
{
    const auto results = make_sample_results();
    std::ostringstream stream;
    unittest::write_error_info(stream, results);
    std::ostringstream expected;
    expected << "\n";
    unittest::write_horizontal_bar(expected, '=');
    expected << "\nFAIL: test_class.test2\n";
    unittest::write_horizontal_bar(expected, '-');
    expected << "\nfailure: message2\n\n";
    unittest::write_horizontal_bar(expected, '=');
    expected << "\nERROR: test_class.test3\n";
    unittest::write_horizontal_bar(expected, '-');
    expected << "\nerror: message3\n\n";
    assert_equal(expected.str(), stream.str(), SPOT);
}

void test_misc::test_write_test_start_message()
{
    unittest::testlog log;
    log.class_name = "stuff";
    log.test_name = "test_me";

    std::ostringstream stream;
    unittest::write_test_start_message(stream, log, false);
    assert_equal("", stream.str(), SPOT);

    std::ostringstream stream2;
    unittest::write_test_start_message(stream2, log, true);
    assert_equal("stuff.test_me ... ", stream2.str(), SPOT);
}

void test_misc::test_write_test_end_message()
{
    const std::vector<unittest::teststatus> statuses = {
            unittest::teststatus::success,
            unittest::teststatus::failure,
            unittest::teststatus::error,
            unittest::teststatus::skipped
    };
    const std::vector<std::string> msg = {
            ".", "F", "E", ""
    };
    const std::vector<std::string> msg_verb = {
            "ok\n", "FAIL\n", "ERROR\n", "\n"
    };

    for (int i=0; i<4; ++i) {
        unittest::testlog log;
        log.status = statuses[i];
        std::ostringstream stream;
        unittest::write_test_end_message(stream, log, false);
        assert_equal(msg[i], stream.str(), SPOT);
        std::ostringstream stream2;
        unittest::write_test_end_message(stream2, log, true);
        assert_equal(msg_verb[i], stream2.str(), SPOT);
    }
}

void test_misc::test_write_horizontal_bar()
{
    std::ostringstream stream;
    unittest::write_horizontal_bar(stream, 'x', 3);
    assert_equal("xxx", stream.str(), SPOT);
    assert_throw<std::length_error>(std::bind(unittest::write_horizontal_bar, std::ref(stream), 'x', -1), SPOT);
}

void test_misc::test_teststatus_integrals()
{
    assert_equal<unsigned>(0, unittest::teststatus::success, SPOT);
    assert_equal<unsigned>(1, unittest::teststatus::failure, SPOT);
    assert_equal<unsigned>(2, unittest::teststatus::error, SPOT);
    assert_equal<unsigned>(3, unittest::teststatus::skipped, SPOT);
}

void test_misc::test_testlog_defaults()
{
    unittest::testlog log;
    assert_equal("", log.class_name, SPOT);
    assert_equal("", log.test_name, SPOT);
    assert_equal(true, log.successful, SPOT);
    assert_equal(unittest::teststatus::skipped, log.status, SPOT);
    assert_equal("", log.message, SPOT);
    assert_equal(0, log.duration, SPOT);
}

void test_misc::test_testresults_defaults()
{
    unittest::testresults results;
    assert_equal(true, results.successful, SPOT);
    assert_equal(0, results.n_tests, SPOT);
    assert_equal(0, results.n_successes, SPOT);
    assert_equal(0, results.n_failures, SPOT);
    assert_equal(0, results.n_errors, SPOT);
    assert_equal(0, results.n_skipped, SPOT);
    assert_equal(0, results.duration, SPOT);
    assert_equal<unsigned>(0, results.testlogs.size(), SPOT);
}

void test_misc::test_testcase_fail()
{
    const std::string msg("a test failure");
    bool caught = false;
    try {
        fail(msg);
    } catch (const unittest::testfailure& e) {
        assert_equal(msg, e.what(), SPOT);
        caught = true;
    }
    if (!caught)
        throw unittest::testfailure("fail() did not throw 'testfailure'");
}

void test_misc::test_testcase_fail_overload()
{
    const std::string assertion("assert_it");
    const std::string msg("a test failure");
    const std::string text("some text");
    bool caught = false;
    try {
        fail(assertion, msg, text);
    } catch (const unittest::testfailure& e) {
        assert_equal(unittest::join(msg, " (", assertion, ") ", text), e.what(), SPOT);
        caught = true;
    }
    if (!caught)
        throw unittest::testfailure("fail() did not throw 'testfailure'");
}

void test_misc::test_testcase_has_no_context()
{
    assert_false(get_test_context(), SPOT);
}

void test_misc::test_testcase_has_context()
{
    assert_true(get_test_context(), SPOT);
}

void test_misc::test_duration_in_seconds()
{
    const std::chrono::duration<double> duration(1);
    assert_equal(1, unittest::duration_in_seconds(duration), SPOT);
}

void test_misc::test_unittest_spot()
{
    assert_equal(unittest::join(" @", __FILE__, ":", __LINE__, ". "), UNITTEST_SPOT);
}

void test_misc::test_is_test_executed()
{
    assert_true(unittest::is_test_executed("stuff.test_me", "", ""), SPOT);
    assert_true(unittest::is_test_executed("stuff.test_me", "", "stuff"), SPOT);
    assert_false(unittest::is_test_executed("stuff.test_me", "", "weird"), SPOT);
    assert_true(unittest::is_test_executed("stuff.test_me", "stuff.test_me", "weird"), SPOT);
    assert_false(unittest::is_test_executed("stuff.test_me", "stuff.test_me_xxx", ""), SPOT);
}

void test_misc::test_formatting_str()
{
    assert_equal("'albert'", str("albert"), SPOT);
    assert_equal("''", str(""), SPOT);
    assert_equal("'0'", str(0), SPOT);
    assert_equal("'3.1415'", str(3.1415), SPOT);
    assert_equal("'blöd'", str("blöd"), SPOT);
}

void test_misc::test_xml_escape()
{
    assert_equal("", unittest::xml_escape(""), SPOT);
    assert_equal("stuff", unittest::xml_escape("stuff"), SPOT);
    assert_equal("blöd", unittest::xml_escape("blöd"), SPOT);
    assert_equal("&amp;", unittest::xml_escape("&"), SPOT);
    assert_equal("&amp;stuff", unittest::xml_escape("&stuff"), SPOT);
    assert_equal("&amp;st uff &lt;", unittest::xml_escape("&st uff <"), SPOT);
    assert_equal("&quot;", unittest::xml_escape("\""), SPOT);
    assert_equal("&apos;", unittest::xml_escape("\'"), SPOT);
    assert_equal("&gt;", unittest::xml_escape(">"), SPOT);
}

void test_misc::test_make_iso_timestamp()
{
    const time_t value = 1234567890;
    const auto time_point = std::chrono::system_clock::from_time_t(value);
    assert_equal("2009-02-13T23:31:30", unittest::make_iso_timestamp(time_point, false), SPOT);
}
