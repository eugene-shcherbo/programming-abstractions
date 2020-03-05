/*
 * File: Main.cpp
 * --------------
 * This program displays the contents of a file chosen by the user.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
using namespace std;

/* Function prototypes */

namespace my {
    string promptUserForFile(ifstream& infile, string prompt = "");
}

/* Main program */

int main() {
    setConsoleOutputColor("white");

    ifstream infile;
    my::promptUserForFile(infile, "Input file: ");
    char ch;
    while (infile.get(ch)) {
        cout.put(ch);
    }
    infile.close();

    return 0;
}

/*
 * Funcion: promtUserForFile
 * Usage: string fileName = promptUserForFile(infile, prompt);
 * -----------------------------------------------------------
 * Asks the user for the name of an input file and opens the reference
 * parameter infile using that name, which is returned as the result of
 * the function. If the requested file does not exist, the user is
 * given additional chances to enter a valid file name. The optional
 * prompt argument is used to give the user more information about the
 * desired input file.
 */

string my::promptUserForFile(ifstream& infile, string prompt) {
    if (prompt.empty()) prompt = "Input file: ";

    while (true) {
        cout << prompt;
        string filename;
        getline(cin, filename);
        infile.open(filename);
        if (!infile.fail()) return filename;
        infile.clear();
        cout << "Unable to open that file. Try again." << endl;
    }
}
