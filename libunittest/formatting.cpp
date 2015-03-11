#include "formatting.hpp"
#include "utilities.hpp"

namespace unittest {
namespace core {

template<>
std::string
str<bool&>(bool& value)
{
	return value ? "true" : "false";
}

template<>
std::string
str<bool>(bool&& value)
{
	return value ? "true" : "false";
}

} // core
} // unittest
