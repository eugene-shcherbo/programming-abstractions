#include <iostream>
#include "console.h"
#include "lexicon.h"

using namespace std;

void printPalindromes(const Lexicon& english);
bool isPalindrome(const string& str);

int main() {
    Lexicon english("EnglishWords.dat");

    printPalindromes(english);

    return 0;
}

void printPalindromes(const Lexicon& english) {
    for (string word: english) {
        if (isPalindrome(word)) {
            cout << word << endl;
        }
    }
}

bool isPalindrome(const string& str) {
    int n = str.length();

    for (int i = 0; i < n / 2; ++i) {
        if (str[i] != str[n - 1 - i]) {
            return false;
        }
    }

    return true;
}
