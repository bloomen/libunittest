/**
 * @brief The userargs class to control application behavior
 * @file userargs.hpp
 */
#pragma once
#include <string>
#include <libunittest/argparser.hpp>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace core {
/**
 * @brief High level user arguments to control application behavior
 */
struct userargs : argparser {
    /**
     * @brief Constructor
     */
    userargs();
    /**
     * @brief Whether the output is verbose (default: false)
     */
    bool verbose;
    /**
     * @brief Whether to stop running after first failure (default: false)
     */
    bool failure_stop;
    /**
     * @brief Whether to generate XML output (default: false)
     */
    bool generate_xml;
    /**
     * @brief Whether to handle unknown exceptions (default: true)
     */
    bool handle_exceptions;
    /**
     * @brief Whether to perform a dry run (default: false)
     */
    bool dry_run;
    /**
     * @brief The number of concurrent threads (default: 0)
     */
    int concurrent_threads;
    /**
     * @brief Sets a name filter on the full test name (default: "")
     */
    std::string name_filter;
    /**
     * @brief Sets a certain test to be run. This supersedes the name filter (default: "")
     */
    std::string test_name;
    /**
     * @brief The global test timeout (default: -1)
     */
    double timeout;
    /**
     * @brief The XML output file name (default: "libunittest.xml")
     */
    std::string xml_filename;
    /**
     * @brief Whether to disable timeout measurement (default: false)
     */
    bool disable_timeout;
    /**
     * @brief The maximum displayed value precision (default: 10)
     */
    int max_value_precision;
    /**
     * @brief The maximum displayed string length (default: 500)
     */
    int max_string_length;
    /**
     * @brief The name of the test suite (default: "libunittest")
     */
    std::string suite_name;

private:

	std::string description();

    void assign_values();

    void post_parse();

};

} // core
} // unittest
