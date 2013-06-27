#include <libunittest/userargs.hpp>

namespace unittest {

userargs::userargs()
    : verbose_(false), failure_stop_(false), generate_xml_(false),
      name_filter_(""), test_name_(""), xml_filename_("libunittest.xml")
{}

userargs::~userargs()
{}

bool
userargs::verbose() const
{
    return verbose_;
}

void
userargs::verbose(bool value)
{
    verbose_ = value;
}

bool
userargs::failure_stop() const
{
    return failure_stop_;
}

void
userargs::failure_stop(bool value)
{
    failure_stop_ = value;
}

bool
userargs::generate_xml() const
{
    return generate_xml_;
}

void
userargs::generate_xml(bool value)
{
    generate_xml_ = value;
}

std::string
userargs::name_filter() const
{
    return name_filter_;
}

void
userargs::name_filter(const std::string& value)
{
    name_filter_ = value;
}

std::string
userargs::test_name() const
{
    return test_name_;
}

void
userargs::test_name(const std::string& value)
{
    test_name_ = value;
}

std::string
userargs::xml_filename() const
{
    return xml_filename_;
}

void
userargs::xml_filename(const std::string& value)
{
    xml_filename_ = value;
}

} // unittest
