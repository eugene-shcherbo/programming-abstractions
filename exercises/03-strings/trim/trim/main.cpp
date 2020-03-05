//
//  main.cpp
//  trim
//
//  Created by Eugene Shcherbo on 9/29/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string trim(const string& str);
void testTrim(const string& original);
int findFirstAlphaNum(const string& str);
int findLastAlphaNum(const string& str);

int main(int argc, const char * argv[]) {
    testTrim("     Hello World    ");
    testTrim("\n\r\tHello World\t\n\r");
    testTrim("\n\r\t\t\n\r");
    
    return 0;
}

void testTrim(string original) {
    cout << "Trimm of a string " << original
        << " is " << trim(original) << endl;
}

string trim(const string& str) {
    int startIndex = findFirstAlphaNum(str);
    int lastIndex = findLastAlphaNum(str);
    
    if (startIndex == -1 || lastIndex == -1) return "";
    
    return str.substr(startIndex, lastIndex - startIndex + 1);
}

int findFirstAlphaNum(const string& str) {
    for (int i = 0; i < str.length(); ++i) {
        if (!iswspace(str[i])) return i;
    }
    return -1;
}

int findLastAlphaNum(const string& str) {
    for (size_t i = str.length() - 1; i >= 0; --i) {
        if (!iswspace(str[i])) return static_cast<int>(i);
    }
    return -1;
}
