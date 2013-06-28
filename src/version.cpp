#include <libunittest/version.hpp>
#include <libunittest/utilities.hpp>

namespace unittest {

std::tuple<int,int,int>
get_version_tuple()
{
    return std::make_tuple(3, 1, 3);
}

std::string
get_version_string()
{
    const auto vs = get_version_tuple();
    return join(std::get<0>(vs), ".", std::get<1>(vs), ".", std::get<2>(vs));
}

} // unittest
