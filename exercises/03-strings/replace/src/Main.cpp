#include <iostream>
#include <string>
#include "console.h"
using namespace std;

string replaceAll(string str, char c1, char c2);
string replaceAll(string str, string s1, string s2);
void testReplaceAll();
void designTestCase(string testCase, char c1, char c2);
void designTestCase(string testCase, string s1, string s2);

int main() {
    testReplaceAll();
    return 0;
}

void testReplaceAll() {
    designTestCase("nannies", 'n', 'd');
    designTestCase("Hello World, my friend!", 'r', 'R');
    designTestCase("who is on duty today?", 'o', ' ');
    designTestCase("who is on duty today? tod", "tod", "OOOOH");
    designTestCase("who is on duty today?", "tod", "M");
}

void designTestCase(string testCase, char c1, char c2) {
    cout << "Original: " << testCase << ". Replaced: " << replaceAll(testCase, c1, c2)
         << endl;
}

void designTestCase(string testCase, string s1, string s2) {
    cout << "Original: " << testCase << ". Replaced: " << replaceAll(testCase, s1, s2)
         << endl;
}

string replaceAll(string str, char c1, char c2) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == c1)
            str[i] = c2;
    }
    return str;
}

string replaceAll(string str, string s1, string s2) {
    while (true) {
        auto s1Index = str.find(s1);

        if (s1Index == str.npos)
            break;

        str.replace(s1Index, s1.length(), s2);
    }

    return str;
}
