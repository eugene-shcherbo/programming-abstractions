#include <iostream>
#include "console.h"
#include "strlib.h"
#include "vector.h"
#include "set.h"

using namespace std;

void listMnemonics(string digits);
void mnemonicsHelper(string str, int index);

const static Vector<Set<char>> KEYPAD
{
    {}, // 0
    {}, // 1
    {'A', 'B', 'C'}, // 2,
    {'D', 'E', 'F'}, // 3,
    {'G', 'H', 'I'}, // 4
    {'J', 'K', 'L'}, // 5,
    {'M', 'N', 'O'}, // 6
    {'P', 'Q', 'R', 'S'}, // 7
    {'T', 'U', 'V'}, // 8
    {'W', 'X', 'Y', 'Z'} // 9
};

int main() {
    listMnemonics("7235");
    return 0;
}

void listMnemonics(string digits) {
    mnemonicsHelper(digits, 0);
}

void mnemonicsHelper(string str, int index) {
    if (index == str.length()) {
        cout << str << endl;
    } else {
        int digit = charToInteger(str[index]);

        for (char ch: KEYPAD[digit]) {
            str[index] = ch;
            mnemonicsHelper(str, index + 1);
        }
    }
}
