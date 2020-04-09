#include <iostream>
#include "tokenscanner.h"

using namespace std;

void printTokens(const string str, bool whitespaces = true) {
    TokenScanner scanner(str);

    if (!whitespaces) {
        scanner.ignoreWhiteSpaces();
    }

    while (scanner.hasMoreTokens()) {
        cout << scanner.nextToken() << endl;
    }
}

int main()
{
    printTokens("hello world");
    printTokens("hello world", false);

    return 0;
}
