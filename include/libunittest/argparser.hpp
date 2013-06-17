#pragma once
#include <libunittest/userargs.hpp>
#include <ostream>
#include <string>
#include <stdexcept>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief An argument parser
 */
class argparser : public userargs {
public:
    /**
     * @brief Constructor
     * @param argc The number of arguments
     * @param argv The array of arguments
     */
    argparser(int argc, char **argv);

private:

    void
    print_help(std::ostream& stream) const;

    void
    help_exit_failure(const std::string& message) const;
};
/**
 * @brief The exception class to indicate argument errors
 */
class argparser_error : public std::runtime_error {
public:
    /**
     * @brief Constructor
     * @param message The exception message
     */
    explicit argparser_error(const std::string& message);
};

} // unittest
