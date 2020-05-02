#include <iostream>
#include "console.h"
#include "intarray.h"
using namespace std;

int main() {
    IntArray empty(0);
    assert(empty.size() == 0);

    IntArray zeros(10);
    assert(zeros.size() == 10);

    for (uint i = 0; i < zeros.size(); i++) {
        assert(zeros.get(i) == 0);
    }

    IntArray index(10);
    for (uint i = 0; i < index.size(); i++) {
        index.put(i, static_cast<int>(i));
    }
    for (uint i = 0; i < index.size(); i++) {
        assert(index.get(i) == static_cast<int>(i));
    }
    index[4] = 100500;
    assert(index[4] == 100500);
    assert(index.get(4) == 100500);
    index[4] = 3;

    IntArray copy1 = index;
    copy1[0] = 15;
    assert(copy1[0] == 15);
    assert(index[0] != 15);

    copy1 = index;
    copy1[0] = 15;
    assert(copy1[0] == 15);
    assert(index[0] != 15);

    return 0;
}
