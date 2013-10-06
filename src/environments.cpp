#include <libunittest/environments.hpp>
#include <libunittest/argparser.hpp>
#include <libunittest/testsuite.hpp>
#include <libunittest/testresults.hpp>
#include <libunittest/utilities.hpp>
#include <iostream>
#include <fstream>

namespace unittest {

int
process(int argc, char **argv)
{
    internals::argparser arguments;
    try {
        arguments.parse(argc, argv);
    } catch (const internals::argparser_error& e) {
        std::cout << "ArgumentError: " << e.what();
        std::exit(EXIT_FAILURE);
    }

    auto suite = internals::testsuite::instance();
    suite->set_arguments(arguments);

    const auto test_runs = suite->get_test_runs();
    const int n_threads = arguments.concurrent_threads();
    internals::call_functions(test_runs, n_threads);

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
