#include <libunittest/formatting.hpp>
#include <libunittest/utilities.hpp>

namespace unittest {
namespace internals {

formatting::formatting()
{}

formatting::~formatting()
{}

std::string
formatting::__displayed_fail_message(const std::string& assertion,
                                     const std::string& text) const
{
    return text;
}

int
formatting::__max_displayed_string_length() const
{
    return 500;
}

int
formatting::__max_displayed_value_precision() const
{
    return 10;
}

std::string
formatting::__stream_to_string(const std::ostringstream& stream) const
{
    const int max_length = __max_displayed_string_length();
    const std::string result = limit_string_length(stream.str(), max_length);
    return "'" + result + "'";
}

} // internals
} // unittest
