#include <libunittest/utilities.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#ifdef _MSC_VER
#include <iomanip>
#endif


namespace unittest {
namespace core {

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
    const auto iso_format = "%Y-%m-%dT%H:%M:%S";
    struct std::tm timeinfo;
#ifdef _MSC_VER
    if (local_time)
        localtime_s(&timeinfo, &rawtime);
    else
        gmtime_s(&timeinfo, &rawtime);
    std::stringstream buffer;
    buffer << std::put_time(&timeinfo, iso_format);
    return buffer.str();
#else
    if (local_time)
        timeinfo = *std::localtime(&rawtime);
    else
        timeinfo = *std::gmtime(&rawtime);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), iso_format, &timeinfo);
    return buffer;
#endif
}

void
write_to_stream(std::ostream&)
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

int
call_functions(const std::vector<std::function<void()>>& functions,
               int n_threads)
{
    const int n_runs = functions.size();
    if (n_threads > n_runs)
        n_threads = n_runs;

    int counter = 0;
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
    const std::string id = "@SPOT@";
    return join(id, filename, ":", linenumber, id);
}


void
make_threads_happy(std::ostream& stream,
                   std::vector<std::pair<std::thread, std::shared_ptr<std::atomic_bool>>>& threads,
                   bool verbose)
{
    int n_unfinished = 0;
    for (auto& thread : threads)
        if (!thread.second->load())
            ++n_unfinished;
    if (n_unfinished && verbose)
    	stream << "\nWAITING for " << n_unfinished << " tests to finish ... " << std::endl;
    for (auto& thread : threads)
        thread.first.join();
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

template<>
bool
to_number<bool>(const std::string& value)
{
    std::istringstream stream(value);
    bool number;
    if (stream >> number) {
        return number;
    } else {
        throw std::invalid_argument("Not a boolean: " + value);
    }
}

std::string
trim(std::string value)
{
    const std::string chars = " \t\n";
    std::string check;
    while (check!=value) {
        check = value;
        for (auto& ch : chars) {
            value.erase(0, value.find_first_not_of(ch));
            value.erase(value.find_last_not_of(ch) + 1);
        }
    }
    return value;
}

std::string
remove_white_spaces(std::string value)
{
    value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
    return value;
}

std::pair<std::string, int>
extract_file_and_line(const std::string& message)
{
    std::string filename = "";
    int linenumber = -1;
    const std::string id = "@SPOT@";
    auto index_start = message.find(id);
    if (index_start!=std::string::npos) {
        index_start += id.length();
        const auto substr = message.substr(index_start);
        const auto index_end = substr.find(id);
        if (index_end!=std::string::npos) {
            const auto spot = substr.substr(0, index_end);
            const auto separator = spot.find_last_of(":");
            if (separator!=std::string::npos) {
                filename = spot.substr(0, separator);
                linenumber = to_number<int>(spot.substr(separator+1));
            }
        }
    }
    return std::make_pair(filename, linenumber);
}

std::string
remove_file_and_line(std::string message)
{
    auto spot = extract_file_and_line(message);
    while (spot.first.size() && spot.second>-1) {
        const auto token = string_of_file_and_line(spot.first, spot.second);
        const auto index = message.find(token);
        message = message.substr(0, index) + message.substr(index+token.length());
        spot = extract_file_and_line(message);
    }
    return std::move(message);
}

} // core
} // unittest
