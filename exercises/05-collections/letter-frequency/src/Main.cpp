/*
 * file: main.cpp
 * --------------
 * this program counts the frequency of letters in a data file.
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "filelib.h"
#include "console.h"

using namespace std;

/* constants */

static constexpr int COLUMNS = 7;

/* main program */


int main() {
    setConsoleOutputColor("white");

    Vector<int> letterCounts(26);
    ifstream infile;
    promptUserForFile(infile, "Input file: ");

    char ch;
    while (infile.get(ch)) {
        if (isalpha(ch)) {
            letterCounts[toupper(ch) - 'A']++;
        }
    }

    infile.close();

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        cout << setw(COLUMNS) << letterCounts[ch - 'A'] << ' ' << ch << endl;
    }

    return 0;
}
