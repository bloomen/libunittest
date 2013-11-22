#include <libunittest/unittest.hpp>
#include <libunittest/shortcuts.hpp>

struct test_utilities : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_utilities)
        UNITTEST_RUN(test_limit_string_length)
        UNITTEST_RUN(test_string_of_file_and_line)
        UNITTEST_RUN(test_join)
        UNITTEST_RUN(test_write_to_stream)
        UNITTEST_RUN(test_write_to_stream_overload)
        UNITTEST_RUN(test_write_horizontal_bar)
        UNITTEST_RUN(test_duration_in_seconds)
        UNITTEST_RUN(test_xml_escape)
        UNITTEST_RUN(test_make_iso_timestamp)
        UNITTEST_RUN(test_call_functions_empty_vector)
        UNITTEST_RUN(test_call_functions_vector_size_one)
        UNITTEST_RUN(test_call_functions_vector_size_two)
        UNITTEST_RUN(test_make_futures_happy_empty)
        UNITTEST_RUN(test_make_futures_happy_filled)
        UNITTEST_RUN(test_get_from_map)
        UNITTEST_RUN(test_get_from_map_key_not_found)
        UNITTEST_RUN(test_get_type_id)
    }

    void test_limit_string_length()
    {
        auto function = unittest::internals::limit_string_length;
        assert_equal("albert", function("albert", 8), SPOT);
        assert_equal("albert", function("albert", 6), SPOT);
        assert_equal("alber", function("albert", 5), SPOT);
        assert_equal("a", function("albert", 1), SPOT);
        assert_equal("", function("albert", 0), SPOT);
        assert_equal("albert", function("albert", -1), SPOT);
        assert_equal("albert", function("albert", -3), SPOT);
    }

    void test_string_of_file_and_line()
    {
        auto function = unittest::internals::string_of_file_and_line;
        assert_equal(" @albert:13. ", function("albert", 13), SPOT);
        assert_equal(" @blöd:-42. ", function("blöd", -42), SPOT);
    }

    void test_join()
    {
        const std::string value_string("pi");
        assert_equal(value_string, unittest::join(value_string), SPOT);
        const double value_double(3.1415);
        assert_equal("3.1415", unittest::join(value_double), SPOT);
        assert_equal("pi = 3.1415", unittest::join(value_string, " = ", value_double), SPOT);
    }

    void test_write_to_stream()
    {
        std::ostringstream stream;
        const std::string value_string("pi");
        const double value_double(3.1415);
        unittest::internals::write_to_stream(stream, value_string, " = ", value_double);
        assert_equal("pi = 3.1415", stream.str(), SPOT);
    }

    void test_write_to_stream_overload()
    {
        std::ostringstream stream;
        unittest::internals::write_to_stream(stream);
        assert_equal("", stream.str(), SPOT);
    }

    void test_write_horizontal_bar()
    {
        auto function = unittest::internals::write_horizontal_bar;
        std::ostringstream stream;
        function(stream, 'x', 3);
        assert_equal("xxx", stream.str(), SPOT);
        assert_throw<std::length_error>(std::bind(function, std::ref(stream), 'x', -1), SPOT);
    }

    void test_duration_in_seconds()
    {
        const std::chrono::duration<double> duration(1);
        assert_equal(1, unittest::internals::duration_in_seconds(duration), SPOT);
    }

    void test_xml_escape()
    {
        auto function = unittest::internals::xml_escape;
        assert_equal("", function(""), SPOT);
        assert_equal("stuff", function("stuff"), SPOT);
        assert_equal("blöd", function("blöd"), SPOT);
        assert_equal("&amp;", function("&"), SPOT);
        assert_equal("&amp;stuff", function("&stuff"), SPOT);
        assert_equal("&amp;st uff &lt;", function("&st uff <"), SPOT);
        assert_equal("&quot;", function("\""), SPOT);
        assert_equal("&apos;", function("\'"), SPOT);
        assert_equal("&gt;", function(">"), SPOT);
    }

    void test_make_iso_timestamp()
    {
        auto function = unittest::internals::make_iso_timestamp;
        const time_t value = 1234567890;
        const auto time_point = std::chrono::system_clock::from_time_t(value);
        assert_equal("2009-02-13T23:31:30", function(time_point, false), SPOT);
    }

    void test_call_functions_empty_vector()
    {
        std::vector<std::function<void()>> functions;
        assert_equal(0, unittest::internals::call_functions(functions), SPOT);
        assert_equal(0, unittest::internals::call_functions(functions, 0), SPOT);
        assert_equal(0, unittest::internals::call_functions(functions, 2), SPOT);
    }

    void test_call_functions_vector_size_one()
    {
        std::function<void()> func = [](){ int a = 1; ++a; };
        std::vector<std::function<void()>> functions = {func};
        assert_equal(1, unittest::internals::call_functions(functions), SPOT);
        assert_equal(1, unittest::internals::call_functions(functions, 0), SPOT);
        assert_equal(1, unittest::internals::call_functions(functions, 2), SPOT);
    }

    void test_call_functions_vector_size_two()
    {
        std::function<void()> func = [](){ int a = 1; ++a; };
        std::vector<std::function<void()>> functions = {func, func};
        assert_equal(2, unittest::internals::call_functions(functions), SPOT);
        assert_equal(2, unittest::internals::call_functions(functions, 0), SPOT);
        assert_equal(2, unittest::internals::call_functions(functions, 2), SPOT);
        assert_equal(2, unittest::internals::call_functions(functions, 3), SPOT);
    }

    void test_make_futures_happy_empty()
    {
        std::vector<std::future<void>> futures;
        std::ostringstream stream1;
        unittest::internals::make_futures_happy(stream1, futures, false);
        assert_equal("", stream1.str(), SPOT);
        std::ostringstream stream2;
        unittest::internals::make_futures_happy(stream2, futures, true);
        assert_equal("", stream2.str(), SPOT);
    }

    void run_make_futures_happy_filled(std::ostream& stream, bool verbose)
    {
        auto functor = []() { std::this_thread::sleep_for(std::chrono::milliseconds(10)); };
        std::vector<std::future<void>> futures;
        futures.push_back(std::async(std::launch::async, functor));
        futures.push_back(std::async(std::launch::async, functor));
        unittest::internals::make_futures_happy(stream, futures, verbose);
        std::chrono::milliseconds wait_ms(1);
        for (auto& future : futures)
            assert_true(std::future_status::ready==future.wait_for(wait_ms), SPOT);
    }

    void test_make_futures_happy_filled()
    {
        std::ostringstream stream1;
        run_make_futures_happy_filled(stream1, false);
        assert_equal("", stream1.str(), SPOT);
        std::ostringstream stream2;
        run_make_futures_happy_filled(stream2, true);
        assert_equal("\nWAITING for 2 tests to finish ... \n", stream2.str(), SPOT);
    }

    void test_get_from_map()
    {
        std::map<int, int> map;
        map[0] = 1;
        assert_equal(1, unittest::internals::get_from_map(map, 0), SPOT);
    }

    void test_get_from_map_key_not_found()
    {
        auto functor = [](){
            std::map<int, int> map;
            map[0] = 1;
            unittest::internals::get_from_map(map, 2);
        };
        assert_throw<std::runtime_error>(functor, SPOT);
    }

    void test_get_type_id()
    {
        assert_equal("d", unittest::internals::get_type_id<double>(), SPOT);
    }

};

REGISTER(test_utilities)
