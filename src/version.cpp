#include <libunittest/version.hpp>
#include <libunittest/utilities.hpp>

std::tuple<int,int,int>
unittest::get_version_tuple()
{
    return std::make_tuple(3, 0, 0);
}

std::string
unittest::get_version_string()
{
    const auto vs = get_version_tuple();
    return join(std::get<0>(vs), ".", std::get<1>(vs), ".", std::get<2>(vs));
}
