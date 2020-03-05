#include <iostream>
#include <string>
#include "stack.h"
#include "console.h"

using namespace std;

bool checkBalance(const string& text);
bool bracketsMatch(char br1, char br2);
void testCheckBalance(const string& text, bool expected);

int main() {
    testCheckBalance("(([])", false);
    testCheckBalance(")(", false);
    testCheckBalance("{(})", false);
    testCheckBalance("{ s = 2 * (a[2] + 3); x = (1 + (2)); }", true);

    return 0;
}

void testCheckBalance(const string& text, bool expected) {
    bool actual = checkBalance(text);

    cout << "Bracketing operators is " << (actual ? "" : "not ") << "balanced in the string \""
         << text << "\"." << endl;
    cout << "Result: " << (actual == expected ? "Success." : "Failed.") << endl;
}

bool checkBalance(const string& text) {
    Stack<char> brackets;

    for (char ch: text) {
        if (ch == '(' || ch == '[' || ch == '{') {
            brackets.push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (brackets.isEmpty() || !bracketsMatch(brackets.peek(), ch)) {
                return false;
            } else {
                brackets.pop();
            }
        }
    }

    return brackets.isEmpty();
}

bool bracketsMatch(char br1, char br2) {
    return (br1 == '{' && br2 == '}')
            || (br1 == '[' && br2 == ']')
            || (br1 == '(' && br2 == ')');
}
