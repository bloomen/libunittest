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
class argparser : public userargs, public pimplpattern<argparser> {
public:
    /**
     * @brief Constructor
     * @param argc The number of arguments
     * @param argv The array of arguments
     */
    argparser(int argc, char **argv);
    /**
     * @brief Destructor
     */
    virtual ~argparser();

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
