#include <libunittest/testfailure.hpp>

namespace unittest {

testfailure::testfailure(const std::string& message)
    : std::runtime_error(message)
{}

} // unittest
