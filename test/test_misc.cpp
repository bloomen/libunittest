#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>

unittest::internals::testresults make_sample_results()
{
    unittest::internals::testlog log1;
    log1.class_name = "test_class";
    log1.test_name = "test1";
    log1.successful = true;
    log1.status = unittest::internals::teststatus::success;
    log1.error_type = "";
    log1.message = "message1";
    log1.duration = 1;

    unittest::internals::testlog log2;
    log2.class_name = "test_class";
    log2.test_name = "test2";
    log2.successful = false;
    log2.status = unittest::internals::teststatus::failure;
    log2.error_type = "failure";
    log2.message = "message2";
    log2.duration = 2;
    log2.has_timed_out = true;
    log2.timeout = 2.4;

    unittest::internals::testlog log3;
    log3.class_name = "test_class";
    log3.test_name = "test3";
    log3.successful = false;
    log3.status = unittest::internals::teststatus::error;
    log3.error_type = "error";
    log3.message = "message3";
    log3.duration = 3;

    unittest::internals::testresults results;
    results.successful = false;
    results.n_tests = 3;
    results.n_successes = 1;
    results.n_failures = 1;
    results.n_errors = 1;
    results.n_timeouts = 1;
    results.n_skipped = 0;
    results.duration = 6;
    results.testlogs = {log1, log2, log3};

    return std::move(results);
}

