#include <iostream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "vector.h"
using namespace std;

int main() {
    collections::Vector<int> ints1;
    assert(ints1.size() == 0);
    assert(ints1.isEmpty());

    collections::Vector<int> ints2(40);
    assert(ints2.size() == 40);
    assert(!ints2.isEmpty());
    for (int i = 0; i < 40; i++) {
        assert(ints2.get(i) == 0);
    }
    for (int i = 0; i < 20; i++) {
        ints2.set(i, i);
    }
    for (int i = 0; i < 20; i++) {
        ints2[i] = i;
    }
    for (int i = 0; i < 20; i++) {
        assert(ints2.get(i) == i);
    }
    for (int i = 0; i < 20; i++) {
        assert(ints2[i] == i);
    }

    for (int i = 0; i < 30; i += 2) {
        ints1.add(i);
    }
    assert(ints1.size() == 15);
    for (int i = 0; i < 15; i++) {
        assert(ints1.get(i) == i * 2);
    }
    for (int i = 1; i < 30; i += 2) {
        ints1.insert(i, i);
    }
    assert(ints1.size() == 30);
    for (int i = 0; i < 30; i++) {
        assert(ints1.get(i) == i);
    }

    for (int i = 29; i >= 1; i -= 2) {
        ints1.remove(i);
    }
    assert(ints1.size() == 15);
    for (int i = 0; i < 15; i++) {
        assert(ints1.get(i) == i * 2);
    }
    for (int i = 14; i >= 0; i--) {
        ints1.remove(i);
    }
    assert(ints1.size() == 0);
    assert(ints1.isEmpty());

    collections::Vector<int> copy = ints1;
    copy.add(15);
    assert(copy[0] == 15);
    assert(ints1.isEmpty());

    copy = ints1;
    copy.add(25);
    assert(copy[0] == 25);
    assert(ints1.isEmpty());

    cout << "All the tests are passes sucessfully.." << endl;

    return 0;
}
