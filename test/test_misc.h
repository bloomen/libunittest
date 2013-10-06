#pragma once
#include <libunittest/unittest.hpp>

struct context {};

struct test_misc final : unittest::testcase<context> {

    static void run()
    {
        UNITTEST_CLASS(test_misc)
        UNITTEST_RUN(test_version)
        UNITTEST_RUN(test_join)
        UNITTEST_RUN(test_write_to_stream)
        UNITTEST_RUN(test_write_to_stream_overload)
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
        UNITTEST_RUN(test_write_horizontal_bar)
        UNITTEST_RUN(test_teststatus_integrals)
        UNITTEST_RUN(test_testlog_defaults)
        UNITTEST_RUN(test_testresults_defaults)
        UNITTEST_RUN(test_testcase_fail)
        UNITTEST_RUN(test_testcase_fail_overload)
        UNITTEST_RUN(test_testcase_has_no_context)
        context cxt;
        UNITTEST_RUNCXT(cxt, test_testcase_has_context)
        UNITTEST_RUN(test_duration_in_seconds)
        UNITTEST_RUN(test_unittest_spot)
        UNITTEST_RUN(test_is_test_executed)
        UNITTEST_RUN(test_formatting_str)
        UNITTEST_RUN(test_xml_escape)
        UNITTEST_RUN(test_make_iso_timestamp)
        UNITTEST_RUN(test_call_functions_empty_vector)
        UNITTEST_RUN(test_call_functions_vector_size_one)
        UNITTEST_RUN(test_call_functions_vector_size_two)
    }

    void test_version();
    void test_join();
    void test_write_to_stream();
    void test_write_to_stream_overload();
    void test_userargs_defaults();
    void test_userargs_set_get();
    void test_write_xml_empty();
    void test_write_xml_filled();
    void test_write_summary_empty();
    void test_write_summary_filled();
    void test_write_error_info_empty();
    void test_write_error_info_filled();
    void test_write_test_start_message();
    void test_write_test_end_message();
    void test_write_horizontal_bar();
    void test_teststatus_integrals();
    void test_testlog_defaults();
    void test_testresults_defaults();
    void test_testcase_fail();
    void test_testcase_fail_overload();
    void test_testcase_has_no_context();
    void test_testcase_has_context();
    void test_duration_in_seconds();
    void test_unittest_spot();
    void test_is_test_executed();
    void test_formatting_str();
    void test_xml_escape();
    void test_make_iso_timestamp();
    void test_call_functions_empty_vector();
    void test_call_functions_vector_size_one();
    void test_call_functions_vector_size_two();

private:
    unittest::testresults make_sample_results();

};
