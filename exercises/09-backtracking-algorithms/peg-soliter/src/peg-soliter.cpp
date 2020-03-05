#include <iostream>
#include "grid.h"
#include "console.h"
#include "direction.h"
#include "vector.h"

using namespace std;

const int BOARD_SIZE = 7;
const int N_CELLS = 33;

enum State {
    EMPTY = 0,
    PEG,
    HOLE
};

void initBoard(Grid<State>& board);
bool pegSolitaire(Grid<State>& board);
bool pegSolitairHelper(Grid<State>& board, Vector<Point> holes);
bool canJumpToHole(const Grid<State>& board, const Point& point, const Direction& dir);
Point adjacentPoint(const Point& pt, const Direction& dir);
Point getBetweenPoint(const Point& pt, const Direction& dir);
bool hasPegInDirection(const Grid<State>& board, const Point& pt, const Direction& dir);
void jump(Grid<State>& board, Vector<Point>& holes, const Point& source, const Direction& dir);
void jumpBack(Grid<State>& board, Vector<Point>& holes, const Point& source, const Direction& dir);

int main() {
    Grid<State> board(BOARD_SIZE, BOARD_SIZE);
    initBoard(board);

    if (pegSolitaire(board)) {
        cout << board.toString2D() << endl;
    } else {
        cout << "No solutions" << endl;
    }

    return 0;
}

void initBoard(Grid<State>& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 2; j < 5; j++) {
            if (i == j && j == 3) {
                board[i][j] = HOLE;
            } else {
                board[i][j] = PEG;
                board[j][i] = PEG;
            }
        }
    }
}

bool pegSolitaire(Grid<State>& board) {
    Vector<Point> holes { Point(3, 3) };
    return pegSolitairHelper(board, holes);
}

bool pegSolitairHelper(Grid<State>& board, Vector<Point> holes) {
    int n = holes.size();

    if (n == N_CELLS - 1) return true;

    for (int i = n - 1; i >= 0; i--) {
        for (Direction dir = NORTH; dir <= WEST; dir++) {
            if (canJumpToHole(board, holes[i], dir)) {
                Point hole = holes[i];

                jump(board, holes, hole, dir);

                if (pegSolitairHelper(board, holes)) {
                    return true;
                }

                jumpBack(board, holes, hole, dir);
            }
        }
    }

    return false;
}

bool canJumpToHole(const Grid<State>& board, const Point& source, const Direction& dir) {
    Point dest = adjacentPoint(source, dir);

    return board.inBounds(dest.getY(), dest.getX())
            && board[dest.getY()][dest.getX()] == PEG
            && hasPegInDirection(board, source, dir);
}

Point adjacentPoint(const Point& pt, const Direction& dir) {
    switch (dir) {
        case NORTH: return Point(pt.getX(), pt.getY() - 2);
        case SOUTH: return Point(pt.getX(), pt.getY() + 2);
        case WEST: return Point(pt.getX() - 2, pt.getY());
        case EAST: return Point(pt.getX() + 2, pt.getY());
        default: return pt;
    }
}

bool hasPegInDirection(const Grid<State>& board, const Point& pt, const Direction& dir) {
    Point between = getBetweenPoint(pt, dir);
    return board[between.getY()][between.getX()] == PEG;
}

void jump(Grid<State>& board, Vector<Point>& holes, const Point& source, const Direction& dir) {
    Point dest = adjacentPoint(source, dir);
    Point between = getBetweenPoint(source, dir);

    board[dest.getY()][dest.getX()] = HOLE;
    board[between.getY()][between.getX()] = HOLE;
    board[source.getY()][source.getX()] = PEG;

    holes.removeBack();
    holes.add(between);
    holes.add(dest);
}

Point getBetweenPoint(const Point& pt, const Direction& dir) {
    switch (dir) {
        case NORTH: return Point(pt.getX(), pt.getY() - 1);
        case SOUTH: return Point(pt.getX(), pt.getY() + 1);
        case WEST: return Point(pt.getX() - 1, pt.getY());
        case EAST: return Point(pt.getX() + 1, pt.getY());
        default: return pt;
    }
}

void jumpBack(Grid<State>& board, Vector<Point>& holes, const Point& source, const Direction& dir) {
    Point dest = adjacentPoint(source, dir);
    Point between = getBetweenPoint(source, dir);

    board[dest.getY()][dest.getX()] = PEG;
    board[between.getY()][between.getX()] = PEG;
    board[source.getY()][source.getX()] = HOLE;

    holes.removeBack();
    holes.removeBack();
    holes.add(source);
}
