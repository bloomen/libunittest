#include <libunittest/random.hpp>

namespace unittest {

random_int<bool>
make_random_bool()
{
    return random_int<bool>();
}

} // unittest
