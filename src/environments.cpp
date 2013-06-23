#include <libunittest/argparser.hpp>
#include <libunittest/environments.hpp>
#include <libunittest/testsuite.hpp>
#include <libunittest/testresults.hpp>
#include <iostream>
#include <fstream>

namespace unittest {

int
make_default_environment(int argc, char **argv)
{
	argparser arguments;
	try {
		arguments.parse(argc, argv);
    } catch (const argparser_error& e) {
        std::cout << "ArgumentError: " << e.what();
        std::exit(EXIT_FAILURE);
    }

    auto suite = testsuite::instance();
	suite->set_verbose(arguments.verbose());
	suite->set_failure_stop(arguments.failure_stop());
	suite->set_name_filter(arguments.name_filter());
	suite->set_test_name(arguments.test_name());

	run_all_tests();

	const auto results = suite->get_results();
	write_error_info(std::cout, results);
	write_summary(std::cout, results);
	if (arguments.generate_xml()) {
		std::ofstream file(arguments.xml_filename());
		write_xml(file, results);
	}

	return results.successful ? EXIT_SUCCESS : EXIT_FAILURE;
}

} // unittest
