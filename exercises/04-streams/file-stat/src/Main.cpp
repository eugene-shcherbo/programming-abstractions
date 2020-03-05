#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include "console.h"

using namespace std;

namespace my {
    void gatherFileStat(ifstream& infile, int& lines, int& words, int& characters);
    void printFileStat(int lines, int words, int characters);
    void promtUserForFile(ifstream& file, string prompt);
    int numberOfDigits(int number);
}

int main() {
    setConsoleOutputColor("white");

    ifstream infile;
    my::promtUserForFile(infile, "Input file: ");

    int lines, words, characters;
    my::gatherFileStat(infile, lines, words, characters);
    my::printFileStat(lines, words, characters);

    infile.close();

    return 0;
}

namespace my {
    void promtUserForFile(ifstream& file, string prompt) {
        while (true) {
            cout << prompt;
            string filename;
            getline(cin, filename);
            file.open(filename);

            if (!file.fail()) return;
            file.clear();

            cout << "Unable to open that file. Try again." << endl;
        }
    }

    void gatherFileStat(ifstream& infile, int& lines, int& words, int& characters) {
        char ch;
        bool isWordStarted {false};

        /*while (infile.get(ch)) {
            ++characters;

            if (isalnum(ch) || ispunct(ch))
                isWordStarted = true;
            else if (isWordStarted) {
                ++words;
                isWordStarted = false;
            }

            if (ch == '\n')
                ++lines;

        }

        if (infile.eof()) {
            ++words;
            ++characters;
            ++lines;
        }*/

        string line;

        while (getline(infile, line)) {
            ++lines;
            characters += line.length() + 1;

            istringstream istring{line};
            string word;

            while (istring >> word)
                ++words;
        }
    }

    void printFileStat(int lines, int words, int characters) {
        cout << right;
        int n = numberOfDigits(characters);
        cout << "Chars: " << setw(n) << characters << endl;
        cout << "Words: " << setw(n) << words << endl;
        cout << "Lines: " << setw(n) << lines << endl;
    }

    int numberOfDigits(int number) {
        int res{0};

        while (number > 0) {
            ++res;
            number /= 10;
        }

        return res;
    }
}
