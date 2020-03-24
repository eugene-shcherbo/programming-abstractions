/**
 * File: boggle.cpp
 * ----------------
 * Implements the game of Boggle.
 */

#include <cctype>
#include <iostream>
#include <ctype.h>
#include "console.h"
#include "gboggle.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "random.h"
#include "grid.h"
#include "map.h"
#include "set.h"
#include "lexicon.h"

using namespace std;

/*static const string kStandardCubes[16] = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};*/

/*static const string kStandardCubes[16] = {
   "AAEEGN", "ABBJOO", "PCHOAS", "KFFAPS",
   "AOOTTW", "UIMOTC", "REILDX", "EDLRVY",
   "TISDTY", "EEGHNW", "UEINSE", "RHETVW",
   "TIOSSE", "YLRTTE", "HIMNQU", "LHNNRZ"
};*/

static const string kStandardCubes[16] = {
   "EAAEGN", "BBBJOO", "PCHOAS", "FFFAPS",
   "WOOTTW", "TIMOTC", "REILDX", "YDLRVY",
   "TISDTY", "NEGHNW", "EEINSE", "HHETVW",
   "TIOSSE", "TTLRTTE", "IIMNQU", "HHNNRZ"
};

static const string kBigBoggleCubes[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

static const int kMinLength = 4;
static const double kDelayBetweenHighlights = 100;
static const double kDelayAfterAllHighlights = 500;

/**
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */
static void welcome();

/**
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */
static void giveInstructions();

/**
 * Function: getPreferredBoardSize
 * -------------------------------
 * Repeatedly prompts the user until he or she responds with one
 * of the two supported Boggle board dimensions.
 */

static int getPreferredBoardSize();

/**
 * Function: playBoggle
 * --------------------
 * Manages all details needed for the user to play one
 * or more games of Boggle.
 */
static void playBoggle();

static void findWordsHelper(Grid<string>& board, int row, int col, const string& word, Set<string>& words, const Lexicon& english);

static bool isBoggleWord(const string& word, const Lexicon& english);

static void swap(string& s1, string& s2);

static void swap(char& ch1, char& ch2);

/**
 * Function: main
 * --------------
 * Serves as the entry point to the entire program.
 */
int main() {
    GWindow gw(kBoggleWindowWidth, kBoggleWindowHeight);
    initGBoggle(gw);
    welcome();
   // if (getYesOrNo("Do you need instructions?")) giveInstructions();
    do {
        playBoggle();
    } while (getYesOrNo("Would you like to play again?"));
    cout << "Thank you for playing!" << endl;
    shutdownGBoggle();
    return 0;
}

static void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl;
    cout << endl;
}

static void giveInstructions() {
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl;
    cout << endl;
    cout << "Hit return when you're ready...";
    getLine(); // ignore return value
}

static int getPreferredBoardSize() {
    //cout << "You can choose standard Boggle (4x4 grid) or Big Boggle (5x5 grid)." << endl;
    //return getIntegerBetween("Which dimension would you prefer: 4 or 5?", 4, 5);
    return 4;
}

static int calcRandomInteger(int from, int to) {
    // return randomInteger(from, to);
    return from;
}

static void shuffleLetters(string& word) {
    for (int i = 0; i < word.size(); i++) {
        int randomIndex = calcRandomInteger(i, word.size() - 1);
        swap(word[i], word[randomIndex]);
    }
}

static void shuffleCubes(Vector<string>& cubes) {
    int n = cubes.size();

    for (int i = 0; i < n; i++) {
        int randIndex = calcRandomInteger(i, n);
        swap(cubes[i], cubes[randIndex]);
        shuffleLetters(cubes[i]);
        shuffleLetters(cubes[randIndex]);
    }
}

static string faceLetter(const string& cube) {
    if (cube.length() == 0) throw "faceLetter: word must consists of 6 letters";

    return cube.substr(0, 1);
}

static void initBoard(Grid<string>& board, int dimension, const Vector<string>& cubes) {
    for (int i = 0; i < cubes.size(); i++) {
        int row = i / dimension;
        int col = i % dimension;

        board[row][col] = faceLetter(cubes[i]);
    }
}

static void chooseFindAndUnchoose(Grid<string>& board, int row, int col, const string& word, Set<string>& words, const Lexicon& english) {
    string letter = board[row][col];
    board[row][col] = " ";
    findWordsHelper(board, row, col, word + letter, words, english);
    board[row][col] = letter;
}

static void findWordsHelper(Grid<string>& board, int row, int col, const string& word, Set<string>& words, const Lexicon& english) {
    if (!english.containsPrefix(word)) {
        return;
    }

    if (isBoggleWord(word, english)) {
        words.add(word);
    }

    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = col - 1; c <= col + 1; c++) {
            if (board.inBounds(r, c) && board[r][c] != " ") {
                chooseFindAndUnchoose(board, r, c, word, words, english);
            }
        }
     }
}

static void findAllWorlds(Grid<string>& board, Set<string>& words, const Lexicon& english) {
    for (int r = 0; r < board.height(); r++) {
        for (int c = 0; c < board.width(); c++) {
            chooseFindAndUnchoose(board, r, c, "", words, english);
        }
    }
}

static void playBoggle() {
    int dimension = getPreferredBoardSize();
    drawBoard(dimension, dimension);

    Vector<string> cubes;
    Grid<string> board(dimension, dimension);

    for (string cube: kStandardCubes) {
        cubes += cube;
    }

    shuffleCubes(cubes);
    initBoard(board, dimension, cubes);

    cout << board.toString2D() << endl << endl;

    Lexicon english("dictionary.txt");

    auto start = std::chrono::high_resolution_clock::now();

    Set<string> words;
    findAllWorlds(board, words, english);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << duration.count() << endl;
    cout << words << endl;
}

static bool isBoggleWord(const string& word, const Lexicon& english) {
    return word.length() >= kMinLength
            && english.contains(word);
}

static void swap(string& s1, string& s2) {
    string temp = s1;
    s1 = s2;
    s2 = temp;
}

static void swap(char& ch1, char& ch2) {
    char temp = ch1;
    ch1 = ch2;
    ch2 = temp;
}
