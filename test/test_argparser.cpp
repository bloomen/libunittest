#include <libunittest/all.hpp>
using namespace unittest::assertions;
using unittest::core::argparser;


struct client_empty : argparser {};


struct client_real : argparser {
    client_real()
        : a("duck"), b(3), c(false)
    {
        register_argument('a', "", "aaa", a, true);
        register_argument('b', "bb", "bbb", b, false, true);
        register_trigger('c', "cc", "ccc", c);
    }
    std::string a;
    double b;
    bool c;
private:
    std::string app_name()
    {
        return "cool";
    }
    std::string description()
    {
        return "Wicked program";
    }
    void assign_values()
    {
        assign_value(a, 'a');
        assign_value(b, 'b');
        assign_value(c, 'c');
    }
    void post_parse()
    {
        if (b<=-20)
            error("bb must be larger than -20");
    }
};


struct client_bad1 : argparser {
    client_bad1()
        : a(0)
    {
        register_argument('a', "aa", "aaa", a, true);
        register_argument('a', "aa", "aaa", a, true);
    }
    double a;
};


struct client_bad2 : argparser {
    client_bad2()
        : a(0)
    {
        register_argument('a', "aa", "aaa", a, true);
    }
    double a;
private:
    void assign_values()
    {
        assign_value(a, 'c');
    }
};


struct client_bad3 : argparser {
    client_bad3()
        : a(0)
    {
        register_argument('a', "aa", "aaa", a, true);
    }
    double a;
private:
    void assign_values()
    {
        assign_value(a, 'a');
        assign_value(a, 'a');
    }
};


struct test_argparser : unittest::testcase<> {

    test_argparser(const test_argparser&) = delete;
    test_argparser& operator=(const test_argparser&) = delete;

    static void run()
    {
        UNITTEST_CLASS(test_argparser)
        UNITTEST_RUN(test_empty_client)
        UNITTEST_RUN(test_empty_client_ostream)
        UNITTEST_RUN(test_empty_client_get_help)
        UNITTEST_RUN(test_empty_client_with_help)
        UNITTEST_RUN(test_empty_client_with_unknown_arg)
        UNITTEST_RUN(test_real_client_get_help)
        UNITTEST_RUN(test_real_client_with_help)
        UNITTEST_RUN(test_real_client_ostream)
        UNITTEST_RUN(test_real_client_with_missing_arg)
        UNITTEST_RUN(test_real_client_with_provided_args)
        UNITTEST_RUN(test_real_client_with_double_args)
        UNITTEST_RUN(test_real_client_with_double_args_at_end)
        UNITTEST_RUN(test_real_client_with_missing_value)
        UNITTEST_RUN(test_real_client_with_wrong_value)
        UNITTEST_RUN(test_client_bad1)
        UNITTEST_RUN(test_client_bad2)
        UNITTEST_RUN(test_client_bad3)
    }

    char** argv_;

    test_argparser()
        : argv_(new char*[100])
    {
        argv_[0] = (char*)"wicked";
    }

    ~test_argparser()
    {
        delete[] argv_;
    }

    void test_empty_client()
    {
        client_empty client;
        client.parse(1, argv_);
        assert_equal(std::string(argv_[0]), client.command_line(), SPOT);
    }

    void test_empty_client_ostream()
    {
        client_empty client;
        std::ostringstream os1;
        os1 << client;
        assert_equal("", os1.str(), SPOT);
        client.parse(1, argv_);
        std::ostringstream os2;
        os2 << client;
        assert_equal("", os2.str(), SPOT);
    }

    void test_empty_client_get_help()
    {
        client_empty client;
        std::string exp;
        exp += "Usage: program [Arguments]\n\n";
        exp += "Arguments:\n";
        exp += "-h    Displays this help message and exits\n";
        assert_equal(exp, client.get_help(), SPOT);
    }

    void test_empty_client_with_help()
    {
        client_empty client;
        argv_[1] = (char*)"-h";
        std::string msg;
        try {
            client.parse(2, argv_);
        } catch (const argparser::exit_success& e) {
            msg = e.what();
        }
        assert_equal(std::string(argv_[0]) + " -h", client.command_line(), SPOT);
        std::string exp;
        exp += "Usage: wicked [Arguments]\n\n";
        exp += "Arguments:\n";
        exp += "-h    Displays this help message and exits\n";
        assert_equal(exp, msg, SPOT);
    }

    void test_empty_client_with_unknown_arg()
    {
        client_empty client;
        argv_[1] = (char*)"-p";
        std::string msg;
        try {
            client.parse(2, argv_);
        } catch (const argparser::exit_error& e) {
            msg = e.what();
        }
        assert_equal(std::string(argv_[0]) + " -p", client.command_line(), SPOT);
        std::string exp;
        exp += "Invalid argument: '-p'\n";
        assert_equal(exp, msg, SPOT);
    }

