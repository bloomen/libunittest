#pragma once
#include <string>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
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
     * @brief Returns whether to handle exceptions
     * @returns Whether to handle exceptions
     */
    virtual bool
    handle_exceptions() const;
    /**
     * @brief Sets whether to handle exceptions (default: true)
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

protected:

    bool verbose_;
    bool failure_stop_;
    bool generate_xml_;
    bool handle_exceptions_;
    std::string name_filter_;
    std::string test_name_;
    std::string xml_filename_;

};

} // unittest
