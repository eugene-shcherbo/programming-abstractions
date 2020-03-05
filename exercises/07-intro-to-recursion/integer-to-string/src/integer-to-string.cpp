#include <iostream>
#include "vector.h"
#include "console.h"

using namespace std;

namespace my {
    string integerToString(int n);
    char digitToChar(int digit);
}

void testIntegerToString(int n, const string& expected);

int main() {
    testIntegerToString(0, "0");
    testIntegerToString(5, "5");
    testIntegerToString(17, "17");
    testIntegerToString(154, "154");

    return 0;
}

void testIntegerToString(int n, const string& expected) {
    string actual = my::integerToString(n);
    cout << "Int " << n << " is " << actual << endl;
    cout << "Res: " << (actual == expected ? "success." : "failed.") << endl << endl;
}

/*
string my::integerToString(int n) {
    if (n < 10) {
        return string(1, '0' + n);
    } else {
        return my::integerToString(n / 10) + string(1, '0' + (n % 10));
    }
}
*/


string my::integerToString(int n) {
    if (n < 10) {
        return string(1, my::digitToChar(n));
    } else {
        return my::integerToString(n / 10) + my::digitToChar(n % 10);
    }
}

char my::digitToChar(int digit) {
    switch (digit) {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        default: throw digit;
    }
}


