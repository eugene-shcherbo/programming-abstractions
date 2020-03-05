#include <iostream>
#include <sstream>
#include "console.h"

using namespace std;

namespace my {
    string realToString(double n);
    double stringToReal(const string& n);
    void test(double n, string expected);
    void error(string msg);
    void test(string n, double exptected);
}


int main() {
    setConsoleOutputColor("white");

    my::test(10.5, "10.5");
    my::test(1, "1");
    my::test(1.5631, "1.5631");
    my::test("1.5631", 1.5631);
    my::test("1", 1);
    my::test("10.5", 10.5);

    return 0;
}

void my::test(double n, string expected) {
    auto actual = realToString(n);
    cout << "String value: " << actual << endl
         << "Result: " << (actual == expected ? "SUCCESS" : "FAILED")
         << endl << endl;
}

void my::test(string n, double expected) {
    auto actual = stringToReal(n);
    cout << "String value: " << actual << endl
         << "Result: " << (actual == expected ? "SUCCESS" : "FAILED")
         << endl << endl;
}

string my::realToString(double n) {
    ostringstream ostream;
    ostream << n;
    return ostream.str();
}

double my::stringToReal(const string& n) {
    istringstream istream(n);
    double res;
    istream >> res;
    if (istream.fail() || !istream.eof())
        error("stringToReal: Illegal real number format");
    return res;
}

void my::error(string msg) {
    cerr << msg << endl;
    exit(1);
}


