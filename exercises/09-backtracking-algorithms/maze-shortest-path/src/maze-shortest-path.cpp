#include <iostream>

#include "gwindow.h"
#include "maze.h"
#include "console.h"
#include "direction.h"

using namespace std;

int shortestPathLength(Maze& maze, Point start, int length = 0);
Point adjacentPoint(Point start, Direction dir);

int main() {
    GWindow gw;
    Maze maze("MultipleSolutionMaze.txt", gw);

    int shortestPath = shortestPathLength(maze, maze.getStartPosition());

    if (shortestPath == -1) {
        cout << "There is no solution for this maze." << endl;
    } else {
        cout << "Shortest path is " << shortestPath << endl;
    }

    char ch;
    cin.get(ch);

    gw.close();

    return 0;
}

int shortestPathLength(Maze& maze, Point start, int length) {
    if (maze.isOutside(start)) return length;
    if (maze.isMarked(start)) return -1;

    maze.markSquare(start);

    int minLenght = -1;

    for (Direction dir = NORTH; dir <= WEST; dir++) {
        if (!maze.wallExists(start, dir)) {
            int currLength = shortestPathLength(maze, adjacentPoint(start, dir), length + 1);

            if (minLenght == -1) {
                minLenght = currLength;
            } else if (currLength > -1 && currLength < minLenght) {
                minLenght = currLength;
            }
        }
    }

    maze.unmarkSquare(start);

    return minLenght;
}

Point adjacentPoint(Point start, Direction dir) {
    switch (dir) {
        case NORTH: return Point(start.getX(), start.getY() - 1);
        case EAST: return Point(start.getX() + 1, start.getY());
        case SOUTH: return Point(start.getX(), start.getY() + 1);
        case WEST: return Point(start.getX() - 1, start.getY());
    }
}


