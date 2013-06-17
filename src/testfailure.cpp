#include <libunittest/testfailure.hpp>

unittest::testfailure::testfailure(const std::string& message)
    : std::runtime_error(message)
{}
