/*
 * File: main.cpp
 * --------------
 * This program displays an average score of a group of students.
 * The end of the input is indicating by entering a sentitel value,
 * which is defined by setting the value of the constant SENTITEL.
 */

#include <iostream>
using namespace std;

/*
 * Constant: SENTITEL
 * ------------------
 * This constant defines the value used to terminate the input
 * list and should therefore not be a value one would want to
 * include as a data value.
 */

constexpr int SENTITEL = -1;

/* Main Program */

int main()
{
    cout << "This program displays an average score of a group of students" << endl;
    cout << "Use " << SENTITEL << " to signal the end." << endl;

    int total = 0;
    int numberOfScores = 0;
    while (true) {
        int value;
        cout << " ? ";
        cin >> value;
        if (value == SENTITEL) break;
        total += value;
        numberOfScores++;
    }

    cout << "The average score is " << static_cast<double>(total) / numberOfScores << endl;

    return 0;
}
