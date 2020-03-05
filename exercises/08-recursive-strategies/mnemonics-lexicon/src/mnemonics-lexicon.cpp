#include <iostream>
#include "console.h"
#include "strlib.h"
#include "vector.h"
#include "lexicon.h"
#include "set.h"

using namespace std;

void listMnemonics(string digits);
void mnemonicsHelper(const Vector<Set<char>>& keypad, const Lexicon& lexicon, string str, int index);

int main() {
    listMnemonics("7235");
    return 0;
}

void listMnemonics(string digits) {
    const static Vector<Set<char>> keypad
    {
        {}, // 0
        {}, // 1
        {'A', 'B', 'C'}, // 2
        {'D', 'E', 'F'}, // 3
        {'G', 'H', 'I'}, // 4
        {'J', 'K', 'L'}, // 5
        {'M', 'N', 'O'}, // 6
        {'P', 'Q', 'R', 'S'}, // 7
        {'T', 'U', 'V'}, // 8
        {'W', 'X', 'Y', 'Z'} // 9
    };

    Lexicon english("EnglishWords.dat");

    mnemonicsHelper(keypad, english, digits, 0);
}

void mnemonicsHelper(const Vector<Set<char>>& keypad, const Lexicon& lexicon, string str, int index) {
    if (index == str.length()) {
        if (lexicon.contains(str)) {
            cout << str << endl;
        }
    } else {
        int digit = charToInteger(str[index]);

        for (char ch: keypad[digit]) {
            str[index] = ch;
            mnemonicsHelper(keypad, lexicon, str, index + 1);
        }
    }
}
