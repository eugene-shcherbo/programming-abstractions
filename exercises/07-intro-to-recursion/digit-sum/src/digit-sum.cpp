#include <iostream>
#include "console.h"

using namespace std;

int digitSum(int n);
void testDigitSum(int n, int expected);

int main() {
    testDigitSum(1729, 19);
    testDigitSum(138, 12);
    testDigitSum(5, 5);
    testDigitSum(12, 3);

    return 0;
}

void testDigitSum(int n, int expected) {
    int actual = digitSum(n);

    cout << "Digit sum of " << n << " is " << actual << endl;
    cout << "Result: " << (actual == expected ? "success." : "failed.") << endl << endl;
}

int digitSum(int n) {
    if (n < 10) {
        return n;
    } else {
        return digitSum(n / 10) + (n % 10);
    }
}
