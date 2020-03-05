#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "console.h"

using namespace std;

constexpr int ENGLISH_ALPHABET_LENGTH = 26;

namespace my {
    void promptUserForFile(ifstream& infile, const string& prompt);
    void displayFileInRandomWay(ifstream& infile);
    char applyRandomRule(char ch);
    int randomInteger(int low, int hight);
}

int main() {
    setConsoleOutputColor("white");

    ifstream infile;
    my::promptUserForFile(infile, "Input file: ");
    my::displayFileInRandomWay(infile);

    infile.close();

    return 0;
}

namespace my {
    void promptUserForFile(ifstream& infile, const string& prompt) {
        while (true) {
            cout << prompt;
            string fileName;
            getline(cin, fileName);
            infile.open(fileName);

            if (!infile.fail())
                return;

            cout << "Unable to open that file. Try again." << endl;
        }
    }

    void displayFileInRandomWay(ifstream& infile) {
        char ch;

        while (infile.get(ch)) {
            cout << applyRandomRule(ch);
        }

        if (!infile.eof())
            cout << "Error: omething wrong has happed while reading the file."
                 << endl;

        cout << endl;
    }

    char applyRandomRule(char ch) {
        if (!isalpha(ch))
            return ch;

        auto randomLetter = char(randomInteger(0, ENGLISH_ALPHABET_LENGTH - 1));

        if (isupper(ch)) {
            return 'A' + randomLetter;
        } else
            return 'a' + randomLetter;
    }

    int randomInteger(int low, int hight) {
        double d = rand() / (double(RAND_MAX) + 1);
        double s = d * (double(hight) - low + 1);

        return int(floor(low + s));
    }
}
