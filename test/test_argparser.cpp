#include "test_argparser.h"
#define SPOT UNITTEST_SPOT
using unittest::argparser;

test_argparser::test_argparser()
    : max_argc_(20)
{
    arguments_ = new char*[max_argc_];
    arguments_[0] = (char*)"unittest_app";
}

test_argparser::~test_argparser()
{
    delete[] arguments_;
    arguments_ = nullptr;
}

void test_argparser::test_no_arguments()
{
    argparser args(1, arguments_);
    assert_equal(false, args.verbose(), SPOT);
    assert_equal(false, args.failure_stop(), SPOT);
    assert_equal(false, args.generate_xml(), SPOT);
    assert_equal("", args.name_filter(), SPOT);
    assert_equal("", args.test_name(), SPOT);
    assert_equal("libunittest.xml", args.xml_filename(), SPOT);
}

void test_argparser::test_verbose()
{
    arguments_[1] = (char*)"-v";
    argparser args(2, arguments_);
    assert_equal(true, args.verbose(), SPOT);
    assert_equal(false, args.failure_stop(), SPOT);
    assert_equal(false, args.generate_xml(), SPOT);
    assert_equal("", args.name_filter(), SPOT);
    assert_equal("", args.test_name(), SPOT);
    assert_equal("libunittest.xml", args.xml_filename(), SPOT);
}

void test_argparser::test_failure_stop()
{
    arguments_[1] = (char*)"-s";
    argparser args(2, arguments_);
    assert_equal(false, args.verbose(), SPOT);
    assert_equal(true, args.failure_stop(), SPOT);
    assert_equal(false, args.generate_xml(), SPOT);
    assert_equal("", args.name_filter(), SPOT);
    assert_equal("", args.test_name(), SPOT);
    assert_equal("libunittest.xml", args.xml_filename(), SPOT);
}

void test_argparser::test_generate_xml()
{
    arguments_[1] = (char*)"-x";
    argparser args(2, arguments_);
    assert_equal(false, args.verbose(), SPOT);
    assert_equal(false, args.failure_stop(), SPOT);
    assert_equal(true, args.generate_xml(), SPOT);
    assert_equal("", args.name_filter(), SPOT);
    assert_equal("", args.test_name(), SPOT);
    assert_equal("libunittest.xml", args.xml_filename(), SPOT);
}

void test_argparser::test_name_filter()
{
    arguments_[1] = (char*)"-f";
    arguments_[2] = (char*)"stuff";
    argparser args(3, arguments_);
    assert_equal(false, args.verbose(), SPOT);
    assert_equal(false, args.failure_stop(), SPOT);
    assert_equal(false, args.generate_xml(), SPOT);
    assert_equal("stuff", args.name_filter(), SPOT);
    assert_equal("", args.test_name(), SPOT);
    assert_equal("libunittest.xml", args.xml_filename(), SPOT);
}

void test_argparser::test_test_name()
{
    arguments_[1] = (char*)"-t";
    arguments_[2] = (char*)"test_me";
    argparser args(3, arguments_);
    assert_equal(false, args.verbose(), SPOT);
    assert_equal(false, args.failure_stop(), SPOT);
    assert_equal(false, args.generate_xml(), SPOT);
    assert_equal("", args.name_filter(), SPOT);
    assert_equal("test_me", args.test_name(), SPOT);
    assert_equal("libunittest.xml", args.xml_filename(), SPOT);
}

void test_argparser::test_xml_filename()
{
    arguments_[1] = (char*)"-o";
    arguments_[2] = (char*)"stuff.xml";
    argparser args(3, arguments_);
    assert_equal(false, args.verbose(), SPOT);
    assert_equal(false, args.failure_stop(), SPOT);
    assert_equal(false, args.generate_xml(), SPOT);
    assert_equal("", args.name_filter(), SPOT);
    assert_equal("", args.test_name(), SPOT);
    assert_equal("stuff.xml", args.xml_filename(), SPOT);
}

