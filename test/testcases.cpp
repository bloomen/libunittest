#include "test_assertions.h"
#include "test_misc.h"
#include "test_argparser.h"
#include "test_random.h"
using namespace unittest;

void unittest::run_all_tests() {
    call<test_assertions>();
    call<test_misc>();
    call<test_argparser>();
    call<test_random>();

//    std::thread t1(call<test_assertions>);
//    std::thread t2(call<test_misc>);
//    std::thread t3(call<test_argparser>);
//    std::thread t4(call<test_random>);
//
//    t4.join();
//    t3.join();
//    t2.join();
//    t1.join();
}
