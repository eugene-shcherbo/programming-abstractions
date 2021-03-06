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

static const int kStandardBoardDimension = 4;
static const int kBigBoardDimension = 5;

static const string kStandardCubes[kStandardBoardDimension * kStandardBoardDimension] = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

static const string kBigBoggleCubes[kBigBoardDimension * kBigBoardDimension] = {
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
static void playBoggle(Lexicon& english);

static void preconfigureBoard(Grid<char>& board, int dimension);

static void fillCubesWithUserConfiguration(Vector<string>& cubes, int size);

static void fillCubes(Vector<string>& cubes, const string config[], int size);

static void shuffleCubes(Vector<string>& cubes);

static void shuffleLetters(string& word);

static char faceLetter(const string& cube);

static void drawCubeBoard(const Grid<char>& board);

static void findAllWorlds(const Grid<char>& board, Set<string>& words, const Lexicon& english);

static void findWordsHelper(const Grid<char>& board, int row, int col, const string& word,
                            Set<string>& words, const Lexicon& english, Grid<bool>& visited);

static bool isBoggleWord(const string& word, const Lexicon& english);

static void humanTurn(const Grid<char>& board, const Set<string>& words, const Lexicon& english, Set<string>& userWords);

static void findHumanPath(const Grid<char>& board, Vector<int>& path, const string& word);

static bool findHumanPathHelper(const Grid<char>& board, Vector<int>& path, int row, int col, const string& word);

static void showHumanPath(Vector<int>& path, int dimension);

static void computerTurn(const Set<string> words, const Set<string>& userWords);

/**
 * Function: main
 * --------------
 * Serves as the entry point to the entire program.
 */
int main() {
    Lexicon english("dictionary.txt");
    GWindow gw(kBoggleWindowWidth, kBoggleWindowHeight);
    initGBoggle(gw);
    welcome();

    if (getYesOrNo("Do you need instructions?")) giveInstructions();

    do {
        playBoggle(english);
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

static void playBoggle(Lexicon& english) {
    int dimension = getPreferredBoardSize();
    drawBoard(dimension, dimension);

    Grid<char> board(dimension, dimension);
    preconfigureBoard(board, dimension);
    drawCubeBoard(board);

    Set<string> words;
    findAllWorlds(board, words, english);

    Set<string> userWords;
    humanTurn(board, words, english, userWords);
    computerTurn(words, userWords);
}

static int getPreferredBoardSize() {
    cout << "You can choose standard Boggle (4x4 grid) or Big Boggle (5x5 grid)." << endl;
    return getIntegerBetween("Which dimension would you prefer: 4 or 5?", 4, 5);
}

static void preconfigureBoard(Grid<char>& board, int dimension) {
    cout << "I'll give you a chance to set up the board to your specification,"
         << "which makes it easier to confirm your boggle program is working."
         << endl;
    bool isUserSetup = getYesOrNo("Do you want to force the board configuration?");

    Vector<string> cubes;

    if (isUserSetup) {
        fillCubesWithUserConfiguration(cubes, dimension * dimension);
    } else if (dimension == kStandardBoardDimension) {
        fillCubes(cubes, kStandardCubes, dimension * dimension);
    } else if (dimension == kBigBoardDimension) {
        fillCubes(cubes, kBigBoggleCubes, dimension * dimension);
    }

    for (int i = 0; i < cubes.size(); i++) {
        int row = i / dimension;
        int col = i % dimension;
        board[row][col] = faceLetter(cubes[i]);
    }
}

static void fillCubesWithUserConfiguration(Vector<string>& cubes, int size) {
    int dimension = sqrt(size);

    cout << "Enter a " << size << "-character string to identify which letters you want on the cubes." << endl;
    cout << "The first "
         << dimension
         << " characters form the top row, the next "
         << dimension
         << " characters form the second row, and so forth." << endl;

    string cubesConfig = getLine("Enter a string: ");

    while (cubesConfig.length() != size) {
        cout << "Enter a string that's precisely " << size << " characters long." << endl;
        cubesConfig = getLine("Try again: ");
    }

    for (char c: cubesConfig) {
        cubes += string(1, c);
    }
}

static void fillCubes(Vector<string>& cubes, const string config[], int size) {
    for (int i = 0; i < size; i++) {
        cubes += config[i];
    }

    shuffleCubes(cubes);
}

static void shuffleCubes(Vector<string>& cubes) {
    int n = cubes.size();

    for (int i = 0; i < n; i++) {
        int randIndex = randomInteger(i, n - 1);
        swap(cubes[i], cubes[randIndex]);
        shuffleLetters(cubes[i]);
        shuffleLetters(cubes[randIndex]);
    }
}

static void shuffleLetters(string& word) {
    size_t n = word.size();

    for (size_t i = 0; i < n; i++) {
        size_t randomIndex = randomInteger(i, n - 1);
        swap(word[i], word[randomIndex]);
    }
}

static char faceLetter(const string& cube) {
    if (cube.length() == 0) throw "faceLetter: word must consists of 6 letters";

    return cube[0];
}


static void drawCubeBoard(const Grid<char>& board) {
    for (int r = 0; r < board.height(); r++) {
        for (int c = 0; c < board.width(); c++) {
            labelCube(r, c, board[r][c]);
        }
    }
}

static void findAllWorlds(const Grid<char>& board, Set<string>& words, const Lexicon& english) {
    Grid<bool> visited(board.height(), board.width());

    for (int r = 0; r < board.height(); r++) {
        for (int c = 0; c < board.width(); c++) {
            findWordsHelper(board, r, c, "", words, english, visited);
        }
    }
}

static void findWordsHelper(const Grid<char>& board, int row, int col, const string& word,
                            Set<string>& words, const Lexicon& english, Grid<bool>& visited) {

    if (!english.containsPrefix(word)) return;
    if (isBoggleWord(word, english)) words.add(word);

    visited[row][col] = true;

    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = col - 1; c <= col + 1; c++) {
            if (board.inBounds(r, c) && !visited[r][c]) {
                findWordsHelper(board, r, c, word + board[r][c], words, english, visited);
            }
        }
     }

    visited[row][col] = false;
}

static bool isBoggleWord(const string& word, const Lexicon& english) {
    return word.length() >= kMinLength
            && english.contains(word);
}

static void humanTurn(const Grid<char>& board, const Set<string>& words, const Lexicon& english, Set<string>& userWords) {
    while (true) {
        string word = getLine("Enter a word: ");

        if (word.empty()) {
            break;
        } else if (word.length() < kMinLength) {
            cout << "Sorry, that isn't long enough to even be considered." << endl;
        } else if (userWords.contains(word)) {
            cout << "You've already guessed that word." << endl;
        } else if (!english.contains(word)) {
            cout << "Sorry, that isn't even a word." << endl;
        } else if (!words.contains(word)) {
            cout << "Sorry, that word can't be constructed with this board." << endl;
        } else {
            Vector<int> humanPath;
            userWords.add(word);
            recordWordForPlayer(word, HUMAN);
            findHumanPath(board, humanPath, word);
            showHumanPath(humanPath, board.width());
        }
    }
}

static void findHumanPath(const Grid<char>& board, Vector<int>& path, const string& word) {
    for (int r = 0; r < board.height(); r++) {
        for (int c = 0; c < board.width(); c++) {
            if (findHumanPathHelper(board, path, r, c, word)) {
                return;
            }
        }
    }
}

static bool findHumanPathHelper(const Grid<char>& board, Vector<int>& path, int row, int col, const string& word) {
    if (word.empty()) return true;

    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = col - 1; c <= col + 1; c++) {
            int i = r * board.height() + c;

            if (board.inBounds(r, c) && !path.contains(i) && board[r][c] == word[0]) {
                path.add(i);

                if (findHumanPathHelper(board, path, r, c, word.substr(1))) {
                    return true;
                }

                path.removeBack();
            }
        }
    }

    return false;
}

static void showHumanPath(Vector<int>& path, int dimension) {
    for (int pathItem : path) {
        int row = pathItem / dimension;
        int col = pathItem % dimension;
        highlightCube(row, col, true);
        pause(kDelayBetweenHighlights);
    }

    pause(kDelayAfterAllHighlights);

    for (int i = path.size() - 1; i >= 0; i--) {
        int row = path[i] / dimension;
        int col = path[i] % dimension;
        highlightCube(row, col, false);
        pause(kDelayBetweenHighlights);
    }
}

static void computerTurn(const Set<string> words, const Set<string>& userWords) {
    Set<string> remainingWords = words - userWords;

    for (string word : remainingWords) {
        recordWordForPlayer(word, COMPUTER);
    }
}
