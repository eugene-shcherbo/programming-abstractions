#include <iostream>
#include <string>
using namespace std;

constexpr int DEFAULT_SUBSTR_NUMBER{-1};

string substr(string str, int pos, int n = DEFAULT_SUBSTR_NUMBER);
void testSubstr(string str, int pos, int n = DEFAULT_SUBSTR_NUMBER);
[[ noreturn ]] void error(string msg);

int main()
{
    testSubstr("Hello World", 0);
    testSubstr("Hello World", 0, 5);
    testSubstr("Hello Words", 6, 2);
    testSubstr("Hello Words", 40, 17);

    return 0;
}

void testSubstr(string str, int pos, int n) {
    cout << "Substr of "
         << str << " for (" << pos << ", " << n << ") is "
         << substr(str, pos, n) << endl;
}

string substr(string str, int pos, int n) {
    int strLength = static_cast<int>(str.length());

    if (pos > strLength) {
        error("Error: pos can't be greater than the string of the length.");
    }

    n = n == DEFAULT_SUBSTR_NUMBER || n > strLength
            ? strLength
            : n;

    string res;

    for (int i = 0; i < n && (pos + i) < strLength; ++i) {
        res += str.at(pos + i);
    }

    return res;
}

void error(string msg) {
    cerr << msg << endl;
    exit(1);
}
