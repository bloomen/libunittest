#include <libunittest/unittest.hpp>

int main(int argc, char **argv)
{
    auto status = unittest::process(argc, argv);
    if (status==EXIT_FAILURE) {
        return status;
    } else {
        auto results = unittest::internals::testsuite::instance()->get_results();
        auto exp_tests = 141;
        if (exp_tests!=results.n_tests) {
            std::cerr << "Expected " << exp_tests << " tests, but got " << results.n_tests << std::endl;
            status = EXIT_FAILURE;
        }
        auto exp_skips = 16;
        if (exp_skips!=results.n_skipped) {
            std::cerr << "Expected " << exp_skips << " skips, but got " << results.n_skipped << std::endl;
            status = EXIT_FAILURE;
        }
        auto exp_timeouts = 8;
        if (exp_timeouts!=results.n_timeouts) {
            std::cerr << "Expected " << exp_timeouts << " timeouts, but got " << results.n_timeouts << std::endl;
            status = EXIT_FAILURE;
        }
        return status;
    }
}
