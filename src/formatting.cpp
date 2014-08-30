#include <libunittest/formatting.hpp>
#include <libunittest/utilities.hpp>

namespace unittest {
namespace core {

std::string
stream_to_string(const std::ostringstream& stream)
{
    return "'" + limit_string_length(stream.str(), unittest::core::testsuite::instance()->get_arguments().max_string_length()) + "'";
}

} // internals
} // unittest
