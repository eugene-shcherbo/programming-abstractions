#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "strlib.h"
#include "vector.h"

using namespace std;

void readVectorFromFile(const std::string& filename, Vector<string>& words);

int main() {
    text::Lexicon lex("SmallDict.txt");
    Vector<string> words;
    readVectorFromFile("SmallDict.txt", words);

    for (const string& word: words) {
        cout << "contains " << word << "? " << boolToString(lex.contains(word)) << endl;
    }

    Vector<string> prefixes;
    readVectorFromFile("Prefixes.txt", prefixes);

    for (const string& prefix: prefixes) {
        cout << "contains prefix " << prefix << "? " << boolToString(lex.containsPrefix(prefix)) << endl;
    }

    return 0;
}

void readVectorFromFile(const std::string& filename, Vector<string>& words) {
    ifstream infile(filename);

    if (infile.good()) {
        string word;
        while (getline(infile, word)) {
            words.add(word);
        }
    }
}