struct test_misc : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_misc)
        UNITTEST_RUN(test_version)
        UNITTEST_RUN(test_userargs_defaults)
        UNITTEST_RUN(test_userargs_set_get)
        UNITTEST_RUN(test_write_xml_empty)
        UNITTEST_RUN(test_write_xml_filled)
        UNITTEST_RUN(test_write_summary_empty)
        UNITTEST_RUN(test_write_summary_filled)
        UNITTEST_RUN(test_write_error_info_empty)
        UNITTEST_RUN(test_write_error_info_filled)
        UNITTEST_RUN(test_write_test_start_message)
        UNITTEST_RUN(test_write_test_end_message)
        UNITTEST_RUN(test_write_test_timeout_message)
        UNITTEST_RUN(test_teststatus_integrals)
        UNITTEST_RUN(test_testlog_defaults)
        UNITTEST_RUN(test_testresults_defaults)
        UNITTEST_RUN(test_testcase_fail)
        UNITTEST_RUN(test_testcase_fail_overload)
        UNITTEST_RUN(test_unittest_spot)
        UNITTEST_RUN(test_is_test_executed)
        UNITTEST_RUN(test_make_full_test_name)
        UNITTEST_RUN(test_collection_get_name)
    }

    void test_version()
    {
        const unsigned size = 5;
        assert_greater_equal(unittest::version.size(), size);
    }

    void test_userargs_defaults()
    {
        unittest::internals::userargs args;
        assert_equal(false, args.verbose(), SPOT);
        assert_equal(false, args.failure_stop(), SPOT);
        assert_equal(false, args.generate_xml(), SPOT);
        assert_equal(true, args.handle_exceptions(), SPOT);
        assert_equal(false, args.dry_run(), SPOT);
        assert_equal(0, args.concurrent_threads(), SPOT);
        assert_equal("", args.name_filter(), SPOT);
        assert_equal("", args.test_name(), SPOT);
        assert_equal(-1, args.timeout(), SPOT);
        assert_equal("libunittest.xml", args.xml_filename(), SPOT);
    }

    void test_userargs_set_get()
    {
        unittest::internals::userargs args;
        args.verbose(true);
        args.failure_stop(true);
        args.generate_xml(true);
        args.handle_exceptions(false);
        args.dry_run(true);
        args.concurrent_threads(3);
        args.name_filter("test_me");
        args.test_name("test_me_more");
        args.timeout(10);
        args.xml_filename("awesome_tests.xml");
        assert_equal(true, args.verbose(), SPOT);
        assert_equal(true, args.failure_stop(), SPOT);
        assert_equal(true, args.generate_xml(), SPOT);
        assert_equal(false, args.handle_exceptions(), SPOT);
        assert_equal(true, args.dry_run(), SPOT);
        assert_equal(3, args.concurrent_threads(), SPOT);
        assert_equal("test_me", args.name_filter(), SPOT);
        assert_equal("test_me_more", args.test_name(), SPOT);
        assert_equal(10, args.timeout(), SPOT);
        assert_equal("awesome_tests.xml", args.xml_filename(), SPOT);
    }

    void test_write_xml_empty()
    {
        const unittest::internals::testresults results;
        std::ostringstream stream;
        const time_t value = 1234567890;
        const auto time_point = std::chrono::system_clock::from_time_t(value);
        unittest::internals::write_xml(stream, results, time_point);
        std::ostringstream expected;
        expected << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        expected << "<testsuite name=\"libunittest\" ";
        expected << "timestamp=\"2009-02-14T00:31:30\" ";
        expected << "tests=\"0\" errors=\"0\" ";
        expected << "failures=\"0\" timeouts=\"0\" skipped=\"0\" time=\"0.000000\">\n";
        expected << "</testsuite>\n";
        assert_equal(expected.str(), stream.str(), SPOT);
    }

    void test_write_xml_filled()
    {
        const auto results = make_sample_results();
        std::ostringstream stream;
        const time_t value = 1234567890;
        const auto time_point = std::chrono::system_clock::from_time_t(value);
        unittest::internals::write_xml(stream, results, time_point);
        std::ostringstream expected;
        expected << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        expected << "<testsuite name=\"libunittest\" ";
        expected << "timestamp=\"2009-02-14T00:31:30\" ";
        expected << "tests=\"3\" errors=\"1\" ";
        expected << "failures=\"1\" timeouts=\"1\" skipped=\"0\" time=\"6.000000\">\n";
        expected << "\t<testcase classname=\"test_class\" name=\"test1\" time=\"1.000000\"/>\n";
        expected << "\t<testcase classname=\"test_class\" name=\"test2\" time=\"2.000000\" timeout=\"2.400000\">\n";
        expected << "\t\t<failure type=\"failure\" message=\"message2\"/>\n";
        expected << "\t</testcase>\n";
        expected << "\t<testcase classname=\"test_class\" name=\"test3\" time=\"3.000000\">\n";
        expected << "\t\t<error type=\"error\" message=\"message3\"/>\n";
        expected << "\t</testcase>\n";
        expected << "</testsuite>\n";
        assert_equal(expected.str(), stream.str(), SPOT);
    }

    void test_write_summary_empty()
    {
        const unittest::internals::testresults results;
        std::ostringstream stream;
        unittest::internals::write_summary(stream, results);
        std::ostringstream expected;
        expected << "\n";
        unittest::internals::write_horizontal_bar(expected, '-');
        expected << "\nRan 0 tests in 0s\n\nOK\n";
        assert_equal(expected.str(), stream.str(), SPOT);
    }

    void test_write_summary_filled()
    {
        const auto results = make_sample_results();
        std::ostringstream stream;
        unittest::internals::write_summary(stream, results);
        std::ostringstream expected;
        expected << "\n";
        unittest::internals::write_horizontal_bar(expected, '-');
        expected << "\nRan 3 tests in 6s\n\nFAILED (failures=1, errors=1, timeouts=1)\n";
        assert_equal(expected.str(), stream.str(), SPOT);
    }

    void test_write_error_info_empty()
    {
        const unittest::internals::testresults results;
        std::ostringstream stream;
        unittest::internals::write_error_info(stream, results.testlogs, results.successful);
        assert_equal("", stream.str(), SPOT);
    }

    void test_write_error_info_filled()
    {
        const auto results = make_sample_results();
        std::ostringstream stream;
        unittest::internals::write_error_info(stream, results.testlogs, results.successful);
        std::ostringstream expected;
        expected << "\n";
        unittest::internals::write_horizontal_bar(expected, '=');
        expected << "\nFAIL: test_class.test2 (TIMEOUT)\n";
        unittest::internals::write_horizontal_bar(expected, '-');
        expected << "\nfailure: message2\n\n";
        unittest::internals::write_horizontal_bar(expected, '=');
        expected << "\nERROR: test_class.test3\n";
        unittest::internals::write_horizontal_bar(expected, '-');
        expected << "\nerror: message3\n\n";
        assert_equal(expected.str(), stream.str(), SPOT);
    }

    void test_write_test_start_message()
    {
        unittest::internals::testlog log;
        log.class_name = "stuff";
        log.test_name = "test_me";

        std::ostringstream stream;
        unittest::internals::write_test_start_message(stream, log, false);
        assert_equal("", stream.str(), SPOT);

        std::ostringstream stream2;
        unittest::internals::write_test_start_message(stream2, log, true);
        assert_equal("stuff.test_me ... ", stream2.str(), SPOT);
    }

    void test_write_test_end_message()
    {
        const std::vector<unittest::internals::teststatus> statuses = {
                unittest::internals::teststatus::success,
                unittest::internals::teststatus::failure,
                unittest::internals::teststatus::error,
                unittest::internals::teststatus::skipped
        };
        const std::vector<std::string> msg = {
                ".", "F", "E", ""
        };
        const std::vector<std::string> msg_verb = {
                "ok\n", "FAIL\n", "ERROR\n", "\n"
        };

        for (int i=0; i<4; ++i) {
            unittest::internals::testlog log;
            log.status = statuses[i];
            std::ostringstream stream;
            unittest::internals::write_test_end_message(stream, log, false);
            assert_equal(msg[i], stream.str(), SPOT);
            std::ostringstream stream2;
            unittest::internals::write_test_end_message(stream2, log, true);
            assert_equal(msg_verb[i], stream2.str(), SPOT);
        }
    }

    void test_write_test_timeout_message()
    {
        std::ostringstream stream1;
        unittest::internals::write_test_timeout_message(stream1, false);
        assert_equal("T", stream1.str(), SPOT);
        std::ostringstream stream2;
        unittest::internals::write_test_timeout_message(stream2, true);
        assert_equal("TIMEOUT\n", stream2.str(), SPOT);
    }

    void test_teststatus_integrals()
    {
        assert_equal<unsigned>(0, unittest::internals::teststatus::success, SPOT);
        assert_equal<unsigned>(1, unittest::internals::teststatus::failure, SPOT);
        assert_equal<unsigned>(2, unittest::internals::teststatus::error, SPOT);
        assert_equal<unsigned>(3, unittest::internals::teststatus::skipped, SPOT);
    }

    void test_testlog_defaults()
    {
        unittest::internals::testlog log;
        assert_equal("", log.class_name, SPOT);
        assert_equal("", log.test_name, SPOT);
        assert_equal(true, log.successful, SPOT);
        assert_equal(unittest::internals::teststatus::skipped, log.status, SPOT);
        assert_equal("", log.message, SPOT);
        assert_equal(0, log.duration, SPOT);
    }

    void test_testresults_defaults()
    {
        unittest::internals::testresults results;
        assert_equal(true, results.successful, SPOT);
        assert_equal(0, results.n_tests, SPOT);
        assert_equal(0, results.n_successes, SPOT);
        assert_equal(0, results.n_failures, SPOT);
        assert_equal(0, results.n_errors, SPOT);
        assert_equal(0, results.n_skipped, SPOT);
        assert_equal(0, results.duration, SPOT);
        assert_equal<unsigned>(0, results.testlogs.size(), SPOT);
    }

    void test_testcase_fail()
    {
        const std::string assertion("assert_something");
        const std::string msg("a test failure");
        bool caught = false;
        try {
            fail(assertion, msg);
        } catch (const unittest::testfailure& e) {
            assert_equal(unittest::join(msg, "  (", assertion, ") "), e.what(), SPOT);
            assert_equal(assertion, e.assertion(), SPOT);
            caught = true;
        }
        if (!caught)
            throw unittest::testfailure(__func__, "fail() did not throw 'testfailure'");
    }

    void test_testcase_fail_overload()
    {
        const std::string assertion("assert_it");
        const std::string msg("a test failure");
        const std::string text("some text");
        bool caught = false;
        try {
            fail(assertion, msg, text);
        } catch (const unittest::testfailure& e) {
            assert_equal(unittest::join(msg, "  (", assertion, ") ", text), e.what(), SPOT);
            assert_equal(assertion, e.assertion(), SPOT);
            caught = true;
        }
        if (!caught)
            throw unittest::testfailure(__func__, "fail() did not throw 'testfailure'");
    }

    void test_unittest_spot()
    {
        assert_equal(unittest::join(" @", __FILE__, ":", __LINE__, ". "), UNITTEST_SPOT);
    }

    void test_is_test_executed()
    {
        assert_true(unittest::internals::is_test_executed("stuff.test_me", "", ""), SPOT);
        assert_true(unittest::internals::is_test_executed("stuff.test_me", "", "stuff"), SPOT);
        assert_false(unittest::internals::is_test_executed("stuff.test_me", "", "weird"), SPOT);
        assert_true(unittest::internals::is_test_executed("stuff.test_me", "stuff.test_me", "weird"), SPOT);
        assert_false(unittest::internals::is_test_executed("stuff.test_me", "stuff.test_me_xxx", ""), SPOT);
    }

    void test_make_full_test_name()
    {
        assert_equal("", unittest::internals::make_full_test_name("",""), SPOT);
        assert_equal("a.b", unittest::internals::make_full_test_name("a","b"), SPOT);
        assert_equal("a.", unittest::internals::make_full_test_name("a",""), SPOT);
        assert_equal("b", unittest::internals::make_full_test_name("","b"), SPOT);
        assert_equal("a.b", unittest::internals::make_full_test_name(" a "," b  "), SPOT);
        assert_equal("a.cb", unittest::internals::make_full_test_name("a","  c  b "), SPOT);
    }

    void test_collection_get_name()
    {
        unittest::internals::testcollection collection;
        assert_equal(unittest::internals::testcollection::inactive_name(), collection.get_name(), SPOT);
    }

};

REGISTER(test_misc)
