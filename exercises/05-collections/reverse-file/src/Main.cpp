/*
 * file: main.cpp
 * --------------
 * This program dispays the lines of an input file in reverse order.
 */

#include <iostream>
#include <fstream>
#include <string>
#include "filelib.h"
#include "vector.h"
#include "console.h"

using namespace std;

namespace my {

    /* Function prototypes */

    void readEntireFile(istream& is, Vector<string>& lines);
}

/* Main program */

int main() {
    setConsoleOutputColor("white");
    ifstream infile;
    Vector<string> lines;
    promptUserForFile(infile, "Input file: ");
    my::readEntireFile(infile, lines);
    infile.close();

    for (int i = lines.size() - 1; i >= 0; --i) {
        cout << lines[i] << endl;
    }

    return 0;
}

/*
 * function: readEntireFile
 * Usage: readEntireFile(is, lines);
 * ---------------------------------
 * Reads the entire contents of the specified input stream into the
 * string vector lines. The client is responsible for opening and
 * closing the stream.
 */

void my::readEntireFile(istream& is, Vector<string>& lines) {
    string line;
    while (getline(is, line)) {
        lines.add(line);
    }
}
