#pragma once
#include "unittest.hpp"

struct test_argparser : unittest::testcase<> {

    static void run()
    {
        UNITTEST_RUN(test_argparser, test_no_arguments)
        UNITTEST_RUN(test_argparser, test_verbose)
        UNITTEST_RUN(test_argparser, test_failure_stop)
        UNITTEST_RUN(test_argparser, test_generate_xml)
        UNITTEST_RUN(test_argparser, test_handle_exceptions)
        UNITTEST_RUN(test_argparser, test_verbose_failure_stop)
        UNITTEST_RUN(test_argparser, test_verbose_generate_xml)
        UNITTEST_RUN(test_argparser, test_failure_stop_generate_xml)
        UNITTEST_RUN(test_argparser, test_verbose_failure_stop_generate_xml)
        UNITTEST_RUN(test_argparser, test_name_filter)
        UNITTEST_RUN(test_argparser, test_test_name)
        UNITTEST_RUN(test_argparser, test_xml_filename)
        UNITTEST_RUN(test_argparser, test_all_arguments)
        UNITTEST_RUN(test_argparser, test_argparser_errors)
        UNITTEST_RUN(test_argparser, test_copy_constructor)
        UNITTEST_RUN(test_argparser, test_assignment_operator)
    }

    test_argparser();
    ~test_argparser();

    void test_no_arguments();
    void test_verbose();
    void test_failure_stop();
    void test_generate_xml();
    void test_handle_exceptions();
    void test_verbose_failure_stop();
    void test_verbose_generate_xml();
    void test_failure_stop_generate_xml();
    void test_verbose_failure_stop_generate_xml();
    void test_name_filter();
    void test_test_name();
    void test_xml_filename();
    void test_all_arguments();
    void test_argparser_errors();
    void test_copy_constructor();
    void test_assignment_operator();

private:
    int max_argc_;
    char **arguments_;
};
