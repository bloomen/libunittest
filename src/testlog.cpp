#include <libunittest/testlog.hpp>
#include <libunittest/teststatus.hpp>

unittest::testlog::testlog()
    : class_name(""), test_name(""), successful(true),
      status(teststatus::skipped), message(""), duration(0)
{}

void
unittest::write_test_start_message(std::ostream& stream,
                                   const testlog& log,
                                   bool verbose)
{
    if (verbose) {
        stream << log.class_name << "." << log.test_name << " ... ";
        stream << std::flush;
    }
}

void
unittest::write_test_end_message(std::ostream& stream,
                                 const testlog& log,
                                 bool verbose)
{
    if (verbose) {
        switch (log.status) {
        case teststatus::success: stream << "ok"; break;
        case teststatus::failure: stream << "FAIL"; break;
        case teststatus::error: stream << "ERROR"; break;
        case teststatus::skipped: break;
        }
        stream << "\n";
    } else {
        switch (log.status) {
        case teststatus::success: stream << "."; break;
        case teststatus::failure: stream << "F"; break;
        case teststatus::error: stream << "E"; break;
        case teststatus::skipped: break;
        }
    }
    stream << std::flush;
}
