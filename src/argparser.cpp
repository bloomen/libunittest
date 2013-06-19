#include <libunittest/argparser.hpp>
#include <libunittest/utilities.hpp>
#include <libunittest/version.hpp>
#include <iostream>

namespace unittest {

template<>
struct implementation<argparser> {

	void
	write_help(std::ostream& stream) const
	{
	    stream << "This is your testing application using libunittest-";
	    stream << get_version_string() << "\n\n";
	    stream << "Available options are:\n";
	    stream << "-h          Displays this help message\n";
	    stream << "-v          Sets verbose output for running tests\n";
	    stream << "-s          Stops running tests after the first test fails\n";
	    stream << "-x          Enables the generation of the XML output\n";
	    stream << "-f filter   Specifies a filter applied to the beginning of the test names\n";
	    stream << "-t test     Specifies a certain test to run superseding the name filter\n";
	    stream << "-o xmlfile  Specifies the XML output file name (default: libunittest.xml)\n";
	    stream << std::flush;
	}

	void
	help_and_throw(const std::string& message) const
	{
	    std::ostringstream stream;
	    write_help(stream);
	    throw argparser_error(join(message, "\n\n", stream.str()));
	}

};

argparser::argparser(int argc, char **argv)
    : userargs(),
      pimplpattern(new implementation<argparser>())
{
    for (int i=1; i<argc; ++i) {
        const std::string value(argv[i]);
        if (value=="-h") {
            impl_->print_help(std::cout);
            std::exit(EXIT_SUCCESS);
        } else if (value=="-v") {
            verbose(true);
        } else if (value=="-s") {
            failure_stop(true);
        } else if (value=="-x") {
            generate_xml(true);
        } else if (value=="-sv" || value=="-vs") {
            verbose(true);
            failure_stop(true);
        } else if (value=="-vx" || value=="-xv") {
            verbose(true);
            generate_xml(true);
        } else if (value=="-sx" || value=="-xs") {
            failure_stop(true);
            generate_xml(true);
        } else if (value=="-vsx" || value=="-svx" || value=="-xvs" ||
                   value=="-xsv" || value=="-vxs" || value=="-sxv") {
            verbose(true);
            failure_stop(true);
            generate_xml(true);
        } else if (value=="-f") {
            if (++i<argc) {
                name_filter(argv[i]);
            } else {
            	impl_->help_and_throw("Option '-f' needs a filter string");
            }
        } else if (value=="-t") {
            if (++i<argc) {
                test_name(argv[i]);
            } else {
            	impl_->help_and_throw("Option '-t' needs a test name");
            }
        } else if (value=="-o") {
            if (++i<argc) {
                xml_filename(argv[i]);
            } else {
            	impl_->help_and_throw("Option '-o' needs an XML file name");
            }
        } else {
        	impl_->help_and_throw(join("Unknown argument '", value, "'"));
        }
    }
}

argparser::~argparser()
{}

argparser_error::argparser_error(const std::string& message)
    : std::runtime_error(message)
{}

} // unittest
