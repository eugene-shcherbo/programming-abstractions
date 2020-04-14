#include <iostream>
#include "rational.h"

using namespace std;

string boolToString(bool val) {
    return val ? "true" : "false";
}

void incrementDecrementTest() {
    Rational r1(1, 3);

    cout << "---- Inc. Dec operators----" << endl;
    cout << r1 << "++ == " << r1++ << endl; // 1/3
    cout << "++" << r1 << " == " << ++r1 << endl; // 7/3
    cout << "--" << r1 << " == " << --r1 << endl; // 4/3
    cout << r1 << "--" << " == " << r1-- << endl; // 4/3
}

void relationOperators() {
    Rational r1(1, 3);
    Rational r2(2, 6);
    Rational r3(1, 5);
    Rational r4(7, 5);

    cout << "---- Relations operators----" << endl;
    cout << r1 << " == " << r2 << " " << boolToString(r1 == r1) << endl;
    cout << r1 << " > " << r2 << " " << boolToString(r1 > r2) << endl;
    cout << r1 << " >= " << r2 << " " << boolToString(r1 >= r2) << endl;
    cout << r1 << " > " << r3 << " " << boolToString(r1 > r3) << endl;
    cout << r3 << " < " << r4 << " " << boolToString(r3 < r4) << endl;
    cout << r4 << " <= " << r3 << " " << boolToString(r4 <= r3) << endl;
}

int main()
{
    Rational zero;
    Rational num(5);
    Rational num2(10, 2);
    Rational frac(2, 6);
    Rational frac2(1, 3);

    cout << zero << endl;
    cout << num << endl;
    cout << num2 << endl;
    cout << frac << endl;
    cout << frac2 << endl;

    cout << frac << " + " << num << " = " << frac + num2 << endl;
    cout << frac << " * " << num << " = " << frac * num2 << endl;
    cout << frac << " / " << num << " = " << frac / num2 << endl;
    cout << frac << " - " << num << " = " << frac - num2 << endl;

    relationOperators();
    incrementDecrementTest();

    return 0;
}
