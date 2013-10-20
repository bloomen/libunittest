#include <libunittest/assertions.hpp>
#include <libunittest/testfailure.hpp>

namespace unittest {
namespace internals {

assertions::assertions()
{}

assertions::~assertions()
{}

void
assertions::fail(const std::string& message) const
{
    throw testfailure(message);
}

} // internals
} // unittest
