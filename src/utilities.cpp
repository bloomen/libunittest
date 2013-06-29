#include <libunittest/utilities.hpp>

namespace unittest {

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

bool
is_test_executed(const std::string& test_name,
                 const std::string& exact_name,
                 const std::string& filter_name)
{
    if (exact_name!="") {
        if (exact_name==test_name)
            return true;
        else
            return false;
    }

    if (filter_name!="") {
        if (test_name.substr(0, filter_name.size())==filter_name)
            return true;
        else
            return false;
    }

    return true;
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

std::string
xml_escape(const std::string& data)
{
    std::string escaped("");
    escaped.reserve(data.size());
    for (auto character : data) {
        switch (character) {
            case '&':  escaped.append("&amp;");       break;
            case '\"': escaped.append("&quot;");      break;
            case '\'': escaped.append("&apos;");      break;
            case '<':  escaped.append("&lt;");        break;
            case '>':  escaped.append("&gt;");        break;
            default:   escaped.append(1, character);  break;
        }
    }
    return std::move(escaped);
}

std::string
make_iso_timestamp(const std::chrono::system_clock::time_point& time_point)
{
    const auto rawtime = std::chrono::system_clock::to_time_t(time_point);
    struct tm timeinfo = *std::localtime(&rawtime);
    char buffer[20];
    std::strftime(buffer, 20, "%FT%X", &timeinfo);
    return buffer;
}

} // unittest
