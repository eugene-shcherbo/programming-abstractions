#include <iostream>
#include "point.h"

using namespace std;

string booleanToString(bool value) {
    return value ? "true" : "false";
}

int main()
{
    Point p1(10, 20);
    Point p2(10, 20);
    Point p3(5, 10);
    cout << "p1=" << p1 << endl;

    cout << "p1==p2 - " << booleanToString(p1 == p2) << endl;
    cout << "p1==p3 - " << booleanToString(p1 == p3) << endl;
    cout << "p1!=p3 - " << booleanToString(p1 != p3) << endl;

    return 0;
}
