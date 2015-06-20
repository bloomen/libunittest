#include "libunittest/testfailure.hpp"
#include "libunittest/utilities.hpp"


namespace unittest {

testfailure::testfailure(const std::string& assertion,
                         const std::string& message)
    : std::runtime_error(error_msg_),
      error_msg_(message),
      assertion_(assertion),
      spot_(std::make_pair("", -1))
{}

testfailure::testfailure(const std::string& assertion,
                         const std::string& message,
                         const std::string& user_msg)
    : std::runtime_error(make_error_msg(message, user_msg)),
      error_msg_(make_error_msg(message, user_msg)),
      assertion_(assertion),
      spot_(core::extract_file_and_line(user_msg))
{}

testfailure::testfailure(const testfailure& other)
    : std::runtime_error(other.error_msg_),
      error_msg_(other.error_msg_),
      assertion_(other.assertion_),
      spot_(other.spot_)
{}

testfailure&
testfailure::operator=(const testfailure& other)
{
    if (this!=&other) {
        error_msg_ = other.error_msg_;
        assertion_ = other.assertion_;
        spot_ = other.spot_;
    }
    return *this;
}

testfailure::~testfailure() UNITTEST_NOEXCEPT
{}

std::string testfailure::make_error_msg(const std::string& message,
                                        const std::string& user_msg)
{
    const auto msg = core::remove_tagged_text(user_msg, "SPOT");
    return msg.size() ? message + " - " + msg : message;
}

std::string
testfailure::assertion() const
{
    return assertion_;
}

std::string
testfailure::filename() const
{
    return spot_.first;
}

int
testfailure::linenumber() const
{
    return spot_.second;
}

} // unittest
