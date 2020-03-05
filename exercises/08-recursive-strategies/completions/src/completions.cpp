#include <iostream>
#include "console.h"
#include "strlib.h"
#include "vector.h"
#include "lexicon.h"
#include "set.h"

using namespace std;

void listCompletions(const string& str, const Lexicon& lex);
void completionsHelper(const string& mnemonic, const Lexicon& lex);
void formMnemonics(const string& digits, const string& mnemonic, const Vector<string>& keypad, int index, Set<string>& mnemonics);


int main() {
    Lexicon english("EnglishWords.dat");
    listCompletions("72547", english);

    return 0;
}

void listCompletions(const string& digits, const Lexicon& lex) {
    Vector<string> keypad
    {
        "",
        "",
        "ABC", "DEF",
        "GHI", "JKL", "MNO",
        "PQRS", "TUV", "WXYZ"
    };

    Set<string> mnemonics;
    formMnemonics(digits, "", keypad, 0, mnemonics);

    for (string mn: mnemonics) {
        completionsHelper(mn, lex);
    }
}

void formMnemonics(const string& digits, const string& mnemonic, const Vector<string>& keypad, int index, Set<string>& mnemonics) {
    if (index == digits.length()) {
        mnemonics.add(toLowerCase(mnemonic));
    } else {
        auto letters = keypad[charToInteger(digits[index])];
        for (char letter: letters) {
            formMnemonics(digits, mnemonic + letter, keypad, index + 1, mnemonics);
        }
    }}

void completionsHelper(const string& word, const Lexicon& lex) {
    if (lex.contains(word)) {
        cout << word << endl;
    }

    for (char ch = 'a'; ch < 'z'; ++ch) {
        string extWord = word + ch;
        if (lex.containsPrefix(extWord)) {
            completionsHelper(extWord, lex);
        }
    }
}
