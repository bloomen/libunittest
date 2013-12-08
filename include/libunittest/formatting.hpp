/**
 * @brief The formatting class defining a formatting interface
 * @file formatting.hpp
 */
#pragma once
#include <string>
#include <sstream>
/**
 * @brief Unit testing in C++
 */
namespace unittest {
/**
 * @brief Internal functionality, not relevant for most users
 */
namespace internals {
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
     * @brief Generates a displayed fail message from assertion name and text
     * @param assertion The name of the assertion
     * @param text The assertion text
     * @returns A displayed fail message
     */
    virtual std::string
    make_displayed_fail_message(const std::string& assertion,
                                const std::string& text) const;
    /**
     * @brief Returns the maximum displayed string length
     *  (default: 500)
     * @returns The maximum displayed string length
     */
    virtual int
    max_displayed_string_length() const;
    /**
     * @brief Returns the maximum displayed precision of numerical values
     *  (default: 10)
     * @returns The maximum displayed value precision
     */
    virtual int
    max_displayed_value_precision() const;
    /**
     * @brief Converts a given value to string by taking into account
     * 	the maximum string length and the maximum value precision
     * @param value The value
     * @returns A string
     */
    template<typename T>
    std::string
    str(const T& value) const
    {
        std::ostringstream stream;
        stream.precision(max_displayed_value_precision());
        stream << value;
        return std::move(stream_to_string(stream));
    }

private:
    std::string
    stream_to_string(const std::ostringstream& stream) const;
};

} // internals
} // unittest
