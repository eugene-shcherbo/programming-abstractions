#include <iostream>
#include <string>
#include <fstream>
#include "console.h"

using namespace std;

namespace my {
    void removeComments(istream& is, ostream& os);
    string promptUserForFile(ifstream& infile, string prompt);
    void handleOneLineComment(istream& is);
    void handleLongLineComment(istream& is);
}

int main() {
    setConsoleOutputColor("white");

    ifstream infile;
    string fileName = my::promptUserForFile(infile, "Input file: ");

    ofstream ofile;
    ofile.open("output.txt");
    my::removeComments(infile, ofile);

    ofile.close();
    infile.close();

    return 0;
}

string my::promptUserForFile(ifstream& infile, string prompt) {
    while (true) {
        cout << prompt;
        string fileName;
        getline(cin, fileName);
        infile.open(fileName);
        if (!infile.fail()) return fileName;
        cout << "Unable to open that file. Try again." << endl;
    }
}

void my::removeComments(istream& is, ostream& os) {
    char ch;

    while (is.get(ch)) {
        if (ch == '/') {
            char next = is.get();

            if (next == '/') {
                handleOneLineComment(is);
                continue;
            }
            else if (next == '*') {
                handleLongLineComment(is);
                continue;
            }
            else
                is.unget();
        }

        os << ch;
    }

}

void my::handleOneLineComment(istream& is) {
    string line;
    getline(is, line);
}

void my::handleLongLineComment(istream& is) {
    char ch;

    while (is.get(ch)) {
        if (ch == '*') {
            char next = is.get();

            if (next == '/')
                return;
            else
                is.unget();
        }
    }
}
