/*
 * This program implements the mad libs game where a user is asked for some words
 * which should be filled in in placeholders of some story. Then, the whole story
 * with the user's words are shown.
 */

#include <iostream>
#include <cctype>
#include <fstream>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
#include "filelib.h"

constexpr char PLACEHOLDER_START = '<';
constexpr char PLACEHOLDER_END = '>';

using namespace std;

/**
 * Function: welcome
 * -----------------
 * Prints the welcome message and the rules of the game to the user.
 */
static void welcome();

/**
 * Function: createStory
 * ---------------------
 * Creates a story from the input file 'infile' asking the user for some words
 * for each placeholder in the input file and sets 'replacedCount' to the number of
 * all the replaced placeholders.
 */
static string createStory(ifstream& infile, int& replacedCount);

/**
 * Function: fillLine
 * ------------------
 * Asks the user to fill in each placeholder in the given string 'line' and increments
 * 'replaceCount' output parameter if a plcaholder is replaced.
 */
static string fillLine(const string& line, int& replacedCount);

/**
 * Function: promptForWord
 * -----------------------
 * Asks the user for specific word dependent on the given 'wordType'.
 */
static string promptForWord(const string& wordType);


/**
 * Function: isVowel
 * -----------------
 * Returns true if 'ch' is a vowel.
 */
bool isVowel(char ch);


/**
 * Function: main
 * --------------
 * Entry point to the application. It opens the input file and prints the statistic
 * of the game.
 */
int main() {
    welcome();

    int storiesNumber = 0;
    int totalPlaceholders = 0;

    while (true) {
        int replacedCount;

        ifstream inputFile;
        promptUserForFile(inputFile, "Mad Lib input file? ");

        cout << endl;

        string story = createStory(inputFile, replacedCount);
        inputFile.close();

        cout << endl << "Your Mad Lib story" << endl;
        cout << story << endl;
        cout << replacedCount << " placeholder(s) replaced." << endl;

        ++storiesNumber;
        totalPlaceholders += replacedCount;

        if (!getYesOrNo("Do another Mad Lib (Y/N)? ")) {
            cout << "Mad Libs stories you created: " << storiesNumber << endl;
            cout << "Total placeholders replaced: " << totalPlaceholders
                 << fixed << setprecision(1) << " (" << double(totalPlaceholders) / storiesNumber << ") per story" << endl;
            break;
        }
    }

    return 0;
}

static void welcome() {
    cout << "Welcome to Mad Libs!" << endl;
    cout << "I will ask you to provide various words" << endl
         << "and phrases to fill in a story." << endl;
    cout << "At the end, I will display your story to you." << endl << endl;
}

static string createStory(ifstream& infile, int& replacedCount) {
    replacedCount = 0;
    string story;
    string line;

    while (getline(infile, line)) {
        story += (fillLine(line, replacedCount) + '\n');
    }

    return story;
}

static string fillLine(const string& line, int& replacedCount) {
    string filledLine;
    int placeholderStart = -1;

    for (size_t i = 0; i < line.length(); ++i) {
        if (line[i] == PLACEHOLDER_START) {
            placeholderStart = i;
        } else if (placeholderStart == -1) {
            filledLine += line[i];
        } else if (line[i] == PLACEHOLDER_END) {
            string word = promptForWord(line.substr(placeholderStart + 1, i - placeholderStart - 1));
            filledLine += word;
            placeholderStart = -1;

            if (!word.empty()) {
                ++replacedCount;
            }
        }
    }

    if (placeholderStart >= 0) {
        filledLine += line.substr(placeholderStart);
    }

    return filledLine;
}

static string promptForWord(const string& wordType) {
    cout << "Please type "
         << (isVowel(wordType[0]) ? "an " : "a ")
         << wordType << ": ";

    string word;
    getline(cin, word);

    return word;
}

bool isVowel(char ch) {
    return tolower(ch) == 'a'
            || ch == 'e'
            || ch == 'i'
            || ch == 'o'
            || ch == 'u'
            || ch == 'y';
}