    void test_real_client_with_help()
    {
        client_real client;
        std::string msg;
        argv_[1] = (char*)"-h";
        try {
            client.parse(2, argv_);
        } catch (const argparser::exit_success& e) {
            msg = e.what();
        }
        assert_equal(std::string(argv_[0]) + " -h", client.command_line(), SPOT);
        std::string exp;
        exp += "Wicked program\n\n";
        exp += "Usage: cool -b bb [Arguments]\n\n";
        exp += "Arguments:\n";
        exp += "-h     Displays this help message and exits\n";
        exp += "-a     aaa (default: duck)\n";
        exp += "-b bb  bbb (required)\n";
        exp += "-c     ccc\n";
        assert_equal(exp, msg, SPOT);
    }

    void test_real_client_get_help()
    {
        client_real client;
        std::string exp;
        exp += "Wicked program\n\n";
        exp += "Usage: cool -b bb [Arguments]\n\n";
        exp += "Arguments:\n";
        exp += "-h     Displays this help message and exits\n";
        exp += "-a     aaa (default: duck)\n";
        exp += "-b bb  bbb (required)\n";
        exp += "-c     ccc\n";
        assert_equal(exp, client.get_help(), SPOT);
    }

    void test_real_client_ostream()
    {
        client_real client;
        std::ostringstream os1;
        os1 << client;
        assert_equal("-a    = \"duck\"\n-b bb = 3\n-c cc = false\n", os1.str(), SPOT);
        argv_[1] = (char*)"-b";
        argv_[2] = (char*)"2";
        client.parse(3, argv_);
        std::ostringstream os2;
        os2 << client;
        assert_equal("-a    = \"duck\"\n-b bb = 2\n-c cc = false\n", os2.str(), SPOT);
    }

    void test_real_client_with_missing_arg()
    {
        client_real client;
        std::string msg;
        try {
            client.parse(1, argv_);
        } catch (const argparser::exit_error& e) {
            msg = e.what();
        }
        assert_equal(std::string(argv_[0]), client.command_line(), SPOT);
        std::string exp;
        exp += "Missing required argument '-b'\n";
        assert_equal(exp, msg, SPOT);
    }

    void test_real_client_with_provided_args()
    {
        client_real client;
        argv_[1] = (char*)"-ca";
        argv_[2] = (char*)"suck";
        argv_[3] = (char*)"-b";
        argv_[4] = (char*)"-13.4";
        client.parse(5, argv_);
        assert_equal(std::string(argv_[0]) + " -ca suck -b -13.4", client.command_line(), SPOT);
        assert_equal("suck", client.a, SPOT);
        assert_equal(-13.4, client.b, SPOT);
        assert_equal(true, client.c, SPOT);
    }

    void test_real_client_with_double_args()
    {
        client_real client;
        argv_[1] = (char*)"-c";
        argv_[2] = (char*)"-c";
        argv_[3] = (char*)"-b";
        argv_[4] = (char*)"-13.4";
        client.parse(5, argv_);
        assert_equal("duck", client.a, SPOT);
        assert_equal(-13.4, client.b, SPOT);
        assert_equal(true, client.c, SPOT);
    }

    void test_real_client_with_double_args_at_end()
    {
        client_real client;
        argv_[1] = (char*)"-c";
        argv_[2] = (char*)"-b";
        argv_[3] = (char*)"-13.4";
        argv_[4] = (char*)"-c";
        argv_[5] = (char*)"-b";
        argv_[6] = (char*)"42";
        client.parse(7, argv_);
        assert_equal("duck", client.a, SPOT);
        assert_equal(-13.4, client.b, SPOT);
        assert_equal(true, client.c, SPOT);
    }

    void test_real_client_with_missing_value()
    {
        client_real client;
        std::string msg;
        argv_[1] = (char*)"-b";
        try {
            client.parse(2, argv_);
        } catch (const argparser::exit_error& e) {
            msg = e.what();
        }
        assert_equal(std::string(argv_[0]) + " -b", client.command_line(), SPOT);
        std::string exp;
        exp += "Missing value to argument '-b'\n";
        assert_equal(exp, msg, SPOT);
    }

    void test_real_client_with_wrong_value()
    {
        client_real client;
        std::string msg;
        argv_[1] = (char*)"-b";
        argv_[2] = (char*)"-30";
        try {
            client.parse(3, argv_);
        } catch (const argparser::exit_error& e) {
            msg = e.what();
        }
        assert_equal(std::string(argv_[0]) + " -b -30", client.command_line(), SPOT);
        std::string exp;
        exp += "bb must be larger than -20\n";
        assert_equal(exp, msg, SPOT);
    }

    void test_client_bad1()
    {
        auto functor = []() { client_bad1 c; };
        assert_throw<std::invalid_argument>(functor, SPOT);
    }

    void test_client_bad2()
    {
        auto functor = [this]() { client_bad2 c; c.parse(1, argv_); };
        assert_throw<std::invalid_argument>(functor, SPOT);
    }

    void test_client_bad3()
    {
        auto functor = [this]() { client_bad3 c; c.parse(1, argv_); };
        assert_throw<std::invalid_argument>(functor, SPOT);
    }

};

REGISTER(test_argparser)
