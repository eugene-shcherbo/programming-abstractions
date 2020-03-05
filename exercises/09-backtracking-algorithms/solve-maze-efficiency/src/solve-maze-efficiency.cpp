#include <iostream>

#include "gwindow.h"
#include "maze.h"
#include "console.h"
#include "direction.h"

using namespace std;

bool solveMaze(Maze& maze, Point start, int& recursiveCalls, bool unmark = false);
Point adjacentPoint(Point start, Direction dir);

int main() {
    GWindow gw;
    Maze maze("RecursiveMaze.txt", gw);

    int recursiveCalls = 0;
    solveMaze(maze, maze.getStartPosition(), recursiveCalls, true);

    cout << "With unmark operation there are " << recursiveCalls << " recursive calls" << endl;

    recursiveCalls = 0;
    maze = Maze("RecursiveMaze.txt", gw);
    solveMaze(maze, maze.getStartPosition(), recursiveCalls, false);

    cout << "Without unmark operation there are " << recursiveCalls << " recursive calls" << endl;

    char ch;
    cin.get(ch);

    gw.close();

    return 0;
}

bool solveMaze(Maze& maze, Point start, int& recursiveCalls, bool unmark) {
    recursiveCalls++;

    if (maze.isOutside(start)) return true;
    if (maze.isMarked(start)) return false;

    maze.markSquare(start);

    for (Direction dir = NORTH; dir <= WEST; dir++) {
        if (!maze.wallExists(start, dir)) {
            if (solveMaze(maze, adjacentPoint(start, dir), recursiveCalls, unmark)) {
                return true;
            }
        }
    }

    if (unmark) maze.unmarkSquare(start);

    return false;
}

Point adjacentPoint(Point start, Direction dir) {
    switch (dir) {
        case NORTH: return Point(start.getX(), start.getY() - 1);
        case EAST: return Point(start.getX() + 1, start.getY());
        case SOUTH: return Point(start.getX(), start.getY() + 1);
        case WEST: return Point(start.getX() - 1, start.getY());
    }
}


