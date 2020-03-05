#include <iostream>
#include "console.h"
#include "strlib.h"

using namespace std;

bool wildcardMatch(string filename, string pattern);
void test(const string& filename, const string& pattern, bool expected);
string cutStar(string filename, string pattern, int i);


int main() {
    test("US.txt", "*.*", true);
    test("test", "*.*", false);
    test("test.h", "test.?", true);
    test("test.cpp", "test.?", false);
    test("x", "??*", false);
    test("yy", "??*", true);
    test("zzz", "??*", true);
    test("he.llo", "??.???", true);
    test("he.ll", "??.??", true);
    test("he.lloooo", "??.??", false);
    test("baaabab", "*****ba*****ab", true);

    return 0;
}

bool wildcardMatch(string filename, string pattern) {
    if (filename.empty() && pattern.empty()) {
        return true;
    } else if (!pattern.empty()) {
        char s = pattern[0];

        if (s == '*') {
            filename = cutStar(filename, pattern, 0);
        } else if (filename.empty()) {
            return false;
        } else if (s == '?') {
            filename = filename.substr(1);
        } else if (filename[0] != s) {
            return false;
        } else {
            filename = filename.substr(1);
        }

        return wildcardMatch(filename, pattern.substr(1));
    }

    return false;
}

string cutStar(string filename, string pattern, int star) {
    char ch = '\0';

    for (int i = star; i < pattern.size(); i++) {
        if (pattern[i] != '*') {
            ch = pattern[i];
            break;
        }
    }

    if (ch == '\0') {
        return "";
    } else {
        int index = filename.find(ch, 0);

        if (index == string::npos) {
            return "";
        }

        return filename.substr(index);
    }
}

void test(const string& filename, const string& pattern, bool expected) {
    bool m = wildcardMatch(filename.c_str(), pattern.c_str());

    cout << filename << " and " << pattern
         << " == " << boolToString(m)
         << " (" << boolToString(expected) << ")" << endl;
}


