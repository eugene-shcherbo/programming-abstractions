#include <iostream>
#include <string>
#include "console.h"
using namespace std;

namespace my {
    void test(const string& fileName, const string& ext, const string& expected);
    string defaultExtension(const string& fileName, const string& extension);
    bool hasExtension(const string& fileName);
    bool isExtensionOverride(const string& extension);
    string getRoot(const string& fileName);
}

int main() {
    setConsoleOutputColor("white");
    my::test("Shakespeare", ".txt", "Shakespeare.txt");
    my::test("Shakespeare.txt", ".cpp", "Shakespeare.txt");
    my::test("Shakespeare.txt", "*.cpp", "Shakespeare.cpp");
    my::test("Shakespeare.txt", "", "Shakespeare.txt");
    my::test("Shakespeare.txt", "*.", "Shakespeare.");


    return 0;
}

namespace my {
    void test(const string& fileName, const string& ext, const string& expected) {
        auto actual = defaultExtension(fileName, ext);

        cout << "Filename is " << actual << endl
             << "Result: " << (actual == expected ? "SUCCESS" : "FAILED")
             << endl << endl;
    }

    string defaultExtension(const string& fileName, const string& extension) {
        if (!hasExtension(fileName))
            return fileName + extension;
        else if (isExtensionOverride(extension))
            return getRoot(fileName) + extension.substr(1);
        return fileName;
    }

    bool hasExtension(const string& fileName) {
        for (int i = fileName.length() - 1; i >= 0; --i) {
            if (fileName.at(i) == '.')
                return true;
        }
        return false;
    }

    bool isExtensionOverride(const string& extension) {
        return extension.length() > 0 && extension.at(0) == '*';
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
}
