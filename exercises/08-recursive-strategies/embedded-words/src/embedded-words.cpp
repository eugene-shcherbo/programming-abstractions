#include <iostream>
#include "console.h"
#include "set.h"
#include "lexicon.h"
#include "simpio.h"

using namespace std;

Set<string> findEmbededWords(const Lexicon& english, const string& original);
Set<string> subStrings(const string& str);

int main() {
    Lexicon english("EnglishWords.dat");

    string str = getLine("Enter a string: ");
    cout << "The embedded words of\"" << str << "\" are:" << endl;

    for (string s: findEmbededWords(english, str)) {
        cout << "  \"" << s << "\"" << endl;
    }

    return 0;
}

Set<string> findEmbededWords(const Lexicon& english, const string& original) {
    Set<string> res;

    for (string s: subStrings(original)) {
        if (english.contains(s)) {
            res += s;
        }
    }

    return res;
}

Set<string> subStrings(const string& str) {
    Set<string> res;

    if (!str.empty()) {
        string rest = str.substr(1);

        res += string(1, str[0]);
        res += subStrings(rest);

        for (string s: subStrings(rest)) {
            res += str[0] + s;
        }
    }

    return res;
}
