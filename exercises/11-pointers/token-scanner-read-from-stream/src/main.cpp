#include <iostream>
#include "console.h"
#include "tokenscanner.h"

using namespace std;

void printTokens(const string str, bool whitespaces = true) {
    text::TokenScanner scanner(str);

    if (!whitespaces) {
        scanner.ignoreWhiteSpaces();
    }

    while (scanner.hasMoreTokens()) {
        cout << scanner.nextToken() << endl;
    }
}

void testSaveToken() {
    cout << "---Save Token Testing---" << endl;

    text::TokenScanner ts;
    ts.ignoreWhiteSpaces();
    ts.saveToken("hello world");
    ts.saveToken("bye bye");

    while (ts.hasMoreTokens()) {
        cout << "token = " << ts.nextToken() << endl;
    }
}

void testScanString() {
    cout << "---Scan String Testing---" << endl;

    text::TokenScanner ts;
    ts.ignoreWhiteSpaces();
    ts.scanString();
    ts.setSource("hello world \"string literal ' ends here\" and another 'string literal is over \" here'");

    while (ts.hasMoreTokens()) {
        cout << "token = " << ts.nextToken() << endl;
    }
}

void testScanNumbers() {
    cout << "---Scan Numbers Testing---" << endl;

    text::TokenScanner ts;
    ts.ignoreWhiteSpaces();
    ts.scanString();
    ts.scanNumbers();
    ts.setSource("hello world 3.0E-9word54");

    while (ts.hasMoreTokens()) {
        cout << "token = " << ts.nextToken() << endl;
    }
}

int main() {
    printTokens("hello world");
    printTokens("hello world", false);
    testSaveToken();
    testScanString();
    testScanNumbers();

    return 0;
}
