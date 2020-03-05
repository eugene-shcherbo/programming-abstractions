#include <iostream>
#include <sstream>
#include "console.h"
using namespace std;

int getInteger(string prompt);

int main() {
  cout << "Hello, world!" << endl;
  return 0;
}

/*
 * Function: getInteger
 * Usage: int n = getInteger(prompt);
 * ----------------------------------
 * Requests an integer value from the user. The function begins by
 * printing prompt string on the console and then waits for the
 * user to enter a line of input data. If that line contains a
 * single integer, the function returns the corresponding integer
 * value. If the input is not a legal of ir extraneous
 * characters (other than whitespaces) appear on the input line,
 * the implementation gives the user a chance to reenter the value.
 */

int getInteger(string prompt) {
    int value;
    string line;

    while (true) {
        cout << prompt;
        getline(cin, line);
        istringstream istream{line};
        istream >> value >> ws;
        if (!istream.fail() && istream.eof()) break;
        cout << "Illegal integer format. Try again." << endl;
    }

    return value;
}
