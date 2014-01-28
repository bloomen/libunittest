#include <libunittest/utilities.hpp>
#include <thread>
#include <iostream>
#ifdef _MSC_VER
#include <iomanip>
#endif


namespace unittest {
namespace internals {

std::string
xml_escape(const std::string& data)
{
    std::string escaped;
    escaped.reserve(data.size());
    for (auto& character : data) {
        switch (character) {
            case '&':  escaped.append("&amp;");       break;
            case '\"': escaped.append("&quot;");      break;
            case '\'': escaped.append("&apos;");      break;
            case '<':  escaped.append("&lt;");        break;
            case '>':  escaped.append("&gt;");        break;
            default:   escaped.append(1, character);  break;
        }
    }
    return escaped;
}

std::string
make_iso_timestamp(const std::chrono::system_clock::time_point& time_point,
                   bool local_time)
{
    const auto rawtime = std::chrono::system_clock::to_time_t(time_point);
    struct std::tm timeinfo = {};
    const auto format = "%Y-%m-%dT%H:%M:%S";
#ifdef _MSC_VER
    if (local_time)
        localtime_s(&timeinfo, &rawtime);
    else
        gmtime_s(&timeinfo, &rawtime);
    std::stringstream buffer;
    buffer << std::put_time(&timeinfo, format);
    return buffer.str();
#else
    if (local_time)
        timeinfo = *std::localtime(&rawtime);
    else
        timeinfo = *std::gmtime(&rawtime);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), format, &timeinfo);
    return buffer;
#endif
}

void
write_to_stream(std::ostream& stream)
{}

void
write_horizontal_bar(std::ostream& stream,
                     char character,
                     int length)
{
    std::string bar(length, character);
    stream << bar << std::flush;
}

double
duration_in_seconds(const std::chrono::duration<double>& duration)
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}

bool
is_regex_matched(const std::string& value,
                 const std::string& regex)
{
    return std::regex_match(value, std::regex(regex));
}

bool
is_regex_matched(const std::string& value,
                 const std::regex& regex)
{
    return std::regex_match(value, regex);
}

long
call_functions(const std::vector<std::function<void()>>& functions,
               int n_threads)
{
    const long n_runs = functions.size();
    if (n_threads > n_runs)
        n_threads = n_runs;

    long counter = 0;
    if (n_threads > 1 && n_runs > 1) {
        while (counter < n_runs) {
            if (n_threads > n_runs - counter)
                n_threads = n_runs - counter;
            std::vector<std::thread> threads(n_threads);
            for (auto& thread : threads)
                thread = std::thread(functions[counter++]);
            for (auto& thread : threads)
                thread.join();
        }
    } else {
        for (auto& function : functions) {
            function();
            ++counter;
        }
    }

    return counter;
}

std::string
limit_string_length(const std::string& value,
                    int max_length)
{
    if (int(value.size()) > max_length) {
        return value.substr(0, max_length);
    } else {
        return value;
    }
}

std::string
string_of_file_and_line(const std::string& filename,
                        int linenumber)
{
    return join(" @", filename, ":", linenumber, ". ");
}


void
make_futures_happy(std::ostream& stream,
                   const std::vector<std::future<void>>& futures,
                   bool verbose)
{
    static std::mutex make_futures_happy_mutex_;
    std::lock_guard<std::mutex> lock(make_futures_happy_mutex_);
    const auto wait_ms = std::chrono::milliseconds(1);
    long n_unfinished(0);
    for (auto& future : futures)
        if (future.wait_for(wait_ms)!=std::future_status::ready)
            ++n_unfinished;
    if (n_unfinished) {
        if (verbose)
            stream << "\nWAITING for " << n_unfinished << " tests to finish ... " << std::flush;
        for (auto& future : futures)
            future.wait();
        if (verbose)
            stream << std::endl;
    }
}

bool
is_numeric(const std::string& value)
{
    bool result;
    try {
        to_number<double>(value);
        result = true;
    } catch (const std::invalid_argument&) {
        result = false;
    }
    return result;
}

std::string
trim(std::string value)
{
    const std::string chars = " \t\n";
    std::string check;
    while (check != value) {
        check = value;
        for (auto& ch : chars) {
            value.erase(0, value.find_first_not_of(ch));
            value.erase(value.find_last_not_of(ch) + 1);
        }
    }
    return value;
}

} // internals
} // unittest
