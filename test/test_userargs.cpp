#include <libunittest/all.hpp>
using namespace unittest::assertions;
using unittest::core::userargs;
using unittest::core::argparser;

struct test_userargs : unittest::testcase<> {

    test_userargs(const test_userargs&) = delete;
    test_userargs& operator=(const test_userargs&) = delete;

    static void run()
    {
        UNITTEST_CLASS(test_userargs)
        UNITTEST_RUN(test_no_arguments)
        UNITTEST_RUN(test_verbose)
        UNITTEST_RUN(test_failure_stop)
        UNITTEST_RUN(test_generate_xml)
        UNITTEST_RUN(test_handle_exceptions)
        UNITTEST_RUN(test_dry_run)
        UNITTEST_RUN(test_concurrent_threads)
        UNITTEST_RUN(test_name_filter)
        UNITTEST_RUN(test_test_name)
        UNITTEST_RUN(test_timeout)
        UNITTEST_RUN(test_xml_filename)
        UNITTEST_RUN(test_suite_name)
        UNITTEST_RUN(test_disable_timeout)
        UNITTEST_RUN(test_max_string_length)
        UNITTEST_RUN(test_max_value_precision)
        UNITTEST_RUN(test_verbose_failure_stop)
        UNITTEST_RUN(test_verbose_generate_xml)
        UNITTEST_RUN(test_failure_stop_generate_xml)
        UNITTEST_RUN(test_verbose_failure_stop_generate_xml)
        UNITTEST_RUN(test_all_arguments)
        UNITTEST_RUN(test_parsing_errors)
    }

    int max_argc_;
    char **arguments_;

    test_userargs()
    : max_argc_(22), arguments_(nullptr)
    {
        arguments_ = new char*[max_argc_];
        arguments_[0] = (char*)"unittest_app";
    }

    ~test_userargs()
    {
        delete[] arguments_;
        arguments_ = nullptr;
    }

