#include <libunittest/userargs.hpp>

unittest::userargs::userargs()
    : verbose_(false), failure_stop_(false), generate_xml_(false),
      name_filter_(""), test_name_(""), xml_filename_("libunittest.xml")
{}

unittest::userargs::~userargs()
{}

bool
unittest::userargs::verbose() const
{
    return verbose_;
}

void
unittest::userargs::verbose(bool value)
{
    verbose_ = value;
}

bool
unittest::userargs::failure_stop() const
{
    return failure_stop_;
}

void
unittest::userargs::failure_stop(bool value)
{
    failure_stop_ = value;
}

bool
unittest::userargs::generate_xml() const
{
    return generate_xml_;
}

void
unittest::userargs::generate_xml(bool value)
{
    generate_xml_ = value;
}

std::string
unittest::userargs::name_filter() const
{
    return name_filter_;
}

void
unittest::userargs::name_filter(const std::string& value)
{
    name_filter_ = value;
}

std::string
unittest::userargs::test_name() const
{
    return test_name_;
}

void
unittest::userargs::test_name(const std::string& value)
{
    test_name_ = value;
}

std::string
unittest::userargs::xml_filename() const
{
    return xml_filename_;
}

void
unittest::userargs::xml_filename(const std::string& value)
{
    xml_filename_ = value;
}
