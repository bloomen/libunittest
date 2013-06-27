#include <libunittest/assertions.hpp>
#include <libunittest/testfailure.hpp>

namespace unittest {

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

} // unittest
