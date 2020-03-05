#include <iostream>
using namespace std;

double sqrt(double n);

int main()
{
    int number;
    cout << "This program calculates square root of a number." << endl
         << "Type a number to calculate square root of this: ";
    cin >> number;

    cout << "square root of " << number << " is " << sqrt(number) << endl;

    return 0;
}

double sqrt(double n) {
    double g = n / 2;

    while (g != n/g) {
        g = (g + n/g) / 2;
    }

    return g;
}
