#include <iostream>
#include "console.h"
#include "strlib.h"

using namespace std;

bool wildcardMatch(string filename, string pattern);
void test(const string& filename, const string& pattern, bool expected);
bool matchHelper(string filename, string pattern, int nameIndex, int patternIndex);
bool matchAfterStar(string filename, string pattern, int nameIndex, int patternIndex);
bool notMatchSpecifically(string filename, string pattern, int nameIndex, int patternIndex);
bool isEmpty(string str, int idx);

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
    test("", "?", false);
    test(" ", "?", true);
    test(".", "..", false);

    return 0;
}

bool wildcardMatch(string filename, string pattern) {
    return matchHelper(filename, pattern, 0, 0);
}

bool matchHelper(string filename, string pattern, int nameIndex, int patternIndex) {
    if (isEmpty(pattern, patternIndex)) {
        return isEmpty(filename, nameIndex);
    } else if (pattern[patternIndex] == '*') {
        return matchAfterStar(filename, pattern, nameIndex, patternIndex);
    } else if (notMatchSpecifically(filename, pattern, nameIndex, patternIndex)) {
        return false;
    } else {
        return matchHelper(filename, pattern, nameIndex + 1, patternIndex + 1);
    }
}

bool isEmpty(string str, int idx) {
    return idx == str.size();
}


bool matchAfterStar(string filename, string pattern, int nameIndex, int patternIndex) {
    for (int i = nameIndex; i <= filename.size(); i++) {
        if (matchHelper(filename, pattern, i, patternIndex + 1)) {
            return true;
        }
    }

    return false;
}

bool notMatchSpecifically(string filename, string pattern, int nameIndex, int patternIndex) {
    return pattern[patternIndex] != '?' && pattern[patternIndex] != filename[nameIndex];
}

void test(const string& filename, const string& pattern, bool expected) {
    bool m = wildcardMatch(filename.c_str(), pattern.c_str());

    cout << filename << " and " << pattern
         << " == " << boolToString(m)
         << " (" << boolToString(expected) << ")" << endl;
}
