#include <iostream>
#include <string>
#include "console.h"
#include "pair.h"
using namespace std;

template <typename T1, typename T2>
void printPair(const Pair<T1,T2>& p) {
    cout << "pair.first()=" << p.first() << " and pair.second()=" << p.second() << endl;
}

int main() {
    Pair<int, string> pair;
    printPair(pair);

    Pair<string, int> id("I'm ", 25);
    printPair(id);

    return 0;
}
