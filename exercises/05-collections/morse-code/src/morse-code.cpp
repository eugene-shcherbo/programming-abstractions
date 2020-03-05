#include <iostream>
#include <cctype>
#include "map.h"
#include "simpio.h"
#include "console.h"

using namespace std;

string encode(const string& msg);
string decode(const string& morse);
bool isMorse(const string& msg);

const Map<char, string> MORSE_CODE = {
    {'A', ".-"}, {'H', "...."}, {'O', "---"}, {'V', "...-"},
    {'B', "-..."}, {'I', ".."}, {'P', ".--."}, {'W', ".--"},
    {'C', "-.-."}, {'J', ".---"}, {'Q', "--.-"}, {'X', "-..-"},
    {'D', "-.."}, {'K', "-.-"}, {'R', ".-."}, {'Y', "-.--"},
    {'E', "."}, {'L', ".-.."}, {'S', "..."}, {'Z', "--.."},
    {'F', "..-."}, {'M', "--"}, {'T', "-"},
    {'G', "--."}, {'N', "-."}, {'U', "..-"}
};

const Map<string, char> REVERSE_MORSE_CODE = {
    {".-", 'A'}, {"....", 'H'}, {"---", 'O'}, {"...-", 'V'},
    {"-...", 'B'}, {"..", 'I'}, {".--.", 'P'}, {".--", 'W'},
    {"-.-.", 'C'}, {".---", 'J'}, {"--.-", 'Q'}, {"-..-", 'X'},
    {"-..", 'D'}, {"-.-", 'K'}, {".-.", 'R'}, {"-.--", 'Y'},
    {".", 'E'}, {".-..", 'L'}, {"...", 'S'}, {"--..", 'Z'},
    {"..-.", 'F'}, {"--", 'M'}, {"-", 'T'},
    {"--.", 'G'}, {"-.", 'N'}, {"..-", 'U'}
};

int main() {
    cout << "Morse code translator" << endl;

    while (true) {
        string msg = getLine("> ");

        if (msg.empty()) {
            break;
        }

        string encoded = isMorse(msg) ? decode(msg) : encode(msg);

        cout << encoded << endl;
    }

    return 0;
}

bool isMorse(const string& msg) {
    return msg.size() > 0
            && (msg[0] == '.' || msg[0] == '-');
}

string encode(const string& msg) {
    string res;

    for (char ch: msg) {
        if (MORSE_CODE.containsKey(ch)) {
            res += MORSE_CODE[ch] + ' ';
        }
    }

    return res;
}

string decode(const string& morse) {
    string res;
    string letter;

    for (char ch: morse) {
        if (isspace(ch) && REVERSE_MORSE_CODE.containsKey(letter)) {
            res += REVERSE_MORSE_CODE[letter];
            letter = "";
        } else {
            letter += ch;
        }
    }

    if (REVERSE_MORSE_CODE.containsKey(letter)) {
        res += REVERSE_MORSE_CODE[letter];
    }

    return res;
}


