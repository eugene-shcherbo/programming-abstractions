/*
 * File: tower-of-hanoi.cpp
 * ------------------------
 * This program solves the Tower of Hanoi puzzle.
 */

#include <iostream>
#include "console.h"

using namespace std;

void moveTower(int height, char start, char finish, char tmp);
void moveSingleDisk(char start, char finish);

int main() {
    moveTower(2, 'A', 'B', 'C');

    return 0;
}

void moveTower(int height, char start, char finish, char tmp) {
    if (height > 0) {
        moveTower(height - 1, start, tmp, finish);
        moveSingleDisk(start, finish);
        moveTower(height - 1, tmp, finish, start);
    }
}

void moveSingleDisk(char start, char finish) {
    cout << start << " -> " << finish << endl;
}
