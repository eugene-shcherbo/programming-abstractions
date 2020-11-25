#include <iostream>
#include "console.h"

using namespace std;

double raiseToPower(double x, int n);

void anyNumInZeroPowerIs1();
void correctRaiseToPower();

int main() {
    anyNumInZeroPowerIs1();
    correctRaiseToPower();

    return 0;
}

double raiseToEvenPower(double x, int n) {
    if (n == 0) return 1;
    if (n == 1) return x;

    double halfPower = raiseToEvenPower(x, n / 2);
    return halfPower * halfPower;
}

double raiseToPower(double x, int n) {
    if (n % 2 == 0) {
        return raiseToEvenPower(x, n);
    } else {
        return x * raiseToEvenPower(x, n - 1);
    }
}

void anyNumInZeroPowerIs1() {
    assert(raiseToPower(0, 0) == 1);
    assert(raiseToPower(1, 0) == 1);
    assert(raiseToPower(10, 0) == 1);
    assert(raiseToPower(100500, 0) == 1);
}

void correctRaiseToPower() {
    assert(raiseToPower(2, 2) == 4);
    assert(raiseToPower(2, 3) == 8);
    assert(raiseToPower(10, 3) == 1000);
    assert(raiseToPower(0.5, 3) == 0.125);
    assert(raiseToPower(2, 5) == 32);
}

