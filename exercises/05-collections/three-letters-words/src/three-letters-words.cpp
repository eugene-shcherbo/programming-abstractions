#include <iostream>
#include "set.h"
#include "lexicon.h"
#include "console.h"

using namespace std;

void generateTwoLettersWords(const Lexicon& english, Set<string>& words);
void generateThreeLettersWords(const Set<string>& twoLetters, const Lexicon& english, Set<string>& words);

int main() {
    Lexicon english("EnglishWords.dat");
    Set<string> twoLetters;
    Set<string> threeLetters;

    generateTwoLettersWords(english, twoLetters);
    generateThreeLettersWords(twoLetters, english, threeLetters);

    for (string word: threeLetters) {
        cout << word << endl;
    }

    return 0;
}

void generateTwoLettersWords(const Lexicon& english, Set<string>& words) {
    string word = "xx";

    for (char c1 = 'a'; c1 <= 'z'; ++c1) {
        word[0] = c1;

        for (char c2 = 'a'; c2 <= 'z'; ++c2) {
            word[1] = c2;

            if (english.contains(word)) {
                words.add(word);
            }
        }
    }
}

void generateThreeLettersWords(const Set<string>& twoLetters, const Lexicon& english, Set<string>& words) {
    for (char c = 'a'; c <= 'z'; ++c) {
        for (string twoLetterWord: twoLetters) {
            string threeLetterWord1 = twoLetterWord + c;
            string threeLetterWord2 = c + twoLetterWord;

            if (english.contains(threeLetterWord1)) {
                words.add(threeLetterWord1);
            }

            if (english.contains(threeLetterWord2)) {
                words.add(threeLetterWord2);
            }
        }
    }
}

