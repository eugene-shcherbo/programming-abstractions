/*
 * File: tower-of-hanoi.cpp
 * ------------------------
 * This program solves the Tower of Hanoi puzzle.
 */

#include <iostream>
#include "console.h"

using namespace std;


/**
 * Function: moveTower
 * -------------------
 * Moves a tower of size height from the start spire to the finish
 * spire using the tmp spire as the temporary repository.
 */
void moveTower(int height, char start, char finish, char tmp);

/**
 * Function: moveSingleDisk
 * ------------------------
 * Executes the transfer of a single disk from the start spire to the
 * finish spire. In this implementation, the move is simply displayed
 * on the console; in a graphical implementation, the code would update
 * the graphics window to show the new arrangement.
 */
void moveSingleDisk(char start, char finish);

int main() {
    moveTower(5, 'A', 'B', 'C');

    return 0;
}

void moveTower(int height, char start, char finish, char tmp) {
    if (height == 1) {
        moveSingleDisk(start, finish);
    } else {
        moveTower(height - 1, start, tmp, finish);
        moveSingleDisk(start, finish);
        moveTower(height - 1, tmp, finish, start);
    }
}

void moveSingleDisk(char start, char finish) {
    cout << start << " -> " << finish << endl;
}
