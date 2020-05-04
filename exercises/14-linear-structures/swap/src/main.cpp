#include <iostream>
#include <string>
#include "console.h"
using namespace std;

namespace utils {
    template <typename T>
    void swap(T& v1, T& v2);
}

int main() {
    int i1 = 1;
    int i2 = 10;
    utils::swap(i1, i2);
    cout << "i1=" << i1 << " and i2=" << i2 << endl;

    string s1 = "hello world";
    string s2 = "bye bye";
    utils::swap(s2, s1);
    cout << "s1=" << s1 << " and s2=" << s2 << endl;

    return 0;
}

namespace utils {
    template<typename T>
    void swap(T& v1, T& v2) {
        T tmp = v1;
        v1 = v2;
        v2 = tmp;
    }
}
