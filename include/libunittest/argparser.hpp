#pragma once
#include <libunittest/userargs.hpp>
#include <libunittest/pimplpattern.hpp>
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
class argparser : public userargs,
                  public pimplpattern<argparser> {
public:
    /**
     * @brief Constructor
     */
    argparser();
    /**
     * @brief Parses the arguments and assigns given values
     * @param argc The number of arguments
     * @param argv The array of arguments
     */
    void
    parse(int argc, char **argv);
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
    explicit
    argparser_error(const std::string& message);
};

} // unittest
