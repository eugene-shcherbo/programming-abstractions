#include <iostream>
#include <string>
#include "console.h"
using namespace std;

string removeDoubleLetters(string str);

int main() {
    string str;
    cout << "This program removes double letters from a string" << endl
         << "Enter a string: ";
    getline(cin, str);

    cout << "The result is " << removeDoubleLetters(str) << endl;

    return 0;
}

string removeDoubleLetters(string str) {
    for (size_t i = 1; i < str.length(); ++i) {
        if (str.at(i) == str.at(i - 1)) {
            str.erase(i, 1);
        }
    }

    return str;
}
