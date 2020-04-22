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

int main()
{
    // printTokens("hello world");
    // printTokens("hello world", false);
    testSaveToken();

    return 0;
}
