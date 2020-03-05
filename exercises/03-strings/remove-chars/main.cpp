#include <iostream>
#include <string>
using namespace std;

string removeCharacters(string str, string remove);
void removeCharactersInPlace(string& str, const string& remove);
bool contains(string str, char ch);

int main()
{
    string str, remove;
    cout << "This program removes characters from a string." << endl
         << "Enter a string: ";
    getline(cin, str);
    cout << "Enter the characters to remove: ";
    getline(cin, remove);
    cout << "The result is " << removeCharacters(str, remove) << endl
         << "Original string is " << str << endl;
    removeCharactersInPlace(str, remove);
    cout << "Original string is " << str << endl;

    return 0;
}

void removeCharactersInPlace(string& str, const string& remove) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (contains(remove, str.at(i))) {
            str.erase(i, 1);
            --i;
        }
    }
}

string removeCharacters(string str, string remove) {
    string result = "";
    for (size_t i = 0; i < str.length(); ++i) {
        auto ch = str.at(i);
        if (!contains(remove, ch)) {
            result += ch;
        }
    }
    return result;
}

bool contains(string str, char ch) {
    for (size_t i = 0; i < str.length(); ++i) {
        if (str.at(i) == ch)
            return true;
    }
    return false;
}
