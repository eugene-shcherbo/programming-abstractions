#include <iostream>
#include <string>
#include "io/simpio.h"
#include "console.h"
using namespace std;

constexpr int ALPHABET_LENGTH = 26;

string encodeCaesarCipher(string str, int shift);

int main() {
    setConsoleOutputColor("white");
    cout << "This program encodes a message using a Caesar cipher." << endl;

    int shift = getInteger("Enter the number of characters positions to shift: ");
    string message = getLine("Enter a message: ");

    cout << "Encoded message: " << encodeCaesarCipher(message, shift) << endl;
    return 0;
}

string encodeCaesarCipher(string str, int shift) {
    string res{""};

    if (shift < 0)
        shift = ALPHABET_LENGTH - abs(shift);

    for (int i = 0; i < str.length(); ++i) {
        auto ch = str[i];
        auto firstLetter = isupper(ch) ? 'A' : 'a';

        if (!isalpha(ch)) {
            res += ch;
        } else
            res += (firstLetter + (ch - firstLetter + shift) % ALPHABET_LENGTH);
    }

    return res;
}
