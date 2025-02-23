#include "uniq.hpp"

struct Test {
    Test() { ::fmt::print("{}\n", __PRETTY_FUNCTION__); }
    ~Test() { ::fmt::print("{}\n", __PRETTY_FUNCTION__); }
};

struct DeleterTest {
    void operator()(Test* pointer) {
        if (pointer) {
            delete pointer;
            ::fmt::print("{}", __PRETTY_FUNCTION__);
        }
    }
};

int main() {
    // {
    //     ::memory::unique_ptr::UniquePtr<Test> smart_int;
    //     auto a = smart_int.relese();
    //     if (!a) {
    //         ::fmt::print("OK\n");
    //     } else {
    //         ::fmt::print("FAIL\n");
    //         return -1;
    //     }
    // }

    // {
    //     ::memory::unique_ptr::UniquePtr<Test> smart_int(new Test);
    //     auto a = smart_int.relese();
    //     if (a) {
    //         ::fmt::print("OK\n");
    //     } else {
    //         ::fmt::print("FAIL\n");
    //         return -1;
    //     }
    // }

    {
        ::memory::unique_ptr::UniquePtr<int> uniq_int1(new int(10));
        ::memory::unique_ptr::UniquePtr<int> uniq_int2(new int(20));

        ::fmt::print("uniq_int1 = {}\n", *uniq_int1);
        ::fmt::print("uniq_int2 = {}\n", *uniq_int2);

        uniq_int1.swap(uniq_int2);

        ::fmt::print("uniq_int1 = {}\n", *uniq_int1);
        ::fmt::print("uniq_int2 = {}\n", *uniq_int2);
    }
    return 0;
}