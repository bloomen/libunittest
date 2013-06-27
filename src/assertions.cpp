#include <libunittest/assertions.hpp>

namespace unittest {

assertions::assertions()
{}

assertions::~assertions()
{}

void
assertions::fail(const std::string& message) const
{
    throw testfailure(message);
}

} // unittest
