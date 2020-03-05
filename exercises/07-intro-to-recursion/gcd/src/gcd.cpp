#include <iostream>
#include "console.h"

using namespace std;

int gcd(int x, int y);
void testGcd(int x, int y, int expected);

int main() {
    testGcd(9, 3, 3);
    testGcd(50, 20, 10);
    testGcd(35, 14, 7);

    return 0;
}

void testGcd(int x, int y, int expected) {
    int actual = gcd(x, y);
    cout << "gcd of " << x << " and " << y << " is " << actual << endl;
    cout << "result: " << (actual == expected ? "success." : "failed.")
         << endl << endl;
}

int gcd(int x, int y) {
    int r = x % y;
    if (r == 0) {
        return y;
    } else {
        return gcd(y, r);
    }
}
