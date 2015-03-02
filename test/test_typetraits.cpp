#include <libunittest/all.hpp>
using namespace unittest::assertions;


struct has_all {
    bool operator==(has_all const&) const { return true; }
    bool operator<(has_all const&) const { return true; }
    bool operator>(has_all const&) const { return true; }
};
std::ostream& operator<<(std::ostream& stream, has_all const&) { return stream; }


struct has_all_nc {
    bool operator==(has_all_nc &) { return true; }
    bool operator<(has_all_nc &) { return true; }
    bool operator>(has_all_nc &) { return true; }
};
std::ostream& operator<<(std::ostream& stream, has_all_nc &) { return stream; }


struct has_eqop {
    bool operator==(has_eqop const&) const { return true; }
};


struct has_eqop_nc {
    bool operator==(has_eqop_nc &) { return true; }
};


struct has_leop {
    bool operator<(has_leop const&) const { return true; }
};


struct has_leop_nc {
    bool operator<(has_leop_nc &) { return true; }
};


struct has_grop {
    bool operator>(has_grop const&) const { return true; }
};


struct has_grop_nc {
    bool operator>(has_grop_nc &) { return true; }
};


struct has_stop {
};
std::ostream& operator<<(std::ostream& stream, has_stop const&) { return stream; }


struct has_stop_nc {
};
std::ostream& operator<<(std::ostream& stream, has_stop_nc &) { return stream; }


struct test_typetraits : unittest::testcase<> {

	static void run()
	{
		UNITTEST_CLASS(test_typetraits)
		UNITTEST_RUN(test_is_output_streamable_positives)
		UNITTEST_RUN(test_is_output_streamable_negatives)
	}

	void test_is_output_streamable_positives()
	{
		static_assert(unittest::core::is_output_streamable<bool>::value, "");
		static_assert(unittest::core::is_output_streamable<int>::value, "");
		static_assert(unittest::core::is_output_streamable<float*>::value, "");
		static_assert(unittest::core::is_output_streamable<has_all>::value, "");
		static_assert(unittest::core::is_output_streamable<has_all_nc>::value, "");
		static_assert(unittest::core::is_output_streamable<has_stop>::value, "");
		static_assert(unittest::core::is_output_streamable<has_stop_nc>::value, "");
	}

	void test_is_output_streamable_negatives()
	{
		static_assert(!unittest::core::is_output_streamable<void>::value, "");
		static_assert(!unittest::core::is_output_streamable<unittest::sometype>::value, "");
		static_assert(!unittest::core::is_output_streamable<unittest::notype>::value, "");
		static_assert(!unittest::core::is_output_streamable<has_eqop>::value, "");
		static_assert(!unittest::core::is_output_streamable<has_eqop_nc>::value, "");
		static_assert(!unittest::core::is_output_streamable<has_leop>::value, "");
		static_assert(!unittest::core::is_output_streamable<has_leop_nc>::value, "");
		static_assert(!unittest::core::is_output_streamable<has_grop>::value, "");
		static_assert(!unittest::core::is_output_streamable<has_grop_nc>::value, "");
	}

};
REGISTER(test_typetraits)
