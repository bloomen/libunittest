#pragma once
#include <libunittest/argparser.hpp>
#include <libunittest/testsuite.hpp>
#include <libunittest/testresults.hpp>
#include <iostream>
#include <fstream>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief This function is to be implemented by the user if any of the
 *  predefined environment functions are called. run_all_tests() should
 *  contain a list of calls to test classes
 */
void
run_all_tests();
/**
 * @brief Sets up a default testing environment and calls run_all_tests().
 *  This high-level function is intended to be used directly from the
 *  user's main() function
 * @param argc The number of user arguments
 * @param argv The array of user arguments
 * @returns A platform dependent program execution status: A success value if
 *  all tests succeed and an error value otherwise
 */
inline int
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
