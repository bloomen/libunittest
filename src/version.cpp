#include <libunittest/version.hpp>
#include <libunittest/utilities.hpp>

namespace unittest {

std::tuple<int,int,int,std::string>
get_version_tuple()
{
    return std::make_tuple(3, 2, 1, "dev");
}

std::string
get_version_string()
{
    int a, b, c;
    std::string flag;
    std::tie(a, b, c, flag) = unittest::get_version_tuple();
    return join(a, ".", b, ".", c, flag);
}

} // unittest
