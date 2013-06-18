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
    int exit_code;
    try {
        argparser args(argc, argv);
        auto suite = testsuite::instance();
        suite->set_verbose(args.verbose());
        suite->set_failure_stop(args.failure_stop());
        suite->set_name_filter(args.name_filter());
        suite->set_test_name(args.test_name());
        run_all_tests();
        const auto results = suite->get_results();
        write_error_info(std::cout, results);
        write_summary(std::cout, results);
        if (args.generate_xml()) {
            std::ofstream file(args.xml_filename());
            write_xml(file, results);
        }
        if (results.successful)
            exit_code = EXIT_SUCCESS;
        else
            exit_code = EXIT_FAILURE;
    } catch (const argparser_error& e) {
        std::cout << "ArgumentError: " << e.what();
        std::exit(EXIT_FAILURE);
    }
    return exit_code;
}

} // unittest
