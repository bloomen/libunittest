#include <libunittest/all.hpp>
using namespace unittest::assertions;

using unittest::core::extract_tagged_text;

struct test_utilities : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_utilities)
        UNITTEST_RUN(test_limit_string_length)
        UNITTEST_RUN(test_string_of_file_and_line)
        UNITTEST_RUN(test_string_of_tagged_text)
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
        UNITTEST_RUN(test_make_threads_happy_empty)
        UNITTEST_RUN(test_make_threads_happy_filled)
        UNITTEST_RUN(test_get_from_map)
        UNITTEST_RUN(test_get_from_map_key_not_found)
        UNITTEST_RUN(test_get_type_id)
        UNITTEST_RUN(test_is_numeric)
        UNITTEST_RUN(test_to_number)
        UNITTEST_RUN(test_trim)
        UNITTEST_RUN(test_remove_white_spaces)
        UNITTEST_RUN(test_extract_file_and_line_spot_found)
        UNITTEST_RUN(test_extract_file_and_line_spot_found_two)
        UNITTEST_RUN(test_extract_file_and_line_spot_not_found)
        UNITTEST_RUN(test_extract_file_and_line_spot_weird)
        UNITTEST_RUN(test_extract_tagged_text_found)
        UNITTEST_RUN(test_remove_tagged_text_found)
        UNITTEST_RUN(test_remove_tagged_text_found_at_end)
        UNITTEST_RUN(test_remove_tagged_text_found_two)
        UNITTEST_RUN(test_remove_tagged_text_not_found)
        UNITTEST_RUN(test_make_unique)
        UNITTEST_RUN(test_now)
        UNITTEST_RUN(test_isnan)
        UNITTEST_RUN(test_isfinite)
    }

    void test_isfinite()
    {
        assert_true(unittest::core::isfinite(0.), SPOT);
        assert_true(unittest::core::isfinite(42), SPOT);
        assert_true(unittest::core::isfinite(1.3), SPOT);
        assert_true(unittest::core::isfinite(true), SPOT);
        assert_true(unittest::core::isfinite("peter"), SPOT);
        assert_true(unittest::core::isfinite(std::numeric_limits<double>::min()), SPOT);
        assert_true(unittest::core::isfinite(std::numeric_limits<double>::max()), SPOT);
        assert_false(unittest::core::isfinite(std::numeric_limits<double>::infinity()), SPOT);
        assert_false(unittest::core::isfinite(std::numeric_limits<double>::quiet_NaN()), SPOT);
    }

    void test_isnan()
    {
        assert_false(unittest::core::isnan(0.), SPOT);
        assert_false(unittest::core::isnan(42), SPOT);
        assert_false(unittest::core::isnan(1.3), SPOT);
        assert_false(unittest::core::isnan(true), SPOT);
        assert_false(unittest::core::isnan("peter"), SPOT);
        assert_false(unittest::core::isnan(std::numeric_limits<double>::min()), SPOT);
        assert_false(unittest::core::isnan(std::numeric_limits<double>::max()), SPOT);
        assert_false(unittest::core::isnan(std::numeric_limits<double>::infinity()), SPOT);
        assert_true(unittest::core::isnan(std::numeric_limits<double>::quiet_NaN()), SPOT);
    }

    void test_now()
    {
        const auto now1 = unittest::core::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        const auto now2 = unittest::core::now();
        const auto duration = unittest::core::duration_in_seconds(now2 - now1);
        assert_in_range(duration, 0.1, 0.3, SPOT);
    }

    void test_limit_string_length()
    {
        auto function = unittest::core::limit_string_length;
        assert_equal("albert", function("albert", 8), SPOT);
        assert_equal("albert", function("albert", 6), SPOT);
        assert_equal("alber", function("albert", 5), SPOT);
        assert_equal("a", function("albert", 1), SPOT);
        assert_equal("", function("albert", 0), SPOT);
        assert_equal("albert", function("albert", -1), SPOT);
        assert_equal("albert", function("albert", -3), SPOT);
    }

    void test_string_of_tagged_text()
    {
        auto function = unittest::core::string_of_tagged_text;
        assert_equal("@NDAS@albert@NDAS@", function("albert", "NDAS"), SPOT);
    }

    void test_string_of_file_and_line()
    {
        auto function = unittest::core::string_of_file_and_line;
        assert_equal("@SPOT@albert:13@SPOT@", function("albert", 13), SPOT);
        assert_equal("@SPOT@blöd:-42@SPOT@", function("blöd", -42), SPOT);
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
        unittest::core::write_to_stream(stream, value_string, " = ", value_double);
        assert_equal("pi = 3.1415", stream.str(), SPOT);
    }

    void test_write_to_stream_overload()
    {
        std::ostringstream stream;
        unittest::core::write_to_stream(stream);
        assert_equal("", stream.str(), SPOT);
    }

    void test_write_horizontal_bar()
    {
        auto function = unittest::core::write_horizontal_bar;
        std::ostringstream stream;
        function(stream, 'x', 3);
        assert_equal("xxx", stream.str(), SPOT);
        assert_throw<std::length_error>([&]() { function(stream, 'x', -1); }, SPOT);
    }

    void test_duration_in_seconds()
    {
        const std::chrono::duration<double> duration(1);
        assert_equal(1, unittest::core::duration_in_seconds(duration), SPOT);
    }

    void test_xml_escape()
    {
        auto function = unittest::core::xml_escape;
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
        auto function = unittest::core::make_iso_timestamp;
        const time_t value = 1234567890;
        const auto time_point = std::chrono::system_clock::from_time_t(value);
        assert_equal("2009-02-13T23:31:30", function(time_point, false), SPOT);
    }

    void test_call_functions_empty_vector()
    {
        using unittest::core::call_functions;
        std::vector<std::function<void()>> functions;
        assert_equal(0, call_functions(functions), SPOT);
        assert_equal(0, call_functions(functions, 0), SPOT);
        assert_equal(0, call_functions(functions, 2), SPOT);
    }

    void test_call_functions_vector_size_one()
    {
        using unittest::core::call_functions;
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
        using unittest::core::call_functions;
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

    void test_make_threads_happy_empty()
    {
        std::vector<std::pair<std::thread, std::shared_ptr<std::atomic_bool>>> threads;
        std::ostringstream stream1;
        unittest::core::make_threads_happy(stream1, threads, false);
        assert_equal("", stream1.str(), SPOT);
        std::ostringstream stream2;
        unittest::core::make_threads_happy(stream2, threads, true);
        assert_equal("", stream2.str(), SPOT);
    }

    void run_make_threads_happy_filled(std::ostream& stream, bool verbose, int n_threads)
    {
        std::vector<std::pair<std::thread, std::shared_ptr<std::atomic_bool>>> threads;
        for (int i=0; i<n_threads; ++i) {
            std::shared_ptr<std::atomic_bool> done = std::make_shared<std::atomic_bool>();
            done->store(false);
            auto function = [done]() { std::this_thread::sleep_for(std::chrono::milliseconds(100)); done->store(true); };
            std::thread thread(function);
            threads.push_back(std::make_pair(std::move(thread), done));
        }
        unittest::core::make_threads_happy(stream, threads, verbose);
        std::chrono::milliseconds wait_ms(1);
        for (auto& thread : threads)
            assert_true(thread.second->load(), SPOT);
    }

    void test_make_threads_happy_filled()
    {
        int n_threads = 3;
        std::ostringstream stream1;
        run_make_threads_happy_filled(stream1, false, n_threads);
        assert_equal("", stream1.str(), SPOT);
        std::ostringstream stream2;
        run_make_threads_happy_filled(stream2, true, n_threads);
        assert_equal(unittest::join("\nWaiting for ", n_threads, " tests to finish ... \n"), stream2.str(), SPOT);
    }

    void test_get_from_map()
    {
        std::map<int, int> map;
        map[0] = 1;
        assert_equal(1, unittest::core::get_from_map(map, 0), SPOT);
    }

    void test_get_from_map_key_not_found()
    {
        std::map<int, int> map;
        map[0] = 1;
        auto functor = [&](){ unittest::core::get_from_map(map, 2); };
        assert_throw<std::runtime_error>(functor, SPOT);
    }

    void test_get_type_id()
    {
        const std::string id = typeid(double).name();
        assert_equal(id, unittest::core::get_type_id<double>(), SPOT);
    }

    void test_is_numeric()
    {
        std::vector<std::string> values_num = {
                "764", " 132.0", "930 ", " 93.7 ", "\t\n42\t ", "97", "-102 bc"
        };
        for (auto& value : values_num)
            assert_true(unittest::core::is_numeric(value), SPOT, "value: ", value);
        std::vector<std::string> values_not_num = {
                "", "XYZ", "a26"
        };
        for (auto& value : values_not_num)
            assert_false(unittest::core::is_numeric(value), SPOT, "value: ", value);
    }

    void test_to_number()
    {
        using unittest::core::to_number;
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
        auto function = unittest::core::trim;
        assert_equal("albert", function("albert"), SPOT);
        assert_equal("albert peter", function("albert peter  "), SPOT);
        assert_equal("albert  püter", function("albert  püter  "), SPOT);
        assert_equal("albert  peter", function("   albert  peter  "), SPOT);
        assert_equal("ölbert  \tpeter", function("\n   ölbert  \tpeter  \t"), SPOT);
        assert_equal("albert  \npeter", function("\n\t   albert  \npeter  \n\n"), SPOT);
    }

    void test_remove_white_spaces()
    {
        auto function = unittest::core::remove_white_spaces;
        assert_equal("albert", function("albert"), SPOT);
        assert_equal("albert", function("alb ert "), SPOT);
        assert_equal("albert", function("  alber t "), SPOT);
    }

    void test_extract_tagged_text_found()
    {
        const std::string expected = "test_id";
        assert_equal(expected, extract_tagged_text("some text @NDAS@" + expected + "@NDAS@ more text", "NDAS"), SPOT);
    }

    void test_extract_file_and_line_spot_found()
    {
        auto function = unittest::core::extract_file_and_line;
        const auto result = function("some text @SPOT@c:\algo\nada.cpp:13@SPOT@ more text");
        assert_equal("c:\algo\nada.cpp", result.first, SPOT);
        assert_equal(13, result.second, SPOT);
    }

    void test_extract_file_and_line_spot_found_two()
    {
        auto function = unittest::core::extract_file_and_line;
        const auto result = function("some text @SPOT@nada.cpp:13@SPOT@ more text @SPOT@kalle.cpp:42@SPOT@");
        assert_equal("nada.cpp", result.first, SPOT);
        assert_equal(13, result.second, SPOT);
    }

    void test_extract_file_and_line_spot_not_found()
    {
        auto function = unittest::core::extract_file_and_line;
        const auto result = function("some text");
        assert_equal("", result.first, SPOT);
        assert_equal(-1, result.second, SPOT);
    }

    void test_extract_file_and_line_spot_weird()
    {
        auto function = unittest::core::extract_file_and_line;
        const auto result1 = function("some text @SPOT@nada.cpp:13 more text");
        assert_equal("", result1.first, SPOT);
        assert_equal(-1, result1.second, SPOT);
        const auto result2 = function("some text @SPOT@nada.cpp-13@SPOT@ more text");
        assert_equal("", result2.first, SPOT);
        assert_equal(-1, result2.second, SPOT);
    }

    void test_remove_tagged_text_found()
    {
        auto function = unittest::core::remove_tagged_text;
        const auto result = function("some text @SPOT@nada.cpp:13@SPOT@ more text", "SPOT");
        assert_equal("some text  more text", result, SPOT);
    }

    void test_remove_tagged_text_found_at_end()
    {
        auto function = unittest::core::remove_tagged_text;
        const auto result = function("some text@SPOT@nada.cpp:13@SPOT@", "SPOT");
        assert_equal("some text", result, SPOT);
    }

    void test_remove_tagged_text_found_two()
    {
        auto function = unittest::core::remove_tagged_text;
        const auto result = function("some text @SPOT@nada.cpp:13@SPOT@cool@SPOT@kunde.cpp:42@SPOT@", "SPOT");
        assert_equal("some text cool", result, SPOT);
    }

    void test_remove_tagged_text_not_found()
    {
        auto function = unittest::core::remove_tagged_text;
        const auto result = function("some text", "SPOT");
        assert_equal("some text", result, SPOT);
    }

    void test_make_unique()
    {
        using unittest::core::make_unique;

        assert_true(make_unique<int>(), SPOT);
        assert_true(make_unique<std::string>(), SPOT);

        auto ptr1 = make_unique<int>(1729);
        assert_equal(1729, *ptr1, SPOT);

        auto ptr2 = make_unique<std::string>("meow");
        assert_equal("meow", *ptr2, SPOT);

        auto ptr3 = make_unique<std::string>(6, 'z');
        assert_equal("zzzzzz", *ptr3, SPOT);

        auto vector = make_unique<std::vector<float>>(3);
        assert_equal<unsigned>(3, vector->size(), SPOT);
    }

};

REGISTER(test_utilities)
