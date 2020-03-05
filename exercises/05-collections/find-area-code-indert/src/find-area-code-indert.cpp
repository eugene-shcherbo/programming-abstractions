#include <iostream>
#include <fstream>
#include "strlib.h"
#include "map.h"
#include "simpio.h"
#include "console.h"

using namespace std;

void readAreaCodes(const string& filename, Map<int, string>& areaCodes);
void printState(int code, const Map<int, string>& areaCodes);
void printCodes(const string& state, const Map<string, Vector<int>>& codesLookup);
void invertCodes(const Map<int, string>& areaCodes, Map<string, Vector<int>>& codesByArea);

int main() {
    Map<int, string> areaByCode;
    Map<string, Vector<int>> codesByArea;
    readAreaCodes("area-codes.txt", areaByCode);
    invertCodes(areaByCode, codesByArea);

    while(true) {
        string input = getLine("Enter area code or state name: ");

        if (input.empty()) {
            break;
        }

        if (stringIsInteger(input)) {
            printState(stringToInteger(input), areaByCode);
        } else {
            printCodes(input, codesByArea);
        }
    }

    return 0;
}

void readAreaCodes(const string& filename, Map<int, string>& areaByCode) {
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
        areaByCode.put(code, line.substr(4));
    }
}

void invertCodes(const Map<int, string>& areaLookup, Map<string, Vector<int>>& codesLookup) {
    for (int code: areaLookup) {
        string area = areaLookup[code];
        codesLookup[area].add(code);
    }
}

void printState(int code, const Map<int, string>& areaCodes) {
    if (areaCodes.containsKey(code)) {
        cout << areaCodes[code] << endl;
    }
}

void printCodes(const string& state, const Map<string, Vector<int>>& codesLookup) {
    if (codesLookup.containsKey(state)) {
        for (int code: codesLookup[state]) {
            cout << code << endl;
        }
    }
}
