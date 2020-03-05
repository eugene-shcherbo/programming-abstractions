#include <iostream>
#include <sstream>
#include <string>
#include "console.h"

using namespace std;

double getReal(string prompt);
string getLine(string prompt);

int main() {
    setConsoleOutputColor("white");

    double real = getReal("Enter a double number: ");
    string line = getLine("Enter a line: ");

    cout << "Your real number is " << real
         << endl
         << "And your line is " << line
         << endl;

    return 0;
}

double getReal(string prompt) {
    double res;
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        istringstream istream(line);
        istream >> res;
        if (!istream.fail() && istream.eof())
            return res;
        istream.clear();
        cout << "Illegal real format. Try again." << endl;
    }
}

string getLine(string prompt) {
    cout << prompt;
    string res;
    getline(cin, res);
    return res;
}
