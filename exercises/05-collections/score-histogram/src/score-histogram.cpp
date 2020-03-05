#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include "vector.h"
#include "strlib.h"
#include "console.h"

using namespace std;

constexpr int DELTA = 10;
constexpr int MAX_SCORE_RANGE = 100;
constexpr int MIN_SCORE_RANGE = 0;

void readScores(const string& filename, Vector<int>& scores);
void displayHistogram(const Vector<int>& scores);
int countScoresInRange(const Vector<int>& scores, int range);
void printRange(int range);
void printScores(int n);

int main() {
    Vector<int> scores;

    readScores("scores.txt", scores);
    displayHistogram(scores);

    return 0;
}

void readScores(const string& filename, Vector<int>& scores) {
    ifstream infile(filename);

    if (infile.fail()) {
        error("Can't open the file named \"" + filename + "\".");
    }

    char ch;
    string num;

    while (infile.get(ch)) {
        if (isdigit(ch)) {
            num += ch;
        } else if (ch == ',') {
            scores.add(stringToInteger(num));
            num = "";
        }
    }

    if (!num.empty()) {
        scores.add(stringToInteger(num));
    }

    infile.close();
}

void displayHistogram(const Vector<int>& scores) {
    for (int i = MIN_SCORE_RANGE; i <= MAX_SCORE_RANGE; i += DELTA) {
        printRange(i);
        printScores(countScoresInRange(scores, i));
    }
}

int countScoresInRange(const Vector<int>& scores, int range) {
    int res = 0;
    for (int score: scores) {
        if (score >= range && score < range + DELTA) {
            ++res;
        }
    }
    return res;
}

void printRange(int range) {
    cout << setw(2) << setfill('0') << range;

    if (range < 100) {
        cout << "s";
    }

    cout << ": ";
}

void printScores(int n) {
    for (int i = 0; i < n; ++i) {
        cout << "*";
    }
    cout << endl;
}
