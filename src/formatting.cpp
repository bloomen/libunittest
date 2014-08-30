#include <libunittest/formatting.hpp>
#include <libunittest/utilities.hpp>

namespace unittest {
namespace core {

std::string
stream_to_string(const std::ostringstream& stream)
{
	const std::string result = stream.str();
	if (is_numeric(result))
		return result;
	else
		return "'" + limit_string_length(result, unittest::core::testsuite::instance()->get_arguments().max_string_length) + "'";
}

template<>
std::string
str<bool>(const bool& value)
{
	return value ? "true" : "false";
}

} // core
} // unittest
