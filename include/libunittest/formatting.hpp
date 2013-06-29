#pragma once
#include <string>
#include <sstream>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief A formatting interface
 */
class formatting {
public:
    /**
     * @brief Constructor
     */
    formatting();
    /**
     * @brief Destructor
     */
    virtual
    ~formatting();
    /**
     * @brief A pure virtual method
     * @param assertion The name of the assertion
     * @param text The assertion text
     * @returns A displayed fail message
     */
    virtual std::string
    make_displayed_fail_message(const std::string& assertion,
                                const std::string& text) const = 0;
    /**
     * @brief A pure virtual method
     * @returns The maximum displayed string length
     */
    virtual int
    max_displayed_string_length() const = 0;
    /**
     * @brief A pure virtual method
     * @returns The maximum displayed value precision
     */
    virtual int
    max_displayed_value_precision() const = 0;
    /**
     * @brief Converts a given value to string by taking into account
     * 	the maximum string length and the maximum value precision
     * @param value The value
     */
    template<typename T>
    std::string
    str(const T& value) const
    {
        std::ostringstream stream;
        stream.precision(max_displayed_value_precision());
        stream << value;
        std::string result(stream.str());
        if (int(result.size())>max_displayed_string_length()) {
            result = result.substr(0, max_displayed_string_length());
        }
        return std::move("'" + result + "'");
    }

};

} // unittest
