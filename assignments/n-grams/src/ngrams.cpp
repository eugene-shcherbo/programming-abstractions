/**
  * File: ngrams.cpp
  * ----------------
  * Generates random text based on input file using Markov chain.
  */

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "filelib.h"
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "queue.h"
#include "console.h"
#include "random.h"

using namespace std;

/**
 * Function: getNValue
 * -------------------
 * Asks the user with the given 'prompt' for a value of N he or she wants to use in a text generating.
 */
static int getNValue(const string& prompt);

/**
 * Function: buildNGramsMap
 * ------------------------
 * Reads the given 'infile' file and builds the n-grams 'map' based on the given 'nval' value. The map is
 * built in the {prefix:suffix} format where
 *  - the prefix is n-1 words used to choose the nth word, and
 *  - the suffix are collection where the nth word is chosen from
 * For example, for the following part of a some text: "to be or to be just"
 * the map will look like { { "to", "be" }, "{ "or", "just }" }
 */
static void buildNGramsMap(int nval, ifstream& infile, Map<Queue<string>, Vector<string>>& map);

/**
 * Function: addWordToMapAndShiftWindow
 * ------------------------------------
 * A helper function which adds a word into the 'map' for the key represented by 'window' and
 * "shifts" the 'window' adding 'word' there and removing the first word to always
 * have n-1 words in the window.
 */
static void addWordToMapAndShiftWindow(const string& word, Map<Queue<string>, Vector<string>>& map, Queue<string>& window);

/**
 * Function: generateText
 * ----------------------
 * Generates random text with number of words equals to the given 'nWords'. The text is generated
 * using Markov chaing based on the provided 'nGramsMap'
 */
static string generateText(const Map<Queue<string>, Vector<string>>& nGramsMap, int nWords);

int main() {
    ifstream infile;
    promptUserForFile(infile, "Input file name?");

    int nval = getNValue("Value of N?");
    Map<Queue<string>, Vector<string>> nGramsMap;
    buildNGramsMap(nval, infile, nGramsMap);

    infile.close();

    while (true) {
        int nWords = getInteger("# of random words to generate (0 to quit)?");

        if (nWords == 0) {
            break;
        }

        cout << generateText(nGramsMap, nWords) << endl << endl;
    }

    return 0;
}

static int getNValue(const string& prompt) {
    while (true) {
        int nval = getInteger(prompt);

        if (nval > 1) {
            return nval;
        }

        cout << "The value must be 2 or greater. Try again." << endl;
    }
}

static void buildNGramsMap(int nval, ifstream& infile, Map<Queue<string>, Vector<string>>& map) {
    string word;
    Queue<string> window;
    Vector<string> frontWords;

    while (frontWords.size() < nval - 1 && infile >> word) {
        window.enqueue(word);
        frontWords.add(word);
    }

    while (infile >> word) {
        addWordToMapAndShiftWindow(word, map, window);
    }

    for (string word: frontWords) {
        addWordToMapAndShiftWindow(word, map, window);
    }
}

static void addWordToMapAndShiftWindow(const string& word, Map<Queue<string>, Vector<string>>& map, Queue<string>& window) {
    map[window].add(word);
    window.dequeue();
    window.enqueue(word);
}

static string generateText(const Map<Queue<string>, Vector<string>>& nGramsMap, int nWords) {
    auto startPoint = randomInteger(0, nGramsMap.size() - 1);
    auto window = nGramsMap.keys().get(startPoint);
    string text = "... ";

    for (int i = 0; i < nWords; ++i) {
        auto suffixes = nGramsMap[window];
        text += window.dequeue() + ' ';
        int randomWordIndex = randomInteger(0, suffixes.size() - 1);
        window.enqueue(suffixes[randomWordIndex]);
    }

    return text + ' ';
}
