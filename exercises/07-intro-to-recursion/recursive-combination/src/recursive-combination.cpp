#include <iostream>
#include "console.h"

using namespace std;

int combination(int n, int k);
void testCombination(int n, int k, int expected);

int main() {
    testCombination(0, 0, 1);
    testCombination(1, 0, 1);
    testCombination(1, 1, 1);
    testCombination(2, 1, 2);
    testCombination(3, 1, 3);
    testCombination(4, 2, 6);
    testCombination(5, 3, 10);
    testCombination(5, 4, 5);
    testCombination(6, 2, 15);

    return 0;
}

void testCombination(int n, int k, int expected) {
    int actual = combination(n, k);
    cout << "C(" << n << "," << k << ") is " << actual << endl;
    cout << "Result: " << (actual == expected ? "sucess." : "failed.") << endl << endl;
}

int combination(int n, int k) {
    if (n == 0 || k == 0 || k == n) {
        return 1;
    } else {
        return combination(n - 1, k - 1) + combination(n - 1, k);
    }
}
