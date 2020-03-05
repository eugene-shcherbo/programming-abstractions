/*
 * File: main.cpp
 * --------------
 * This program adds a list of integers. The end of the
 * input is indicating by entering a sentitel value, which
 * is defined by setting the value of the constant SENTITEL.
 */

#include <iostream>
using namespace std;

/*
 * Constant: SENTITEL
 * ------------------
 * This constant defines the value used to terminate the input
 * list and should therefore not be a value one would want to
 * include as a data value. The value 0 therefore makes sense
 * for a program that adds a series of numbers because the
 * use can simply skip any 0 values in the input.
 */

constexpr int SENTITEL = 0;

/* Main Program */

int main()
{
    cout << "This program adds a list of numbers." << endl;
    cout << "Use " << SENTITEL << " to signal the end." << endl;

    int total = 0;
    while (true) {
        int value;
        cout << " ? ";
        cin >> value;
        if (value == SENTITEL) break;
        total += value;
    }
    cout << "The total is " << total << endl;

    return 0;
}
