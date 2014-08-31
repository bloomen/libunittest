#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>
using namespace unittest::assertions;
using unittest::core::argparser;


struct client_empty : argparser {};


struct test_argparser : unittest::testcase<> {

	test_argparser(const test_argparser&) = delete;
	test_argparser& operator=(const test_argparser&) = delete;

	static void run()
	{
		UNITTEST_CLASS(test_argparser)
		UNITTEST_RUN(test_empty_client)
		UNITTEST_RUN(test_empty_client_with_help)
	}

	char** argv_;

	test_argparser()
		: argv_(new char*[100])
	{
		argv_[0] = (char*)"program";
	}

	~test_argparser()
	{
		delete[] argv_;
	}

	void test_empty_client()
	{
		client_empty client;
		client.parse(1, argv_);
		assert_equal(std::string(argv_[0]), client.command_line(), SPOT);
	}

	void test_empty_client_with_help()
	{
		client_empty client;
		argv_[1] = (char*)"-h";
		std::string msg;
		try {
			client.parse(2, argv_);
		} catch (const argparser::exit_success& e) {
			msg = e.what();
		}
		assert_equal(std::string(argv_[0]) + " -h", client.command_line(), SPOT);
		std::string exp;
		exp += "Usage: program [Arguments]\n\n";
		exp += "Arguments:\n";
		exp += "-h   Displays this help message and exits\n";
		assert_equal(exp, msg, SPOT);
	}

};
REGISTER(test_argparser)
