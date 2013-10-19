#include <libunittest/testcase.hpp>

namespace unittest {

testcase<internals::nocontext>::testcase()
{}

testcase<internals::nocontext>::~testcase()
{}

internals::nocontext*
testcase<internals::nocontext>::get_test_context() const
{
    internals::nocontext *context(nullptr);
    return context;
}

void
testcase<internals::nocontext>::set_up()
{}

void
testcase<internals::nocontext>::tear_down()
{}

}
