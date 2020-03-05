#include <iostream>
#include "console.h"
using namespace std;

/**
 * Function: isPalindrome
 * ----------------------
 * Returns true if str is a palindrome, which is a string that
 * read the same backwards and forwards. This implementation
 * uses the recursive insight that all strings of length 0 or 1
 * are palindromes and that longer strings are palindromes if
 * their first and last character match and the remaining substring
 * is a palindrome.
 */
bool isPalindrome(string str) {
    int len = str.length();
    if (len < 2) {
        return true;
    } else {
        return str[0] == str[len - 1] && isPalindrome(str.substr(1, len - 2));
    }
}

int main() {
    return 0;
}
