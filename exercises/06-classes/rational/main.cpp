#include <iostream>
#include "rational.h"

using namespace std;

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

    return 0;
}
