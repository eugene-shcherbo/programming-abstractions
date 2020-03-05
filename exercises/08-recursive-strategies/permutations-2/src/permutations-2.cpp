#include <iostream>
#include "console.h"
#include "set.h"
#include "simpio.h"

using namespace std;

/**
 * Function: generatePermutations
 * ------------------------------
 * Returns a set consistsing of all permutations of the specified string.
 * This implementation uses the recursive insigth that you can generate
 * all the permutations of a string by selecting each character in turn,
 * generating all permutations of the string without that character,
 * and then concatenating the selected character on the front of each
 * string generated.
 */
Set<string> generatePermutations(const string& str);

int main() {
    string str = getLine("Enter a string: ");
    cout << "The permutations of\"" << str << "\" are:" << endl;

    for (string s: generatePermutations(str)) {
        cout << "  \"" << s << "\"" << endl;
    }

    return 0;
}

Set<string> generatePermutations(const string& str) {
    Set<string> res;

    if (str.empty()) {
        res += "";
    } else {
        char ch = str[0];
        string rest = str.substr(1);

        for (string s: generatePermutations(rest)) {
            for (int i = 0; i <= s.length(); ++i) {
                res += s.substr(0, i) + ch + s.substr(i);
            }
        }
    }

    return res;
}


