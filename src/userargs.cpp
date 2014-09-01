#include <libunittest/userargs.hpp>
#include <libunittest/utilities.hpp>
#include <libunittest/version.hpp>

namespace unittest {
namespace core {


userargs::userargs()
	: verbose(false), failure_stop(false), generate_xml(false),
	  handle_exceptions(true), dry_run(false), concurrent_threads(0),
	  name_filter(""), test_name(""), timeout(-1), xml_filename("libunittest.xml"),
	  disable_timeout(false), max_value_precision(10), max_string_length(500),
	  suite_name("libunittest")
{
	register_trigger('v', "verbose", "Sets verbose output for running tests", verbose);
	register_trigger('d', "dry_run", "A dry run without actually executing any tests", dry_run);
	register_trigger('s', "fail_stop", "Stops running tests after the first test fails", failure_stop);
	register_trigger('x', "gen_xml", "Enables the generation of the XML output", generate_xml);
	register_trigger('e', "handle_exc", "Turns off handling of unexpected exceptions", handle_exceptions);
	register_trigger('i', "no_timeouts", "Disables the measurement of any test timeouts", disable_timeout);
	register_argument('p', "number", "Runs tests in parallel with a given number of threads", concurrent_threads, false);
	register_argument('f', "filter", "A run filter applied to the beginning of the test names", name_filter, false);
	register_argument('n', "name", "A certain test to be run superseding the name filter", test_name, false);
	register_argument('t', "timeout", "A timeout in seconds for tests without local timeouts", timeout, false);
	register_argument('o', "xmlfile", "The XML output file name", xml_filename, true);
	register_argument('l', "length", "The maximum displayed string length", max_string_length, true);
	register_argument('r', "precision", "The maximum displayed value precision", max_value_precision, true);
	register_argument('u', "suite", "The name of the test suite", suite_name, true);
}

std::string
userargs::description()
{
	return "This is your testing application using libunittest-" + version;
}

void
userargs::assign_values()
{
	assign_value(verbose, 'v');
	assign_value(dry_run, 'd');
	assign_value(failure_stop, 's');
	assign_value(generate_xml, 'x');
	assign_value(handle_exceptions, 'e');
	assign_value(disable_timeout, 'i');
	assign_value(concurrent_threads, 'p');
	assign_value(name_filter, 'f');
	assign_value(test_name, 'n');
	assign_value(timeout, 't');
	assign_value(xml_filename, 'o');
	assign_value(max_string_length, 'l');
	assign_value(max_value_precision, 'r');
	assign_value(suite_name, 'u');
}

void
userargs::post_parse()
{
	if (was_used('o')) generate_xml = true;
	if (concurrent_threads<0) concurrent_threads = 0;
	if (max_string_length<10) max_string_length = 10;
	if (max_value_precision<3) max_value_precision = 3;
}

} // core
} // unittest
