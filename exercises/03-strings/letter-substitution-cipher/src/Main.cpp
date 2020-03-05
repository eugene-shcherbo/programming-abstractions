#include <iostream>
#include <string>
#include "console.h"
using namespace std;

constexpr int ALPHABET_LENGTH = 26;

string encode(string msg, string key);
string invertKey(string key);
void testEncode(string msg, string key, string expected);

int main() {
    setConsoleOutputColor("white");
    testEncode("WORKERS OF THE WORLD UNITE!", "QWERTYUIOPASDFGHJKLZXCVBNM", "VGKATKL GY ZIT VGKSR XFOZT!");
    testEncode("VGKATKL GY ZIT VGKSR XFOZT!", invertKey("QWERTYUIOPASDFGHJKLZXCVBNM"), "WORKERS OF THE WORLD UNITE!");
    return 0;
}

void testEncode(string msg, string key, string expected) {
    auto actual = encode(msg, key);
    cout << "Your message: " << msg << endl
         << "Encoded message: " << actual
         << endl
         << "RESULT: " << (actual == expected ? "SUCCESS." : "FAILED.")
         << endl;
}

string encode(string msg, string key) {
    string res{""};

    for (size_t i = 0; i < msg.length(); ++i) {
        auto letter = msg[i];
        if (isalpha(letter)) {
            res += key[(tolower(letter) - 'a')];
        } else {
            res += letter;
        }
    }

    return res;
}

string invertKey(string key) {
    auto res{""};

    for (size_t i = 0; i < key.length(); ++i) {
        auto alphabetChar = char('A' + i);
        auto keyIndex = key.find(alphabetChar);
        res += 'A' + keyIndex;
    }

    return res;
}
