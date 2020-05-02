#include <iostream>
#include "strlib.h"
#include "simpio.h"
#include "console.h"

using namespace std;

constexpr int MAX_JUDGES = 100;
constexpr double MIN_SCORE = .0;
constexpr double MAX_SCORE = 10.0;

int fillScores(double scores[]);
double average(double scores[], int n, double& minVal, double& maxVal);

int main() {
    double minVal, maxVal;
    double scores[MAX_JUDGES];
    int numScores = fillScores(scores);
    double avg = average(scores, numScores, minVal, maxVal);

    cout << "The average after eliminating " << minVal << " and " << maxVal << " is " << avg << endl;

    return 0;
}

int fillScores(double scores[]) {
    cout << "Enter score for each judge in the range " << MIN_SCORE << " to " << MAX_SCORE << endl;
    cout << "Enter a blank line to signal the end of the list." << endl;

    int num = 0;

    while (true) {
        string line = getLine("Judge #" + integerToString(num + 1));

        if (line.empty() || num == MAX_JUDGES) {
            break;
        }

        if (!stringIsReal(line)) {
            cout << "Illegal integer format. Try again." << endl;
        } else {
            double score = stringToDouble(line);

            if (score >= MIN_SCORE && score <= MAX_SCORE) {
                scores[num++] = score;
            } else {
                cout << "The value should be in the range " << MIN_SCORE << " to " << MAX_SCORE << ". Try again." << endl;
            }
        }
    }

    return num;
}

double average(double scores[], int n, double& minVal, double& maxVal) {
    minVal = MAX_SCORE;
    maxVal = MIN_SCORE;
    double sum = 0;

    for (int i = 0; i < n; i++) {
        if (scores[i] < minVal) {
            minVal = scores[i];
        }

        if (scores[i] > maxVal) {
            maxVal = scores[i];
        }

        sum += scores[i];
    }

    return (sum - minVal - maxVal) / (n - 2);
}
