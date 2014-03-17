#include <libunittest/testfailure.hpp>
#include <libunittest/utilities.hpp>


namespace unittest {

testfailure::testfailure(const std::string& assertion,
                         const std::string& message)
    : std::runtime_error(internals::remove_file_and_line(message)),
      assertion_(assertion),
      filename_(""),
      linenumber_(-1)
{
    const auto spot = internals::extract_file_and_line(message);
    filename_ = spot.first;
    linenumber_ = spot.second;
}

testfailure::~testfailure() noexcept
{}

std::string
testfailure::assertion() const
{
    return assertion_;
}

std::string
testfailure::filename() const
{
    return filename_;
}

int
testfailure::linenumber() const
{
    return linenumber_;
}

} // unittest
