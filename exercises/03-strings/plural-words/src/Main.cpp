#include <iostream>
#include <string>
#include <cctype>
#include "strlib.h"
#include "console.h"
using namespace std;

string createRegularPlural(string word);
bool isEsRule(string word);
bool isIesRule(string word);
bool isConsonant(char ch);
bool isVowel(char ch);
void testPlural(string word, string expected);

int main() {
    setConsoleOutputColor("white");

    testPlural("desk", "desks");
    testPlural("bus", "buses");
    testPlural("launch", "launches");
    testPlural("city", "cities");
    testPlural("s", "ses");

    return 0;
}

void testPlural(string word, string expected) {
    auto plural = createRegularPlural(word);
    cout << "Plular for " << word << " is " << plural
         << ". " << (expected == plural ? "SUCCESS!" : "FAILED!")
         << endl;
}

string createRegularPlural(string word) {
    if (isEsRule(word))
        return word + "es";
    else if (isIesRule(word))
        return word.replace(word.length() - 1, 1, "ies");
    else
        return word + "s";
}

bool isEsRule(string word) {
    auto n = word.length();
    auto lastCh = word[n - 1];

    if (lastCh == 's' || lastCh == 'x' || lastCh == 'z')
        return true;
    else if (n > 1)
        return lastCh == 'h' && (word[n - 2] == 'c' || word[n - 2] == 's');
    else
        return false;
}

bool isIesRule(string word) {
    auto n = word.length();
    return word[n - 1] == 'y' && isConsonant(word[n - 2]);
}

bool isConsonant(char ch) {
    return !isVowel(ch);
}

bool isVowel(char ch) {
    return ch == 'a'
            || ch == 'e'
            || ch == 'i'
            || ch == 'o'
            || ch == 'u'
            || ch == 'y';
}
