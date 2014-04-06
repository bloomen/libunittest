/**
 * @brief The userargs class to control application behavior
 * @file userargs.hpp
 */
#pragma once
#include <string>
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
 * @brief High level user arguments to control application behavior
 */
class userargs {
public:
    /**
     * @brief Constructor
     */
    userargs();
    /**
     * @brief Destructor
     */
    virtual
    ~userargs();
    /**
     * @brief Copy constructor
     * @param other Another instance of userargs
     */
    userargs(const userargs& other);
    /**
     * @brief Copy assignment operator
     * @param other Another instance of userargs
     * @returns An instance of userargs
     */
    userargs& operator=(const userargs& other);
    /**
     * @brief Returns whether the output is verbose
     * @returns Whether the output is verbose
     */
    virtual bool
    verbose() const;
    /**
     * @brief Sets whether the output is verbose (default: false)
     * @param value The value
     */
    virtual void
    verbose(bool value);
    /**
     * @brief Returns whether to stop running after the first test fails
     * @returns Whether to stop running after first failure
     */
    virtual bool
    failure_stop() const;
    /**
     * @brief Sets whether to stop running after first failure (default: false)
     * @param value The value
     */
    virtual void
    failure_stop(bool value);
    /**
     * @brief Returns whether to generate XML output
     * @returns Whether to generate XML output
     */
    virtual bool
    generate_xml() const;
    /**
     * @brief Sets whether to generate XML output (default: false)
     * @param value The value
     */
    virtual void
    generate_xml(bool value);
    /**
     * @brief Returns whether to handle unknown exceptions
     * @returns Whether to handle unknown exceptions
     */
    virtual bool
    handle_exceptions() const;
    /**
     * @brief Sets whether to handle unknown exceptions (default: true)
     * @param value The value
     */
    virtual void
    handle_exceptions(bool value);
    /**
     * @brief Returns a name filter on the full test name
     * @returns The filter string
     */
    virtual std::string
    name_filter() const;
    /**
     * @brief Sets a name filter on the full test name (default: "")
     * @param value The value
     */
    virtual void
    name_filter(const std::string& value);
    /**
     * @brief Returns a certain test to be run. This supersedes the name filter
     * @returns The test name
     */
    virtual std::string
    test_name() const;
    /**
     * @brief Sets a certain test to be run. This supersedes the name filter (default: "")
     * @param value The value
     */
    virtual void
    test_name(const std::string& value);
    /**
     * @brief Sets the timeout for those tests without static timeouts
     * @param value The value
     */
    virtual void
    timeout(double value);
    /**
     * @brief Returns the test timeout
     * @returns The test timeout
     */
    virtual double
    timeout() const;
    /**
     * @brief Returns the XML output file name
     * @returns The XML output file name
     */
    virtual std::string
    xml_filename() const;
    /**
     * @brief Sets the XML output file name (default: "libunittest.xml")
     * @param value The value
     */
    virtual void
    xml_filename(const std::string& value);
    /**
     * @brief Returns whether to perform a dry run
     * @returns Whether to perform a dry run
     */
    virtual bool
    dry_run() const;
    /**
     * @brief Sets whether to perform a dry run (default: false)
     * @param value The value
     */
    virtual void
    dry_run(bool value);
    /**
     * @brief Returns the number of concurrent threads
     * @returns The number of concurrent threads
     */
    virtual int
    concurrent_threads() const;
    /**
     * @brief Sets the number of concurrent threads (default: 0)
     * @param value The value
     */
    virtual void
    concurrent_threads(int value);
    /**
     * @brief Returns whether to disable timeout measurement
     * @returns Whether to disable timeout measurement
     */
    virtual bool
    disable_timeout() const;
    /**
     * @brief Sets whether to disable timeout measurement (default: false)
     * @param value The value
     */
    virtual void
    disable_timeout(bool value);

private:

    userargs(userargs&& other) = delete;

    userargs& operator=(userargs&& other) = delete;

    struct impl;
    std::unique_ptr<impl> impl_;
};

} // internals
} // unittest
