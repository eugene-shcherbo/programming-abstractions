#include <iostream>
#include "console.h"

using namespace std;

int raiseToPower(int base, int exp);
void testRaiseToPower(int base, int exp, int expected);

int main() {
    testRaiseToPower(0, 5, 0);
    testRaiseToPower(5, 0, 1);
    testRaiseToPower(1, 4, 1);
    testRaiseToPower(5, 2, 25);
    testRaiseToPower(3, 8, 6561);

    return 0;
}

void testRaiseToPower(int base, int exp, int expected) {
    int actual = raiseToPower(base, exp);
    cout << "pow(" << base << "," << exp << ") is " << actual << endl;
    cout << "result: " << (expected == actual ? "success." : "failed.")
         << endl << endl;
}

int raiseToPower(int base, int exp) {
    if (exp == 0) {
        return 1;
    } else {
        return base * raiseToPower(base, exp - 1);
    }
}
