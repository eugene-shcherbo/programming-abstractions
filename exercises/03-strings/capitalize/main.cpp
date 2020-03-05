#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string capitalize(const string& str);
void testCapitalize(const string& str);

int main()
{
    testCapitalize("hello world");
    testCapitalize("Hello World");
    testCapitalize("HELLO WORLD");

    return 0;
}

void testCapitalize(const string& str) {
    cout << "Capitalized of " << str << " is " << capitalize(str) << endl;
}

string capitalize(const string& str) {
    string res = str;
    size_t n = res.length();

    if (n == 0) {
        return str;
    } else if (isalpha(str.at(0))) {
        res.at(0) = toupper(res.at(0));
    }

    for (size_t i = 1; i < n; ++i) {
        res.at(i) = tolower(res.at(i));
    }

    return res;
}
