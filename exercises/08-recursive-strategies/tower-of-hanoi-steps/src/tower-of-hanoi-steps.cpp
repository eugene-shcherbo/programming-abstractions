/*
 * File: tower-of-hanoi.cpp
 * ------------------------
 * This program solves the Tower of Hanoi puzzle.
 */

#include <iostream>
#include "console.h"

using namespace std;

void moveTower(int height, char start, char finish, char tmp, int& count);
void moveSingleDisk(char start, char finish, int& count);
int countHanoiMoves(int height);
void testCountHanoiMoves(int height);

int main() {
    testCountHanoiMoves(1);
    testCountHanoiMoves(2);
    testCountHanoiMoves(3);
    testCountHanoiMoves(4);
    testCountHanoiMoves(5);
    testCountHanoiMoves(20);

    return 0;
}

void testCountHanoiMoves(int height) {
    int count = 0;
    moveTower(height, 'A', 'B', 'C', count);

    if (count == countHanoiMoves(height)) {
        cout << "Success." << endl;
    } else {
        cout << "Fail." << endl;
    }
}

void moveTower(int height, char start, char finish, char tmp, int& count) {
    if (height == 1) {
        moveSingleDisk(start, finish, count);
    } else {
        moveTower(height - 1, start, tmp, finish, count);
        moveSingleDisk(start, finish, count);
        moveTower(height - 1, tmp, finish, start, count);
    }
}

void moveSingleDisk(char start, char finish, int& count) {
    ++count;
    cout << start << " -> " << finish << endl;
}

int countHanoiMoves(int height) {
    if (height == 1) {
        return 1;
    } else {
        return 2 * countHanoiMoves(height - 1) + 1;
    }
}
