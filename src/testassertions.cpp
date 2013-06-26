#include <libunittest/testassertions.hpp>

namespace unittest {

testassertions::testassertions()
{}

testassertions::~testassertions()
{}

void
testassertions::fail(const std::string& message) const
{
    throw testfailure(message);
}

} // unittest
