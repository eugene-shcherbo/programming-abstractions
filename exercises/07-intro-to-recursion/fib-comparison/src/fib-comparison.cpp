#include <iostream>
#include <iomanip>
#include "console.h"

using namespace std;

int countFib1(int n, int& count);
int countFib2(int n, int& count);
int additiveSequence(int v1, int v2, int n, int& count);

int main() {
    constexpr int n = 12;

    cout << right << setw(4) << "n" << setw(8) << "fib1" << setw(8) << "fib2" << endl;
    cout << setw(4) << "--" << setw(8) << "----" << setw(8) << "----" << endl;

    for (int i = 0; i < n; ++i) {
        int count1 = 0;
        int count2 = 0;
        countFib1(i, count1);
        countFib2(i, count2);

        cout << setw(4) << i << setw(8) << count1 << setw(8) << count2 << endl;
    }

    return 0;
}

int countFib1(int n, int& count) {
    ++count;
    if (n < 2) {
        return n;
    } else {
        return countFib1(n - 1, count) + countFib1(n - 2, count);
    }
}

int countFib2(int n, int& count) {
    ++count;
    return additiveSequence(0, 1, n, count);
}

int additiveSequence(int v1, int v2, int n, int& count) {
    ++count;

    if (n == 0) {
        return v1;
    } else if (n == 1) {
        return v2;
    } else {
        return additiveSequence(v2, v1 + v2, n - 1, count);
    }
}