void test_argparser::test_verbose_failure_stop()
{
    const std::vector<char*> values = {(char*)"-vs", (char*)"-sv"};
    for (auto value : values) {
        arguments_[1] = value;
        argparser args(2, arguments_);
        assert_equal(true, args.verbose(), SPOT);
        assert_equal(true, args.failure_stop(), SPOT);
        assert_equal(false, args.generate_xml(), SPOT);
        assert_equal("", args.name_filter(), SPOT);
        assert_equal("", args.test_name(), SPOT);
        assert_equal("libunittest.xml", args.xml_filename(), SPOT);
    }
}

void test_argparser::test_verbose_generate_xml()
{
    const std::vector<char*> values = {(char*)"-vx", (char*)"-xv"};
    for (auto value : values) {
        arguments_[1] = value;
        argparser args(2, arguments_);
        assert_equal(true, args.verbose(), SPOT);
        assert_equal(false, args.failure_stop(), SPOT);
        assert_equal(true, args.generate_xml(), SPOT);
        assert_equal("", args.name_filter(), SPOT);
        assert_equal("", args.test_name(), SPOT);
        assert_equal("libunittest.xml", args.xml_filename(), SPOT);
    }
}

void test_argparser::test_failure_stop_generate_xml()
{
    const std::vector<char*> values = {(char*)"-sx", (char*)"-xs"};
    for (auto value : values) {
        arguments_[1] = value;
        argparser args(2, arguments_);
        assert_equal(false, args.verbose(), SPOT);
        assert_equal(true, args.failure_stop(), SPOT);
        assert_equal(true, args.generate_xml(), SPOT);
        assert_equal("", args.name_filter(), SPOT);
        assert_equal("", args.test_name(), SPOT);
        assert_equal("libunittest.xml", args.xml_filename(), SPOT);
    }
}

void test_argparser::test_verbose_failure_stop_generate_xml()
{
    const std::vector<char*> values = {
            (char*)"-vsx", (char*)"-vxs", (char*)"-svx",
            (char*)"-xvs", (char*)"-sxv", (char*)"-xsv"
    };
    for (auto value : values) {
        arguments_[1] = value;
        argparser args(2, arguments_);
        assert_equal(true, args.verbose(), SPOT);
        assert_equal(true, args.failure_stop(), SPOT);
        assert_equal(true, args.generate_xml(), SPOT);
        assert_equal("", args.name_filter(), SPOT);
        assert_equal("", args.test_name(), SPOT);
        assert_equal("libunittest.xml", args.xml_filename(), SPOT);
    }
}

void test_argparser::test_all_arguments()
{
    arguments_[1] = (char*)"-v";
    arguments_[2] = (char*)"-s";
    arguments_[3] = (char*)"-x";
    arguments_[4] = (char*)"-f";
    arguments_[5] = (char*)"stuff";
    arguments_[6] = (char*)"-t";
    arguments_[7] = (char*)"test_me";
    arguments_[8] = (char*)"-o";
    arguments_[9] = (char*)"stuff.xml";
    argparser args(10, arguments_);
    assert_equal(true, args.verbose(), SPOT);
    assert_equal(true, args.failure_stop(), SPOT);
    assert_equal(true, args.generate_xml(), SPOT);
    assert_equal("stuff", args.name_filter(), SPOT);
    assert_equal("test_me", args.test_name(), SPOT);
    assert_equal("stuff.xml", args.xml_filename(), SPOT);
}

void test_argparser::test_argparser_errors()
{
    struct wrapper {
        wrapper(int argc, char **argv)
            : argc_(argc), argv_(argv)
        {}
        void operator()() {
            argparser args(argc_, argv_);
        }
    private:
        int argc_;
        char **argv_;
    };

    const std::vector<char*> values = {
            (char*)"-g", (char*)"-f", (char*)"-t", (char*)"-o"
    };
    for (auto value : values) {
        arguments_[1] = value;
        wrapper functor(2, arguments_);
        assert_throw<unittest::argparser_error>(functor, SPOT);
    }
}
