#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "console.h"

using namespace std;

namespace my {
    void promptUserForFile(ifstream& infile, string prompt);
    void promptUserForFile(ofstream& outfile, string prompt);
    void applyCensor(ifstream& infile, ofstream& outfile, const string& ban);
    bool contains(const string& str, char ch);
    string getFilename(string promt);
}

int main() {
    setConsoleOutputColor("white");

    ifstream infile;
    ofstream outfile;
    string ban;

    my::promptUserForFile(infile, "Input file: ");
    my::promptUserForFile(outfile, "Output file: ");

    cout << "Letters to banish: ";
    getline(cin, ban);

    my::applyCensor(infile, outfile, ban);

    infile.close();
    outfile.close();

    return 0;
}

void my::promptUserForFile(ifstream& file, string prompt) {
    while (true) {
        file.open(getFilename(prompt));
        if (!file.fail()) return;
        file.clear();
        cout << "Unable to open that file. Try again." << endl;
    }
}

void my::promptUserForFile(ofstream& outfile, string prompt) {
    while (true) {
        outfile.open(getFilename(prompt));
        if (!outfile.fail()) return;
        outfile.clear();
        cout << "Unable to open or create that file. Try again." << endl;
    }
}

string my::getFilename(string prompt) {
    cout << prompt;
    string filename;
    getline(cin, filename);
    return filename;
}

void my::applyCensor(ifstream& infile, ofstream& outfile, const string& ban) {
    char ch;

    while (infile.get(ch)) {
        if (!contains(ban, ch))
            outfile << ch;
    }
}

bool my::contains(const string& str, char ch) {
    for (int i = 0; i < str.length(); ++i) {
        if (tolower(str[i]) == tolower(ch))
            return true;
    }

    return false;
}
