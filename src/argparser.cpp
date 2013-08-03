#include <libunittest/argparser.hpp>
#include <libunittest/utilities.hpp>
#include <libunittest/version.hpp>
#include <iostream>
#include <sstream>

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
        stream << "-e          Turns off exception handling\n";
        stream << "-x          Enables the generation of the XML output\n";
        stream << "-f filter   A filter applied to the beginning of the test names\n";
        stream << "-n test     A certain test to be run superseding the name filter\n";
        stream << "-t timeout  A time out for the tests without static time outs\n";
        stream << "-o xmlfile  The XML output file name (default: libunittest.xml)\n";
        stream << std::flush;
    }

    void
    help_and_throw(const std::string& message) const
    {
        std::ostringstream stream;
        write_help(stream);
        throw argparser_error(join(message, "\n\n", stream.str()));
    }

    std::vector<std::string>
    expand_arguments(int argc, char **argv) const
    {
        std::vector<std::string> args;
        for (int i=1; i<argc; ++i) {
            const std::string value(argv[i]);
            if (value.substr(0, 1)=="-") {
                const std::string expanded(value.substr(1, value.size()));
                for (auto& val : expanded) {
                    args.push_back(join("-", val));
                }
            } else {
                args.push_back(value);
            }
        }
        return args;
    }

};

argparser::argparser()
    : userargs(),
      pimplpattern(new implementation<argparser>())
{}

void argparser::parse(int argc, char **argv)
{
    const auto args = impl_->expand_arguments(argc, argv);
    const auto length = args.size();
    for (unsigned i=0; i<length; ++i) {
        if (args[i]=="-h") {
            impl_->write_help(std::cout);
            std::exit(EXIT_SUCCESS);
        } else if (args[i]=="-v") {
            verbose(true);
        } else if (args[i]=="-s") {
            failure_stop(true);
        } else if (args[i]=="-x") {
            generate_xml(true);
        } else if (args[i]=="-e") {
            handle_exceptions(false);
        } else if (args[i]=="-f") {
            if (++i<length) {
                name_filter(args[i]);
            } else {
            	impl_->help_and_throw("Option '-f' needs a filter string");
            }
        } else if (args[i]=="-n") {
            if (++i<length) {
                test_name(args[i]);
            } else {
                impl_->help_and_throw("Option '-n' needs a test name");
            }
        } else if (args[i]=="-t") {
            if (++i<length) {
                time_out(atof(args[i].c_str()));
            } else {
                impl_->help_and_throw("Option '-t' needs a time out");
            }
        } else if (args[i]=="-o") {
            if (++i<length) {
                xml_filename(args[i]);
            } else {
            	impl_->help_and_throw("Option '-o' needs an XML file name");
            }
        } else {
        	impl_->help_and_throw(join("Unknown argument '", args[i], "'"));
        }
    }
}

argparser_error::argparser_error(const std::string& message)
    : std::runtime_error(message)
{}

} // unittest
