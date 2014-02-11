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
        UNITTEST_RUN(test_is_numeric)
        UNITTEST_RUN(test_to_number)
        UNITTEST_RUN(test_trim)
        UNITTEST_RUN(test_remove_white_spaces)
        UNITTEST_RUN(test_expand_commandline_arguments)
        UNITTEST_RUN(test_expand_commandline_arguments_empty_args)
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
        assert_throw<std::length_error>([&]() { function(stream, 'x', -1); }, SPOT);
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
        using unittest::internals::call_functions;
        std::vector<std::function<void()>> functions;
        assert_equal(0, call_functions(functions), SPOT);
        assert_equal(0, call_functions(functions, 0), SPOT);
        assert_equal(0, call_functions(functions, 2), SPOT);
    }

    void test_call_functions_vector_size_one()
    {
        using unittest::internals::call_functions;
        int a = 0;
        std::function<void()> func = [&a](){ ++a; };
        std::vector<std::function<void()>> functions = {func};
        assert_equal(1, call_functions(functions), SPOT);
        assert_equal(1, a, SPOT);
        assert_equal(1, call_functions(functions, 0), SPOT);
        assert_equal(2, a, SPOT);
        assert_equal(1, call_functions(functions, 2), SPOT);
        assert_equal(3, a, SPOT);
    }

    void test_call_functions_vector_size_two()
    {
        using unittest::internals::call_functions;
        int a = 0;
        std::function<void()> func1 = [&a](){ ++a; };
        int b = 0;
        std::function<void()> func2 = [&b](){ ++b; };
        std::vector<std::function<void()>> functions = {func1, func2};
        assert_equal(2, call_functions(functions), SPOT);
        assert_equal(1, a, SPOT);
        assert_equal(1, b, SPOT);
        assert_equal(2, call_functions(functions, 0), SPOT);
        assert_equal(2, a, SPOT);
        assert_equal(2, b, SPOT);
        assert_equal(2, call_functions(functions, 2), SPOT);
        assert_equal(3, a, SPOT);
        assert_equal(3, b, SPOT);
        assert_equal(2, call_functions(functions, 3), SPOT);
        assert_equal(4, a, SPOT);
        assert_equal(4, b, SPOT);
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
        auto functor = []() { std::this_thread::sleep_for(std::chrono::milliseconds(100)); };
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
        std::map<int, int> map;
        map[0] = 1;
        auto functor = [&](){ unittest::internals::get_from_map(map, 2); };
        assert_throw<std::runtime_error>(functor, SPOT);
    }

    void test_get_type_id()
    {
        const std::string id = typeid(double).name();
        assert_equal(id, unittest::internals::get_type_id<double>(), SPOT);
    }

    void test_is_numeric()
    {
        std::vector<std::string> values_num = {
                "764", " 132.0", "930 ", " 93.7 ", "\t\n42\t ", "97", "-102 bc"
        };
        for (auto& value : values_num)
            assert_true(unittest::internals::is_numeric(value), SPOT, "value: ", value);
        std::vector<std::string> values_not_num = {
                "", "XYZ", "a26"
        };
        for (auto& value : values_not_num)
            assert_false(unittest::internals::is_numeric(value), SPOT, "value: ", value);
    }

    void test_to_number()
    {
        using unittest::internals::to_number;
        assert_equal(764, to_number<int>("764"), SPOT);
        assert_equal(132, to_number<long>("132.0"), SPOT);
        assert_equal(930, to_number<float>("930"), SPOT);
        assert_equal(-93.7, to_number<double>("-93.7"), SPOT);
        std::vector<std::string> values_not_num = { "", "XYZ", "a26" };
        for (auto& value : values_not_num)
            assert_throw<std::invalid_argument>([&](){ to_number<int>(value); }, SPOT, "value: ", value);
    }

    void test_trim()
    {
        auto function = unittest::internals::trim;
        assert_equal("albert", function("albert"), SPOT);
        assert_equal("albert peter", function("albert peter  "), SPOT);
        assert_equal("albert  püter", function("albert  püter  "), SPOT);
        assert_equal("albert  peter", function("   albert  peter  "), SPOT);
        assert_equal("ölbert  \tpeter", function("\n   ölbert  \tpeter  \t"), SPOT);
        assert_equal("albert  \npeter", function("\n\t   albert  \npeter  \n\n"), SPOT);
    }

    void test_remove_white_spaces()
    {
        auto function = unittest::internals::remove_white_spaces;
        assert_equal("albert", function("albert"), SPOT);
        assert_equal("albert", function("alb ert "), SPOT);
        assert_equal("albert", function("  alber t "), SPOT);
    }

    void test_expand_commandline_arguments()
    {
        auto function = unittest::internals::expand_commandline_arguments;
        std::vector<std::string> args = { "-ag", "-i", "42", "-tpf" };
        std::vector<std::string> exp_args = { "-a", "-g", "-i", "42", "-t", "-p", "-f" };
        assert_equal_containers(exp_args, function(args));
    }

    void test_expand_commandline_arguments_empty_args()
    {
        auto function = unittest::internals::expand_commandline_arguments;
        std::vector<std::string> args = {};
        std::vector<std::string> exp_args = {};
        assert_equal_containers(exp_args, function(args));
    }

};

REGISTER(test_utilities)
