#include <iostream>
#include <iomanip>
#include <cmath>
#include "console.h"
using namespace std;

constexpr double PI = 3.1415926;

/* Function prototypes */

void printTrigonometrticTable();
double radians(double degree);

/* Main program */

int main() {
    setConsoleOutputColor("white");
    printTrigonometrticTable();
    return 0;
}

void printTrigonometrticTable() {
    cout << right << fixed << setprecision(7);
    cout << "   theta   | sin(theta) | cos(theta) |" << endl;
    cout << "-----------+------------+------------+" << endl;

    for (int i = -90; i < 100; i += 10) {
        cout << setw(8) << i << "   |";
        cout << setw(11) << sin(radians(i)) << " |";
        cout << setw(11) << cos(radians(i)) << " |" << endl;
    }
}

double radians(double degrees) {
    return degrees * PI / 180;
}