    void test_no_arguments()
    {
        userargs args;
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_verbose()
    {
        arguments_[1] = (char*)"-v";
        userargs args;
        args.parse(2, arguments_);
        assert_equal(true, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_failure_stop()
    {
        arguments_[1] = (char*)"-s";
        userargs args;
        args.parse(2, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(true, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_generate_xml()
    {
        arguments_[1] = (char*)"-x";
        userargs args;
        args.parse(2, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(true, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_handle_exceptions()
    {
        arguments_[1] = (char*)"-e";
        userargs args;
        args.parse(2, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(false, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_dry_run()
    {
        arguments_[1] = (char*)"-d";
        userargs args;
        args.parse(2, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(true, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_concurrent_threads()
    {
        arguments_[1] = (char*)"-p";
        arguments_[2] = (char*)"3";
        userargs args;
        args.parse(3, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal(3, args.concurrent_threads, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_name_filter()
    {
        arguments_[1] = (char*)"-f";
        arguments_[2] = (char*)"stuff";
        userargs args;
        args.parse(3, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("stuff", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_test_name()
    {
        arguments_[1] = (char*)"-n";
        arguments_[2] = (char*)"test_me";
        userargs args;
        args.parse(3, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("test_me", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_timeout()
    {
        arguments_[1] = (char*)"-t";
        arguments_[2] = (char*)"3.5";
        userargs args;
        args.parse(3, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(3.5, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_xml_filename()
    {
        arguments_[1] = (char*)"-o";
        arguments_[2] = (char*)"stuff.xml";
        userargs args;
        args.parse(3, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(true, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("stuff.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_suite_name()
    {
        arguments_[1] = (char*)"-u";
        arguments_[2] = (char*)"stuff";
        userargs args;
        args.parse(3, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("stuff", args.suite_name, SPOT);
    }

    void test_disable_timeout()
    {
        arguments_[1] = (char*)"-i";
        userargs args;
        args.parse(2, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(true, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_max_string_length()
    {
        arguments_[1] = (char*)"-l";
        arguments_[2] = (char*)"13";
        userargs args;
        args.parse(3, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(13, args.max_string_length, SPOT);
        assert_equal(-1, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_max_value_precision()
    {
        arguments_[1] = (char*)"-r";
        arguments_[2] = (char*)"42";
        userargs args;
        args.parse(3, arguments_);
        assert_equal(false, args.verbose, SPOT);
        assert_equal(false, args.failure_stop, SPOT);
        assert_equal(false, args.generate_xml, SPOT);
        assert_equal(true, args.handle_exceptions, SPOT);
        assert_equal(false, args.dry_run, SPOT);
        assert_equal(false, args.disable_timeout, SPOT);
        assert_equal("", args.name_filter, SPOT);
        assert_equal("", args.test_name, SPOT);
        assert_equal(-1, args.timeout, SPOT);
        assert_equal("libunittest.xml", args.xml_filename, SPOT);
        assert_equal(500, args.max_string_length, SPOT);
        assert_equal(42, args.max_value_precision, SPOT);
        assert_equal("libunittest", args.suite_name, SPOT);
    }

    void test_verbose_failure_stop()
    {
        const std::vector<char*> values = {(char*)"-vs", (char*)"-sv"};
        for (auto value : values) {
            arguments_[1] = value;
            userargs args;
            args.parse(2, arguments_);
            assert_equal(true, args.verbose, SPOT);
            assert_equal(true, args.failure_stop, SPOT);
            assert_equal(false, args.generate_xml, SPOT);
            assert_equal(true, args.handle_exceptions, SPOT);
            assert_equal(false, args.dry_run, SPOT);
            assert_equal(false, args.disable_timeout, SPOT);
            assert_equal("", args.name_filter, SPOT);
            assert_equal("", args.test_name, SPOT);
            assert_equal(-1, args.timeout, SPOT);
            assert_equal("libunittest.xml", args.xml_filename, SPOT);
            assert_equal(500, args.max_string_length, SPOT);
            assert_equal(-1, args.max_value_precision, SPOT);
            assert_equal("libunittest", args.suite_name, SPOT);
        }
    }

    void test_verbose_generate_xml()
    {
        const std::vector<char*> values = {(char*)"-vx", (char*)"-xv"};
        for (auto value : values) {
            arguments_[1] = value;
            userargs args;
            args.parse(2, arguments_);
            assert_equal(true, args.verbose, SPOT);
            assert_equal(false, args.failure_stop, SPOT);
            assert_equal(true, args.generate_xml, SPOT);
            assert_equal(true, args.handle_exceptions, SPOT);
            assert_equal(false, args.dry_run, SPOT);
            assert_equal(false, args.disable_timeout, SPOT);
            assert_equal("", args.name_filter, SPOT);
            assert_equal("", args.test_name, SPOT);
            assert_equal(-1, args.timeout, SPOT);
            assert_equal("libunittest.xml", args.xml_filename, SPOT);
            assert_equal(500, args.max_string_length, SPOT);
            assert_equal(-1, args.max_value_precision, SPOT);
            assert_equal("libunittest", args.suite_name, SPOT);
        }
    }

    void test_failure_stop_generate_xml()
    {
        const std::vector<char*> values = {(char*)"-sx", (char*)"-xs"};
        for (auto value : values) {
            arguments_[1] = value;
            userargs args;
            args.parse(2, arguments_);
            assert_equal(false, args.verbose, SPOT);
            assert_equal(true, args.failure_stop, SPOT);
            assert_equal(true, args.generate_xml, SPOT);
            assert_equal(true, args.handle_exceptions, SPOT);
            assert_equal(false, args.dry_run, SPOT);
            assert_equal(false, args.disable_timeout, SPOT);
            assert_equal("", args.name_filter, SPOT);
            assert_equal("", args.test_name, SPOT);
            assert_equal(-1, args.timeout, SPOT);
            assert_equal("libunittest.xml", args.xml_filename, SPOT);
            assert_equal(500, args.max_string_length, SPOT);
            assert_equal(-1, args.max_value_precision, SPOT);
            assert_equal("libunittest", args.suite_name, SPOT);
        }
    }

    void test_verbose_failure_stop_generate_xml()
    {
        const std::vector<char*> values = {
                (char*)"-vsx", (char*)"-vxs", (char*)"-svx",
                (char*)"-xvs", (char*)"-sxv", (char*)"-xsv"
        };
        for (auto value : values) {
            arguments_[1] = value;
            userargs args;
            args.parse(2, arguments_);
            assert_equal(true, args.verbose, SPOT);
            assert_equal(true, args.failure_stop, SPOT);
            assert_equal(true, args.generate_xml, SPOT);
            assert_equal(true, args.handle_exceptions, SPOT);
            assert_equal(false, args.dry_run, SPOT);
            assert_equal(false, args.disable_timeout, SPOT);
            assert_equal("", args.name_filter, SPOT);
            assert_equal("", args.test_name, SPOT);
            assert_equal(-1, args.timeout, SPOT);
            assert_equal("libunittest.xml", args.xml_filename, SPOT);
            assert_equal(500, args.max_string_length, SPOT);
            assert_equal(-1, args.max_value_precision, SPOT);
            assert_equal("libunittest", args.suite_name, SPOT);
        }
    }

    void test_all_arguments()
    {
        arguments_[1] = (char*)"-v";
        arguments_[2] = (char*)"-s";
        arguments_[3] = (char*)"-xe";
        arguments_[4] = (char*)"-f";
        arguments_[5] = (char*)"stuff";
        arguments_[6] = (char*)"-n";
        arguments_[7] = (char*)"test_me";
        arguments_[8] = (char*)"-t";
        arguments_[9] = (char*)"10";
        arguments_[10] = (char*)"-o";
        arguments_[11] = (char*)"stuff.xml";
        arguments_[12] = (char*)"-d";
        arguments_[13] = (char*)"-p";
        arguments_[14] = (char*)"3";
        arguments_[15] = (char*)"-i";
        arguments_[16] = (char*)"-l";
        arguments_[17] = (char*)"13";
        arguments_[18] = (char*)"-r";
        arguments_[19] = (char*)"42";
        arguments_[20] = (char*)"-u";
        arguments_[21] = (char*)"peter";
        userargs args;
        args.parse(22, arguments_);
        assert_equal(true, args.verbose, SPOT);
        assert_equal(true, args.failure_stop, SPOT);
        assert_equal(true, args.generate_xml, SPOT);
        assert_equal(false, args.handle_exceptions, SPOT);
        assert_equal(true, args.dry_run, SPOT);
        assert_equal(true, args.disable_timeout, SPOT);
        assert_equal(3, args.concurrent_threads, SPOT);
        assert_equal("stuff", args.name_filter, SPOT);
        assert_equal("test_me", args.test_name, SPOT);
        assert_equal(10, args.timeout, SPOT);
        assert_equal("stuff.xml", args.xml_filename, SPOT);
        assert_equal(13, args.max_string_length, SPOT);
        assert_equal(42, args.max_value_precision, SPOT);
        assert_equal("peter", args.suite_name, SPOT);
    }

    void test_parsing_errors()
    {
        const std::vector<char*> values = {
                (char*)"-g", (char*)"-f", (char*)"-t", (char*)"-o", (char*)"--h"
        };
        for (auto value : values) {
            arguments_[1] = value;
            userargs args;
            assert_throw<argparser::exit_error>([&](){ args.parse(2, arguments_); }, SPOT);
        }
    }

};

REGISTER(test_userargs)
