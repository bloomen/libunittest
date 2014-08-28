/**
 * @brief An argument parser and corresponding exception class
 * @file argparser.hpp
 */
#pragma once
#include <libunittest/userargs.hpp>
#include <string>
#include <stdexcept>
#include <memory>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace internals {
/**
 * @brief An argument parser
 */
class argparser : public unittest::internals::userargs {
public:
    /**
     * @brief Constructor
     */
    argparser();
    /**
     * @brief Destructor
     */
    virtual
    ~argparser();
    /**
     * @brief Copy constructor. Deleted
     * @param other An instance of argparser
     */
    argparser(const argparser& other) = delete;
    /**
     * @brief Copy assignment operator. Deleted
     * @param other An instance of argparser
     * @returns An argparser instance
     */
    argparser&
    operator=(const argparser& other) = delete;
    /**
     * @brief Move constructor. Deleted
     * @param other An instance of argparser
     */
    argparser(argparser&& other) = delete;
    /**
     * @brief Move assignment operator. Deleted
     * @param other An instance of argparser
     * @returns An argparser instance
     */
    argparser&
    operator=(argparser&& other) = delete;
    /**
     * @brief Parses the arguments and assigns given values
     * @param argc The number of arguments
     * @param argv The array of arguments
     */
    void
    parse(int argc, char **argv);

private:
    struct impl;
    std::unique_ptr<impl> impl_;
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
    /**
     * @brief Destructor
     */
    ~argparser_error() noexcept;
};

} // internals
} // unittest
