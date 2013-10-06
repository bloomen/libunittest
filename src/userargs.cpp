#include <libunittest/userargs.hpp>

namespace unittest {

userargs::userargs()
    : verbose_(false), failure_stop_(false), generate_xml_(false),
      handle_exceptions_(true), dry_run_(false), concurrent_threads_(0),
      name_filter_(""), test_name_(""), timeout_(-1),
      xml_filename_("libunittest.xml")
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

bool
userargs::handle_exceptions() const
{
    return handle_exceptions_;
}

void
userargs::handle_exceptions(bool value)
{
    handle_exceptions_ = value;
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

double
userargs::timeout() const
{
    return timeout_;
}

void
userargs::timeout(double value)
{
    timeout_ = value;
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

bool
userargs::dry_run() const
{
    return dry_run_;
}

void
userargs::dry_run(bool value)
{
    dry_run_ = value;
}

int
userargs::concurrent_threads() const
{
    return concurrent_threads_;
}

void
userargs::concurrent_threads(int value)
{
    concurrent_threads_ = value;
}

} // unittest
