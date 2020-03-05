#include <iostream>
#include <string>
#include "console.h"

using namespace std;

namespace my {
    void testRoot(const string& fileName, const string& expected);
    void testExtension(const string& fileName, const string& expected);
    string getRoot(const string& fileName);
    string getExtension(const string& fileName);
}

int main() {
    setConsoleOutputColor("white");

    my::testRoot("filelib.h", "filelib");
    my::testRoot("king-lear.txt", "king-lear");
    my::testRoot("king-lear", "king-lear");

    my::testExtension("filelib.h", ".h");
    my::testExtension("king-lear.txt", ".txt");
    my::testExtension("king-lear", "");

    return 0;
}

namespace my {
    void testRoot(const string& fileName, const string& expected) {
        auto actual = getRoot(fileName);

        cout << "Root for file name is " << actual << endl
             << "Result: " << (actual == expected ? "SUCCESS." : "FAILED.") << endl << endl;
    }

    void testExtension(const string& fileName, const string& expected) {
        auto actual = getExtension(fileName);

        cout << "Extension for file name is " << actual << endl
             << "Result: " << (actual == expected ? "SUCCESS." : "FAILED.") << endl << endl;
    }

    string getRoot(const string& fileName) {
        string res{""};

        for (int i = 0; i < fileName.length(); ++i) {
            char ch = fileName.at(i);

            if (ch == '.')
                return res;

            res += ch;
        }

        return res;
    }

    string getExtension(const string& fileName) {
        string res{""};

        for (int i = fileName.length() - 1; i >= 0; --i) {
            char ch = fileName.at(i);
            res = ch + res;

            if (ch == '.')
                return res;
        }

        return "";
    }
}
