#include <iostream>
#include <fstream>
#include <string>
#include "console.h"

using namespace std;


namespace my {
    string findLongestLineInFile(ifstream& infile);
    void promptUserForFile(ifstream& infile, string prompt);
}

int main() {
    setConsoleOutputColor("white");

    ifstream infile;
    my::promptUserForFile(infile, "Input file: ");
    string longestLine = my::findLongestLineInFile(infile);

    cout << "Longest line is '" << longestLine << "'" << endl;

    infile.close();

    return 0;
}

void my::promptUserForFile(ifstream& infile, string prompt) {
    while (true) {
        cout << prompt;
        string filename;
        getline(cin, filename);
        infile.open(filename);

        if (!infile.fail()) return;

        infile.clear();
        cout << "Unable to open that file. Try again." << endl;
    }
}

string my::findLongestLineInFile(ifstream& infile) {
    string longest{""};
    string line;

    while (getline(infile, line)) {
        if (line.length() > longest.length())
            longest = line;
    }

    if (infile.eof())
        return longest;

    cout << "Some errors caused during reading the file." << endl;

    return longest;
}
