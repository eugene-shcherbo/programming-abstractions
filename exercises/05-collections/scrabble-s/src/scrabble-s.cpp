#include <iostream>
#include <string>
#include "strlib.h"
#include "console.h"
#include "set.h"
#include "lexicon.h"

using namespace std;

void getWordsWithSTiles(const Lexicon& english, Set<string>& sTilesWords);

int main() {
    Lexicon english("EnglishWords.dat");
    Set<string> sTilesWords;
    getWordsWithSTiles(english, sTilesWords);

    cout << "There are " << sTilesWords.size() << " words." << endl;

    for (string word: sTilesWords) {
        cout << word << endl;
    }

    return 0;
}

void getWordsWithSTiles(const Lexicon& english, Set<string>& sTilesWords) {
    for (string word: english) {
        string beginS = "s" + word;
        string tileS = word + "s";

        if (english.contains(beginS)
                && english.contains(tileS)) {
            sTilesWords.add(word);
        }
    }
}
