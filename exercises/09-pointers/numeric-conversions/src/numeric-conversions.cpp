#include <iostream>
#include "vector.h"
#include "strlib.h"
#include "console.h"

using namespace std;

namespace numeric {
    const string DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const size_t MAX_BASE = DIGITS.size();
    const int MIN_BASE = 2;

    string integerToString(int val, int base);
    int stringToInteger(string val, int base);
}

void test(int val, int base, string expected);
void test(string val, int base, int expected);

int main() {
    test(42, 16, "2A");
    test(-42, 16, "-2A");
    test("111111", 2, 63);
    test("-111111", 2, -63);
    test("2A", 16, 42);
    test("-2A", 16, -42);

    return 0;
}

void test(int val, int base, string expected) {
    string actual = numeric::integerToString(val, base);

    cout << val << " in " << base << " base is " << actual << endl;
    cout << (actual == expected ? "Sucess" : "Failed. Should be " + expected) << endl << endl;
}


void test(string val, int base, int expected) {
    int actual = numeric::stringToInteger(val, base);

    cout << val << " in " << base << " base is " << actual << endl;
    cout << (actual == expected ? "Sucess" : "Failed. Should be " + numeric::integerToString(expected, 10)) << endl << endl;

}

string numeric::integerToString(int val, int base) {
    if (base < MIN_BASE || static_cast<size_t>(base) > MAX_BASE) throw "base must be between 2 and 36";

    int quotient = abs(val);
    string res;

    while (quotient > 0) {
        res = DIGITS[static_cast<size_t>(quotient % base)] + res;
        quotient /= base;
    }

    return val >= 0 ? res : "-" + res;
}


int numeric::stringToInteger(string val, int base) {
    int res = 0;
    int pos = 0;

    for (int i = val.size() - 1; i >= 0; i--) {
        char digit = toUpperCase(val[i]);
        int num = 0;

        if (i == 0 && val[i] == '-') {
            res = -res;
        } else if (isalpha(digit)) {
            num = digit - 'A' + 10;
        } else if (isdigit(digit)) {
            num = digit - '0';
        } else {
            throw "stringToInteger: out of range";
        }

        if (num >= base) throw "stringToInteger: invalid input for specified base.";

        res += num * static_cast<int>(pow(base, pos));
        pos++;
    }

    return res;
}

