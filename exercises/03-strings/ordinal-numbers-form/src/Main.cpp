#include <iostream>
#include <string>
#include "console.h"
using namespace std;

// 103rd
// 102nd
// 101st

string createOrdinalForm(int n);
string convertToString(int n);
char convertDigitToChar(int n);
string getOrdinalSuffix(int n);
int getTwoLastDigits(int n);
void testCreateOrdinalForm(int n, string expected);

int main() {
    setConsoleOutputColor("white");
    testCreateOrdinalForm(1, "1st");
    testCreateOrdinalForm(2, "2nd");
    testCreateOrdinalForm(3, "3rd");
    testCreateOrdinalForm(4, "4th");
    testCreateOrdinalForm(10, "10th");
    testCreateOrdinalForm(11, "11th");
    testCreateOrdinalForm(12, "12th");
    testCreateOrdinalForm(13, "13th");
    testCreateOrdinalForm(21, "21st");
    testCreateOrdinalForm(22, "22nd");
    testCreateOrdinalForm(100, "100th");
    testCreateOrdinalForm(101, "101st");
    testCreateOrdinalForm(102, "102nd");
    testCreateOrdinalForm(103, "103rd");
    testCreateOrdinalForm(113, "113th");
    testCreateOrdinalForm(114, "114th");
    testCreateOrdinalForm(147, "147th");

    return 0;
}

void testCreateOrdinalForm(int n, string expected) {
    auto actual = createOrdinalForm(n);
    cout << "Ordinal for " << n << " is " << actual
         << ". " << (actual == expected ? "SUCCESS!" : "FAILED") << endl;
}

string createOrdinalForm(int n) {
    auto numberStr = convertToString(n);
    auto suffix = getOrdinalSuffix(n);
    return numberStr + suffix;
}

string convertToString(int n) {
    string res{""};
    while (n > 0) {
        auto remainder = n % 10;
        res.insert(0, string(1, convertDigitToChar(remainder)));
        n /= 10;
    }
    return res;
}

// also possible to convert using char(n + '0')
char convertDigitToChar(int n) {
    switch (n) {
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        default:
            return '0';
    }
}

string getOrdinalSuffix(int n) {
    auto lastDigits = getTwoLastDigits(n);

    switch (lastDigits) {
        case 11:
        case 12:
        case 13:
            return "th";
        case 3:
            return "rd";
        case 2:
            return "nd";
        case 1:
            return "st";
        default:
            return "th";
    }
}

int getTwoLastDigits(int n) {
    auto twoLast = n % 100;
    // it's neccessary to have two digits only if the number ends with 11, 12, or 13.
    return twoLast > 13 ? twoLast % 10 : twoLast;
}
