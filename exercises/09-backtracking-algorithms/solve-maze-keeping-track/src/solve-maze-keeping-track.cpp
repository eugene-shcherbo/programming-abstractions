#include <iostream>

#include "gwindow.h"
#include "maze.h"
#include "console.h"
#include "direction.h"

using namespace std;

bool findSolutionPath(Maze& maze, Point start, Vector<Point>& path);
Point adjacentPoint(Point start, Direction dir);

int main() {
    GWindow gw;
    Maze maze("SampleMaze.txt", gw);

    Vector<Point> path;
    findSolutionPath(maze, maze.getStartPosition(), path);

    maze = Maze("SampleMaze.txt", gw);

    for (Point pt: path) {
       maze.markSquare(pt);
    }

    char ch;
    cin.get(ch);

    gw.close();

    return 0;
}

bool findSolutionPath(Maze& maze, Point start, Vector<Point>& path) {
    if (maze.isOutside(start)) return true;
    if (maze.isMarked(start)) return false;

    maze.markSquare(start);
    path.add(start);

    for (Direction dir = NORTH; dir <= WEST; dir++) {
        if (!maze.wallExists(start, dir)) {
            Point pt = adjacentPoint(start, dir);

            if (findSolutionPath(maze, pt, path)) {
                return true;
            }
        }
    }

    path.removeBack();

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


