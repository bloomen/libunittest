#include <libunittest/all.hpp>
using namespace unittest::core;


struct test_quote : unittest::testcase<> {

    static void run()
    {
        UNITTEST_CLASS(test_quote)
        UNITTEST_RUN(test_quote_struct_ostream_operator)
        UNITTEST_RUN(test_quote_struct)
        UNITTEST_RUN(test_quote_generator)
    }

    void test_quote_generator()
    {
        quote_generator gen{1};
        std::ostringstream os;
        os << gen.next();
        ASSERT_TRUE(os.str().size() > 0);
    }

    void test_quote_struct()
    {
        quote q{"msg", "person"};
        ASSERT_EQUAL("msg", q.message);
        ASSERT_EQUAL("person", q.author);
    }

    void test_quote_struct_ostream_operator()
    {
        quote q{"msg", "person"};
        std::ostringstream os;
        os << q;
        const std::string expected = "\"msg\" - person";
        ASSERT_EQUAL(expected, os.str());
    }

};
REGISTER(test_quote)
