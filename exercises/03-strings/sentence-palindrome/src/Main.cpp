#include <iostream>
#include <string>
#include <cctype>
#include "console.h"
using namespace std;

bool isSentencePalindrome(string str);

int main() {
    setConsoleOutputColor("white");

    cout << "This program tests for sentence palindromes. "
         << "Indicate the end of the input with a blank line. ";

    string sentence;

    while (true) {
         cout <<  "Enter a sentence: ";
         getline(cin, sentence);

         if (sentence.empty())
             break;

         cout << "That sentence is " << (isSentencePalindrome(sentence) ? "" : "not ")
              << "a palindrome."
              << endl;
    }

    return 0;
}

bool isSentencePalindrome(string str) {
    size_t left = 0;
    auto right = str.length() - 1;

    while (left < right) {
        char leftCh = tolower(str[left]);
        char rightCh = tolower(str[right]);

        if (!isalnum(leftCh)) {
            ++left;
            continue;
        }

        if (!isalnum(rightCh)) {
            --right;
            continue;
        }

        if (leftCh != rightCh) {
            return false;
        }

        ++left;
        --right;
    }

    return true;
}
