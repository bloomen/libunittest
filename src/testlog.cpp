#include <libunittest/testlog.hpp>
#include <libunittest/teststatus.hpp>

namespace unittest {
namespace internals {

testlog::testlog()
    : class_name(""), test_name(""), successful(true),
      status(teststatus::skipped), message(""), duration(0)
{}

void
write_test_start_message(std::ostream& stream,
                         const testlog& log,
                         bool verbose)
{
    if (verbose) {
        stream << make_full_test_name(log.class_name, log.test_name) << " ... ";
        stream << std::flush;
    }
}

void
write_test_end_message(std::ostream& stream,
                       const testlog& log,
                       bool verbose)
{
    if (verbose) {
        switch (log.status) {
        case teststatus::success: stream << "ok";   break;
        case teststatus::failure: stream << "FAIL"; break;
        case teststatus::error: stream << "ERROR";  break;
        default: break;
        }
        stream << "\n";
    } else {
        switch (log.status) {
        case teststatus::success: stream << "."; break;
        case teststatus::failure: stream << "F"; break;
        case teststatus::error: stream << "E";   break;
        default: break;
        }
    }
    stream << std::flush;
}

std::string
make_full_test_name(const std::string& class_name,
                    const std::string& test_name)
{
    return class_name + "." + test_name;
}

bool
is_test_executed(const std::string& full_test_name,
                 const std::string& exact_name,
                 const std::string& filter_name)
{
    if (exact_name!="") {
        if (exact_name==full_test_name)
            return true;
        else
            return false;
    }

    if (filter_name!="") {
        if (full_test_name.substr(0, filter_name.size())==filter_name)
            return true;
        else
            return false;
    }

    return true;
}

} // internals
} // unittest
