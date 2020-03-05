//
//  main.cpp
//  palindrome
//
//  Created by Eugene Shcherbo on 9/28/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(string str);
void testPalindrome();
void assertTrue(bool value);
void assertFalse(bool value);

int main(int argc, const char * argv[]) {
    // insert code here...
    testPalindrome();
    return 0;
}

void testPalindrome() {
    assertTrue(isPalindrome("level"));
    assertTrue(isPalindrome("mum"));
    assertFalse(isPalindrome("xyz"));
}

bool isPalindrome(string str) {
    size_t n = str.length();
    for (int i = 0; i < n / 2; ++i) {
        if (str[i] != str[n - i - 1]) return false;
    }
    return true;
}

void assertTrue(bool value) {
    cout << (value ? "SUCCESS: true" : "FAILED: false") << endl;
}

void assertFalse(bool value) {
    cout << (value ? "FAILED: true" : "SUCCESS: false") << endl;
}
