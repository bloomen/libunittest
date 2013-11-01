#include <libunittest/testresults.hpp>
#include <libunittest/teststatus.hpp>
#include <libunittest/utilities.hpp>

namespace unittest {
namespace internals {

testresults::testresults()
    : successful(true), n_tests(0), n_successes(0), n_failures(0),
      n_errors(0), n_skipped(0), n_timeouts(0), duration(0), testlogs(0)
{}

void
write_xml(std::ostream& stream,
          const testresults& results,
          const std::chrono::system_clock::time_point& time_point)
{
    stream.setf(std::ios_base::fixed);
    stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    stream << "\n";
    stream << "<testsuite name=\"libunittest";
    stream << "\" timestamp=\"" << make_iso_timestamp(time_point);
    stream << "\" tests=\"" << results.n_tests;
    stream << "\" errors=\"" << results.n_errors;
    stream << "\" failures=\"" << results.n_failures;
    stream << "\" timeouts=\"" << results.n_timeouts;
    stream << "\" skipped=\"" << results.n_skipped;
    stream << "\" time=\"" << results.duration << "\">";
    stream << "\n";
    for (auto& log : results.testlogs) {
        stream << "\t<testcase classname=\"" << xml_escape(log.class_name);
        stream << "\" name=\"" << xml_escape(log.test_name);
        stream << "\" time=\"" << log.duration;
        const std::string has_timed_out = log.has_timed_out ? "true" : "false";
        stream << "\" timed_out=\"" << has_timed_out;
        stream << "\" timeout=\"" << log.timeout << "\"";
        if (log.successful) {
            stream << "/>";
            stream << "\n";
        } else {
            stream << ">";
            stream << "\n";
            if (log.status==teststatus::failure)
                stream << "\t\t<failure ";
            else
                stream << "\t\t<error ";
            stream << "type=\"" << xml_escape(log.error_type);
            stream << "\" message=\"" << xml_escape(log.message) << "\"/>";
            stream << "\n";
            stream << "\t</testcase>";
            stream << "\n";
        }
    }
    stream << "</testsuite>";
    stream << "\n";
    stream << std::flush;
    stream.unsetf(std::ios_base::fixed);
}

void
write_summary(std::ostream& stream,
              const testresults& results)
{
    stream << "\n";
    write_horizontal_bar(stream, '-');
    stream << "\n";
    stream << "Ran " << results.n_tests << " tests in ";
    stream << results.duration << "s\n\n";
    if (results.n_tests==results.n_successes) {
        stream << "OK";
        if (results.n_timeouts>0)
            stream << " (timeouts=" << results.n_timeouts <<")";
        stream << "\n";
    } else {
        stream << "FAILED (";
        if (results.n_failures>0 && results.n_errors>0) {
            stream << "failures=" << results.n_failures;
            stream << ", errors=" << results.n_errors;
        } else if (results.n_failures>0) {
            stream << "failures=" << results.n_failures;
        } else if (results.n_errors>0) {
            stream << "errors=" << results.n_errors;
        }
        if (results.n_timeouts>0)
            stream << ",timeouts=" << results.n_timeouts;
        stream << ")\n";
    }
    stream << std::flush;
}

void
write_error_info(std::ostream& stream,
                 const std::vector<testlog>& testlogs,
                 bool successful)
{
    if (!successful) {
        stream << "\n";
        for (auto& log : testlogs) {
            const auto status = log.status;
            if (status==teststatus::failure || status==teststatus::error) {
                write_horizontal_bar(stream, '=');
                stream << "\n";
                std::string flag("FAIL");
                if (status==teststatus::error)
                    flag = "ERROR";
                stream << flag << ": " << make_full_test_name(log.class_name, log.test_name);
                if (log.has_timed_out)
                    stream << " (TIMEOUT)";
                stream << "\n";
                write_horizontal_bar(stream, '-');
                stream << "\n";
                stream << log.error_type << ": " << log.message;
                stream << "\n\n";
            }
        }
        stream << std::flush;
    }
}

} // internals
} // unittest
