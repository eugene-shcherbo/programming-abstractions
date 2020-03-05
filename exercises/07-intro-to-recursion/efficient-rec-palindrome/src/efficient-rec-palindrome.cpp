#include <iostream>
#include "console.h"
using namespace std;

/**
 * Function: isSubstringPalindrome
 * -------------------------------
 * Returns true if the characters in str from p1 to p2 inclusive form
 * a palindrome. This implementation uses the recursive insight that
 * all strings of length 0 or 1 are palindromes (the base case) and
 * that longer strings are palindromes only if their first and last
 * characters match and the remaining substring is a palindrome.
 */
bool isSubstringPalindrome(const string& str, int p1, int p2);

/**
 * Function: isPalindrome
 * ----------------------
 * Returns true if str is a palindrome, which is a string that reads the
 * same backwards and forwards. This level of the implementation is
 * simply a wrapper for isSubstringPalindrome, which does the real work.
 */
bool isPalindrome(const string& str);

int main() {
    return 0;
}

bool isPalindrome(const string& str) {
    return isSubstringPalindrome(str, 0, str.length() - 1);
}

bool isSubstringPalindrome(const string& str, int p1, int p2) {
    if (p1 >= p2) {
        return true;
    } else {
        return str[p1] == str[p2] && isSubstringPalindrome(str, p1 + 1, p2 - 1);
    }
}
