/**
 * File: random-sentence-generator.cpp
 * -----------------------------------
 * Presents a short program capable of reading in
 * context-free grammar files and generating arbitrary
 * sentences from them.
 */

#include <iostream>
#include <fstream>

using namespace std;

#include "console.h"
#include "simpio.h"   // for getLine
#include "strlib.h"   // for toLowerCase, trim
#include "map.h"
#include "vector.h"

static const string kGrammarsDirectory = "grammars/";
static const string kGrammarFileExtension = ".g";
static constexpr int kSentences = 3;

static string getNormalizedFilename(const string& filename);

static bool isValidGrammarFilename(const string& filename);

static string getFileName();

static void readDefinitions(const string& filename, Map<string, Vector<string>>& definitions);

static string getNonterminalName(const string& str, int from, int to);

static string generateRandomSentence(const Map<string, Vector<string>>& grammar);

static string getRandomProduction(const string& nonterminal, const Map<string, Vector<string>>& grammar);

static bool hasNonterminals(const string& production);

int main() {
    while (true) {
        string filename = getFileName();

        if (filename.empty()) {
            break;
        }

        Map<string, Vector<string>> definitions;
        readDefinitions(filename, definitions);

        for (int i = 0; i < kSentences; ++i) {
            cout << i + 1 << ") " << generateRandomSentence(definitions) << endl << endl;
        }
    }
    
    cout << "Thanks for playing!" << endl;

    return 0;
}

static string getFileName() {
    while (true) {
        string filename = trim(getLine("Name of grammar file? [<return> to quit]: "));

        if (filename.empty() || isValidGrammarFilename(filename)) {
            return filename;
        }

        cout << "Failed to open the grammar file named \"" << filename << "\". Please try again...." << endl;
    }
}

static bool isValidGrammarFilename(const string& filename) {
    string normalizedFileName = getNormalizedFilename(filename);
    ifstream infile(normalizedFileName.c_str());

    return !infile.fail();
}

static string getNormalizedFilename(const string& filename) {
    string normalizedFileName = kGrammarsDirectory + filename;

    if (!endsWith(normalizedFileName, kGrammarFileExtension)) {
        normalizedFileName += kGrammarFileExtension;
    }

    return normalizedFileName;
}

static void readDefinitions(const string& filename, Map<string, Vector<string>>& definitions) {
    ifstream infile(getNormalizedFilename(filename));

    string line;

    while (getline(infile, line)) {
        if (line.empty()) {
            continue;
        }

        string nonterminal = getNonterminalName(line, 0, line.size() - 1);
        getline(infile, line);
        int expNumber = stringToInteger(line);

        for (int i = 0; i < expNumber; ++i) {
            getline(infile, line);
            definitions[nonterminal].add(line);
        }
    }

    infile.close();
}

static string getNonterminalName(const string& str, int from, int to) {
    return str.substr(from + 1, to - from - 1);
}

static string generateRandomSentence(const Map<string, Vector<string>>& grammar) {
    string res = getRandomProduction("start", grammar);
    string current = res;

    while (hasNonterminals(res)) {
        auto startIndex = res.find("<");
        auto endIndex = res.find(">");
        auto nonTerminal = getNonterminalName(res, startIndex, endIndex);

        res = res.substr(0, startIndex)
                + getRandomProduction(nonTerminal, grammar)
                + res.substr(endIndex + 1);
    }

    return res;
}

static string getRandomProduction(const string& nonterminal, const Map<string, Vector<string>>& grammar) {
    int randomIndex = randomInteger(0, grammar[nonterminal].size() - 1);
    return grammar[nonterminal][randomIndex];
}

static bool hasNonterminals(const string& production) {
    return production.find("<") != string::npos;
}
