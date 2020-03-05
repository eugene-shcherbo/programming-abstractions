/**
 * File: word-ladder.cpp
 * ---------------------
 * Implements a program to find word ladders connecting pairs of words.
 */

#include <iostream>
using namespace std;

#include "console.h"
#include "queue.h"
#include "vector.h"
#include "lexicon.h"
#include "set.h"
#include "strlib.h"
#include "simpio.h"

static const string ENGLISH_LANGUAGE_DATAFILE = "dictionary.txt";

/**
 * Function: playWordLadder
 * ------------------------
 * Runs the word ladder game.
 */
static void playWordLadder();

/**
 * Function: getWord
 * -----------------
 * Asks the user with the 'prompt' for a word until the word is a valid english one
 * presented in the 'english' lexicon.
 */
static string getWord(const Lexicon& english, const string& prompt);

/**
 * Function: generateLadder
 * ------------------------
 * Generate a ladder from the 'start' to 'end' and displays the result ladder to the user.
 * Looks for such ladder which elements are all valid english words from the 'english' lexicon.
 */
static void generateLadder(const Lexicon& english, const string& start, const string& end);

/**
 * Function: generateWords
 * -----------------------
 * Generates a set of english words from the 'english' lexicon and adds them into the 'words' set.
 * Every word differ only by one letter from the 'source' word.
 */
static void generateWords(const Lexicon& english, const string& source, Set<string>& words);

/**
 * Function: printLadder
 * ---------------------
 * Prints the ladder to the user.
 */
static void printLadder(const Vector<string>& ladder);

/**
 * Function: generateHopLadder
 * ---------------------------
 * Generates new ladder adding 'word' to the end of the 'sourceLadder'. Then adds new generated ladder to the queue
 * of all ladders called 'ladders'.
 */
static void generateHopLadder(const string& word, const Vector<string>& sourceLadder, Queue<Vector<string>>& ladders);

/**
 * Function: main
 * --------------
 * Provides an entry point to the application and starts the game.
 */
int main() {
    cout << "Welcome to the word ladder application!" << endl << endl;
    playWordLadder();
    cout << "Thanks for playing!" << endl;
    return 0;
}

static void playWordLadder() {
    Lexicon english(ENGLISH_LANGUAGE_DATAFILE);
    while (true) {
        string start = getWord(english, "Please enter the source word [return to quit]: ");
        if (start.empty()) break;
        string end = getWord(english, "Please enter the destination word [return to quit]: ");
        if (end.empty()) break;
        generateLadder(english, start, end);
    }
}

static string getWord(const Lexicon& english, const string& prompt) {
    while (true) {
        string response = trim(toLowerCase(getLine(prompt)));
        if (response.empty() || english.contains(response)) return response;
        cout << "Your response needs to be an English word, so please try again." << endl;
    }
}

static void generateLadder(const Lexicon& english, const string& start, const string& end) {
    Queue<Vector<string>> ladders { Vector<string>{start} };
    Set<string> usedWords { start };

    while (!ladders.isEmpty()) {
        Vector<string> ladder = ladders.dequeue();
        string topWord = ladder[ladder.size() - 1];

        if (topWord == end) {
            printLadder(ladder);
            return;
        } else {
            Set<string> words;
            generateWords(english, topWord, words);

            for (string word: words) {
                if (!usedWords.contains(word)) {
                    generateHopLadder(word, ladder, ladders);
                    usedWords.add(word);
                }
            }
        }
    }

    cout << "No ladders exists" << endl;
}

static void generateWords(const Lexicon& english, const string& source, Set<string>& words) {
    string word = source;

    for (int i = 0; i < source.length(); ++i) {
        char letter = word[i];
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            word[i] = ch;
            if (english.contains(word) && ch != letter) {
                words.add(word);
            }
        }
        word[i] = letter;
    }
}

static void printLadder(const Vector<string>& ladder) {
    cout << "Found ladder: ";
    for (string hop: ladder) {
        cout << hop << ' ';
    }
    cout << endl;
}

static void generateHopLadder(const string& word, const Vector<string>& sourceLadder, Queue<Vector<string>>& ladders) {
    Vector<string> hopLadder = sourceLadder;
    hopLadder.add(word);
    ladders.enqueue(hopLadder);
}
