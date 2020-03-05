#include <iostream>
#include <fstream>
#include "strlib.h"
#include "map.h"
#include "simpio.h"
#include "console.h"

using namespace std;

void readAreaCodes(const string& filename, Map<int, string>& areaCodes);
void printState(int code, const Map<int, string>& areaCodes);
void printCodes(const string& state, const Map<int, string>& areaCodes);

int main() {
    Map<int, string> areaCodes;
    readAreaCodes("area-codes.txt", areaCodes);

    while(true) {
        string input = getLine("Enter area code or state name: ");

        if (input.empty()) {
            break;
        }

        if (stringIsInteger(input)) {
            printState(stringToInteger(input), areaCodes);
        } else {
            printCodes(input, areaCodes);
        }
    }

    return 0;
}

void readAreaCodes(const string& filename, Map<int, string>& areaCodes) {
    ifstream infile(filename);

    if (infile.fail()) {
        return;
    }

    string line;

    while (getline(infile, line)) {
        if (line.length() < 4 || line[3] != '-') {
            error("Illegal data line " + line);
        }
        int code = stringToInteger(line.substr(0, 3));
        areaCodes.put(code, line.substr(4));
    }
}

void printState(int code, const Map<int, string>& areaCodes) {
    if (areaCodes.containsKey(code)) {
        cout << areaCodes[code] << endl;
    }
}

void printCodes(const string& state, const Map<int, string>& areaCodes) {
    for (int code: areaCodes) {
        if (areaCodes[code] == state) {
            cout << code << endl;
        }
    }
}
