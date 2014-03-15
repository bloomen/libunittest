#include <libunittest/testfailure.hpp>

namespace unittest {

testfailure::testfailure(const std::string& assertion,
                         const std::string& message)
    : std::runtime_error(message),
      assertion_(assertion)
{}

testfailure::~testfailure() noexcept
{}

std::string
testfailure::assertion() const
{
    return assertion_;
}

} // unittest
