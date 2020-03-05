//
//  main.cpp
//  ends-with
//
//  Created by Eugene Shcherbo on 9/29/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

#include <iostream>
#include <cctype>
#include <string>
using namespace std;

bool endsWith(string str, char suffix);
bool endsWith(string str, string suffix);
void testEndsWith();
void displayTestResult(string str, string suffix, bool result);

int main(int argc, const char * argv[]) {
    testEndsWith();
    return 0;
}

void testEndsWith() {
    bool result = endsWith("Hello World", 'd');
    
    if (result) {
        cout << "SUCCSS: Hello World ends with d" << endl;
    } else {
        cout << "FAILED: Hello World ENDS with d" << endl;
    }
    
    result = endsWith("Hello World", "orld");
    
    if (result) {
        cout << "SUCCESS: Hello World ends with orld" << endl;
    } else {
        cout << "SUCCESS: Hello World ENDS with orld" << endl;
    }
    
    result = endsWith("Hello World", "ord");
    
    if (result) {
        cout << "FAILED: Hello world DOESN'T end with ord" << endl;
    } else {
        cout << "SUCCESS: Hello world doesn't end with ord" << endl;
    }
}

bool endsWith(string str, string suffix) {
    if (suffix.length() > str.length()) return false;
    size_t n = str.length();
    for (int i = 0; i < suffix.length(); ++i) {
        if (tolower(str[n - 1 - i]) != tolower(suffix[i])) return false;
    }
    return true;
}

bool endsWith(string str, char suffix) {
    return endsWith(str, string(1, suffix));
}
