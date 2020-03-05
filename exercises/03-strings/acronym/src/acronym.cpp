#include <iostream>
#include <string>
#include <cctype>
#include "console.h"
using namespace std;

string acronym(string original);
bool isWordBeginning(int index, string str);

int main() {
    string str;
    cout << "This program convert the original string into its acronym." << endl
       << "Enter some string: ";

    getline(cin, str);

    cout << "Acronym is " << acronym(str) << endl
         << "That's it..." << endl;

    return 0;
}

string acronym(string original) {
    string result{""};

    for (int i = 0; i < original.length(); ++i) {
        char ch = original.at(i);
        if (isWordBeginning(i, original)) {
            result += ch;
        }
    }

    return result;
}

bool isWordBeginning(int index, string str) {
    index = index < 0 ? 0 : index;
    char ch = str.at(index);
    return (index == 0 && isalpha(ch))
            || (isalpha(ch) && !isalpha(str.at(index - 1)));
}


