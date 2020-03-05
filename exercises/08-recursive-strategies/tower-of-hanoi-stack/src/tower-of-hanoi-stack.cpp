/*
 * File: tower-of-hanoi.cpp
 * ------------------------
 * This program solves the Tower of Hanoi puzzle.
 */

#include <iostream>
#include "stack.h"
#include "console.h"

using namespace std;

struct Task {
    int height;
    char start;
    char finish;
    char tmp;
};

void moveTower(int height, char start, char finish, char tmp);
void moveSingleDisk(char start, char finish);

void moveTower(Stack<Task>& tasks);

int main() {
    moveTower(3, 'A', 'B', 'C');

    cout << endl << endl;

    Stack<Task> tasks { Task { 3, 'A', 'B', 'C' } };
    moveTower(tasks);

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

void moveTower(Stack<Task>& tasks) {
    while (!tasks.isEmpty()) {
        auto task = tasks.pop();

        if (task.height == 1) {
            moveSingleDisk(task.start, task.finish);
        } else {
            tasks.push(Task { task.height - 1, task.tmp, task.finish, task.start });
            tasks.push(Task { 1, task.start, task.finish, task.tmp });
            tasks.push(Task { task.height - 1, task.start, task.tmp, task.finish });
        }

    }
}
