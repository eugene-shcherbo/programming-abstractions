#include <iostream>
#include "console.h"

using namespace std;

string reverse(string str);
void testReverse(string str, const string& expected);

int main() {
    testReverse("program", "margorp");
    testReverse("hello", "olleh");

    return 0;
}

void testReverse(string str, const string& expected) {
    auto actual = reverse(str);
    cout << "Reverse of " << str << " is " << actual << endl;
    cout << "Result: " << (actual == expected ? "sucess." : "failed.") << endl << endl;
}

string reverseHelper(string str, int start, int end) {
    if (start >= end) {
        return str;
    } else {
       char tmp = str[start];
       str[start] = str[end];
       str[end] = tmp;
       return reverseHelper(str, start + 1, end - 1);
    }
}

string reverse(string str) {
    return reverseHelper(str, 0, str.length() - 1);
}

/*
string reverse(string str) {
    if (len <= 1) {
        return str;
    } else {
        return str[str.length() - 1] + reverse(str.substr(0, str.lenght() - 1));
    }
}
 */


