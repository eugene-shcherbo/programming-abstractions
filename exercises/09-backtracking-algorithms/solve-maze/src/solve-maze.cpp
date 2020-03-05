#include <iostream>

#include "gwindow.h"
#include "maze.h"
#include "console.h"
#include "direction.h"

using namespace std;

bool solveMaze(Maze& maze, Point start);
Point adjacentPoint(Point start, Direction dir);

int main() {
    GWindow gw;
    Maze maze("SampleMaze.txt", gw);

    if (solveMaze(maze, maze.getStartPosition())) {
        cout << "The marked path is a solution." << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    char ch;
    cin.get(ch);

    gw.close();

    return 0;
}

bool solveMaze(Maze& maze, Point start) {
    if (maze.isOutside(start)) return true;
    if (maze.isMarked(start)) return false;

    maze.markSquare(start);

    for (Direction dir = NORTH; dir <= WEST; dir++) {
        if (!maze.wallExists(start, dir)) {
            if (solveMaze(maze, adjacentPoint(start, dir))) {
                return true;
            }
        }
    }

    maze.unmarkSquare(start);

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


