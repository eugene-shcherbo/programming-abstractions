#include <iostream>
#include <string>
#include <iomanip>
#include "console.h"
#include "map.h"
#include "lexicon.h"

using namespace std;

void countWords(const Lexicon& lex, Map<int, int>& count);

int main() {
    Lexicon english("EnglishWords.dat");
    Map<int, int> count;
    countWords(english, count);

    for (int key: count) {
        cout << key << "\t" << right << setw(8) <<  count[key] << endl;
    }

    return 0;
}

void countWords(const Lexicon& lex, Map<int, int>& count) {
    for (string word: lex) {
        ++count[word.length()];
    }
}
