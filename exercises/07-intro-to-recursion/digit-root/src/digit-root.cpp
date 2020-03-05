#include <iostream>
#include "console.h"

using namespace std;

int digitRoot(int n);
int digitSum(int n);
void testDigitRoot(int n, int expected);

int main() {
    testDigitRoot(19, 1);
    testDigitRoot(358, 7);
    testDigitRoot(2, 2);
    testDigitRoot(12, 3);

    return 0;
}

void testDigitRoot(int n, int expected) {
    int actual = digitRoot(n);
    cout << "Digital root of " << n << " is " << actual << endl;
    cout << "Result: " << (expected == actual ? "success." : "failed.") << endl << endl;
}

int digitRoot(int n) {
    if (n < 10) {
        return n;
    } else {
        return digitRoot(n / 10 + n % 10);
    }
}
