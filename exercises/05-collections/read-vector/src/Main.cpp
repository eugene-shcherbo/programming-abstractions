#include <iostream>
#include <fstream>
#include <string>
#include "vector.h"
#include "strlib.h"
#include "filelib.h"
#include "console.h"
using namespace std;

void readVector(istream& is, Vector<int>& vec);
void readVector(istream& is, Vector<double>& vec);
void readVector(istream& is, Vector<string>& vec);

int main() {
    ifstream intFile;
    ifstream doubleFile;
    ifstream strFile;

    openFile(intFile, "integers.txt");
    openFile(doubleFile, "reals.txt");
    openFile(strFile, "strings.txt");

    Vector<int> integers;
    Vector<double> reals;
    Vector<string> strings;

    readVector(intFile, integers);
    readVector(doubleFile, reals);
    readVector(strFile, strings);

    cout << "Integers " << integers << endl;
    cout << "Strings " << strings << endl;
    cout << "1st reals " << reals << endl;

    readVector(doubleFile, reals);
    cout << "2nnd reals " << reals << endl;

    readVector(doubleFile, reals);
    cout << "3rd reals " << reals << endl;

    return 0;
}

void readVector(istream& is, Vector<int>& vec) {
    vec.clear();
    string line;
    while (getline(is, line)) {
        if (line.empty()) {
            break;
        }
        int val = stringToInteger(line);
        vec += val;
    }
}

void readVector(istream& is, Vector<double>& vec) {
    vec.clear();
    string line;
    while (getline(is, line)) {
        if (line.empty()) {
            break;
        }
        double val = stringToDouble(line);
        vec += val;
    }
}

void readVector(istream& is, Vector<string>& vec) {
    vec.clear();
    string line;
    while (getline(is, line)) {
        if (line.empty()) {
            break;
        }
        vec += line;
    }
}
