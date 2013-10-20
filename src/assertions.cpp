#include <libunittest/assertions.hpp>
#include <libunittest/testfailure.hpp>

namespace unittest {
namespace internals {

assertions::assertions()
    : formatting()
{}

assertions::~assertions()
{}

void
assertions::fail(const std::string& message) const
{
    throw testfailure(message);
}

template<> void assertions::assert_true(const bool& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const char& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const short& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const int& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const long& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const long long& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const unsigned char& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const unsigned short& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const unsigned int& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const unsigned long& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const unsigned long long& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const float& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const double& value, const std::string& message) const
{
    assert_true(value, message, "");
}
template<> void assertions::assert_true(const long double& value, const std::string& message) const
{
    assert_true(value, message, "");
}

template<> void assertions::assert_true(const bool& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const char& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const short& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const int& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const long& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const long long& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const unsigned char& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const unsigned short& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const unsigned int& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const unsigned long& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const unsigned long long& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const float& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const double& value) const
{
    assert_true(value, "");
}
template<> void assertions::assert_true(const long double& value) const
{
    assert_true(value, "");
}

template<> void assertions::assert_false(const bool& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const char& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const short& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const int& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const long& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const long long& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const unsigned char& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const unsigned short& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const unsigned int& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const unsigned long& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const unsigned long long& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const float& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const double& value, const std::string& message) const
{
    assert_false(value, message, "");
}
template<> void assertions::assert_false(const long double& value, const std::string& message) const
{
    assert_false(value, message, "");
}

template<> void assertions::assert_false(const bool& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const char& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const short& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const int& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const long& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const long long& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const unsigned char& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const unsigned short& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const unsigned int& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const unsigned long& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const unsigned long long& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const float& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const double& value) const
{
    assert_false(value, "");
}
template<> void assertions::assert_false(const long double& value) const
{
    assert_false(value, "");
}

template<> void assertions::assert_equal(const bool& expected, const bool& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const char& expected, const char& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const short& expected, const short& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const int& expected, const int& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const long& expected, const long& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const long long& expected, const long long& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const unsigned char& expected, const unsigned char& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const unsigned short& expected, const unsigned short& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const unsigned int& expected, const unsigned int& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const unsigned long& expected, const unsigned long& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const unsigned long long& expected,const unsigned long long& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const float& expected, const float& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const double& expected, const double& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const long double& expected, const long double& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}
template<> void assertions::assert_equal(const std::string& expected, const std::string& actual, const std::string& message) const
{
    assert_equal(expected, actual, message, "");
}

template<> void assertions::assert_equal(const bool& expected, const bool& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const char& expected, const char& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const short& expected, const short& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const int& expected, const int& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const long& expected, const long& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const long long& expected, const long long& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const unsigned char& expected, const unsigned char& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const unsigned short& expected, const unsigned short& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const unsigned int& expected, const unsigned int& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const unsigned long& expected, const unsigned long& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const unsigned long long& expected,const unsigned long long& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const float& expected, const float& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const double& expected, const double& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const long double& expected, const long double& actual) const
{
    assert_equal(expected, actual, "");
}
template<> void assertions::assert_equal(const std::string& expected, const std::string& actual) const
{
    assert_equal(expected, actual, "");
}

template<> void assertions::assert_not_equal(const bool& first, const bool& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const char& first, const char& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const short& first, const short& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const int& first, const int& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const long& first, const long& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const long long& first, const long long& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const unsigned char& first, const unsigned char& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const unsigned short& first, const unsigned short& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const unsigned int& first, const unsigned int& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const unsigned long& first, const unsigned long& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const unsigned long long& first,const unsigned long long& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const float& first, const float& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const double& first, const double& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const long double& first, const long double& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}
template<> void assertions::assert_not_equal(const std::string& first, const std::string& second, const std::string& message) const
{
    assert_not_equal(first, second, message, "");
}

template<> void assertions::assert_not_equal(const bool& first, const bool& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const char& first, const char& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const short& first, const short& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const int& first, const int& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const long& first, const long& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const long long& first, const long long& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const unsigned char& first, const unsigned char& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const unsigned short& first, const unsigned short& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const unsigned int& first, const unsigned int& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const unsigned long& first, const unsigned long& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const unsigned long long& first,const unsigned long long& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const float& first, const float& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const double& first, const double& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const long double& first, const long double& second) const
{
    assert_not_equal(first, second, "");
}
template<> void assertions::assert_not_equal(const std::string& first, const std::string& second) const
{
    assert_not_equal(first, second, "");
}

} // internals
} // unittest
