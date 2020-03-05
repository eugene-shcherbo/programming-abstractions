#include <iostream>
#include <string>
#include "console.h"
using namespace std;

string addCommas(string digits);

int main() {
    setConsoleOutputColor("white");
    while (true) {
        string digits;
        cout << "Enter a number: ";
        getline(cin, digits);
        if (digits.empty())
            break;
        cout << addCommas(digits) << endl;
    }

    return 0;
}

string addCommas(string digits) {
    for (int i = digits.length() - 3; i > 0; i -= 3) {
        digits.insert(i, ",");
    }
    return digits;
}
