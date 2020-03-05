#include <iostream>
#include <string>
#include <fstream>
#include "console.h"

using namespace std;

namespace my {
    void promptUserForFile(ifstream& infile, string prompt);
    void promptUserForFile(ofstream& outfile, string prompt);
    string getFilename(string prompt);
    void replaceTabsWithSpaces(ifstream& infile, ofstream& outfile);
    void writeSpaces(ostream& os, int number);
}

int main() {
    setConsoleOutputColor("white");

    ifstream infile;
    ofstream outfile;

    my::promptUserForFile(infile, "Input file: ");
    my::promptUserForFile(outfile, "Output file: ");
    my::replaceTabsWithSpaces(infile, outfile);

    return 0;
}

void my::promptUserForFile(ifstream& infile, string prompt) {
    while (true) {
        infile.open(getFilename(prompt));
        if (!infile.fail())
            return;
        infile.clear();
        cout << "Unable to open that file. Try again" << endl;
    }
}

void my::promptUserForFile(ofstream& outfile, string prompt) {
    while (true) {
        outfile.open(getFilename(prompt));
        if (!outfile.fail())
            return;
        outfile.clear();
        cout << "Unable to open that file. Try again: ";
    }
}

string my::getFilename(string prompt) {
    cout << prompt;
    string filename;
    getline(cin, filename);
    return filename;
}

void my::replaceTabsWithSpaces(ifstream& infile, ofstream& outfile) {
    constexpr int tabStop = 8;
    char ch;
    size_t pos{0};

    while (infile.get(ch)) {
        int spaces = tabStop - (pos % tabStop);

        switch (ch) {
            case '\t':
                writeSpaces(outfile, spaces);
                pos += spaces;
                break;
            case '\n':
                outfile << ch;
                pos = 0;
                break;
            default:
                outfile << ch;
                ++pos;
        }
    }
}

void my::writeSpaces(ostream& os, int number) {
    for (int i = 0; i < number; ++i) {
        os.put(' ');
    }
}
