
/*
 * File: Main.cpp
 * -----------------------
 * This program simulates an electronic calculator that uses
 * reverse Polish notation, in which operators come after
 * the operands to which they apply. Information for users
 * of this application appears in the helpCommand function.
 */

#include <iostream>
#include <fstream>
#include <cctype>
#include "stack.h"
#include "console.h"
#include "strlib.h"
#include "tokenscanner.h"
#include "lexicon.h"
#include "filelib.h"

using namespace std;

int main() {
    ifstream infile;
    promptUserForFile(infile, "Input file: ");

    Lexicon english("EnglishWords.dat");
    TokenScanner scanner(infile);
    scanner.ignoreWhitespace();

    while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        if (isalpha(token[0]) && !english.contains(token)) {
            cout << "\"" << token << "\" is not in the dictionary" << endl;
        }
    }

    return 0;
}
