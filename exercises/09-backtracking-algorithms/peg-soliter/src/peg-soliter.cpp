#include <iostream>
#include "grid.h"
#include "console.h"
#include "direction.h"
#include "vector.h"

using namespace std;

const int BOARD_SIZE = 7;

enum State {
    EMPTY = 0,
    PEG,
    HOLE
};

void initBoard(Grid<State>& board);
bool pegSolitaire(Grid<State>& board);
bool canJump(const Grid<State>& board, Point point, Direction dir);
bool hasPegInDirection(const Grid<State>& board, Point pt, Direction dir);
void jump(Grid<State>& board, Point src, Direction dir, State srcVal, State betweenVal, State destVal);
int pegsNumber(const Grid<State>& board);
void getHoles(const Grid<State>& board, Vector<Point>& holes);
Point adjacentPoint(Point pt, Direction dir);
Point getBetweenPoint(Point pt, Direction dir);

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
    if (pegsNumber(board) == 1 && board[3][3] == PEG) return true;

    Vector<Point> holes;
    getHoles(board, holes);

    for (int i = holes.size() - 1; i >= 0; i--) {
        for (Direction dir = NORTH; dir <= WEST; dir++) {
            if (canJump(board, holes[i], dir)) {
                jump(board, holes[i], dir, PEG, HOLE, HOLE);

                if (pegSolitaire(board)) {
                    return true;
                }

                jump(board, holes[i], dir, HOLE, PEG, PEG);
            }
        }
    }

    return false;
}

bool canJump(const Grid<State>& board, Point source, Direction dir) {
    Point dest = adjacentPoint(source, dir);

    return board.inBounds(dest.getY(), dest.getX())
            && board[dest.getY()][dest.getX()] == PEG
            && hasPegInDirection(board, source, dir);
}

bool hasPegInDirection(const Grid<State>& board, Point pt, Direction dir) {
    Point between = getBetweenPoint(pt, dir);
    return board[between.getY()][between.getX()] == PEG;
}


void jump(Grid<State>& board, Point source, Direction dir, State srcVal, State betweenVal, State destVal) {
    Point dest = adjacentPoint(source, dir);
    Point between = getBetweenPoint(source, dir);

    board[source.getY()][source.getX()] = srcVal;
    board[between.getY()][between.getX()] = betweenVal;
    board[dest.getY()][dest.getX()] = destVal;
}

Point adjacentPoint(Point pt, Direction dir) {
    switch (dir) {
        case NORTH: return Point(pt.getX(), pt.getY() - 2);
        case SOUTH: return Point(pt.getX(), pt.getY() + 2);
        case WEST: return Point(pt.getX() - 2, pt.getY());
        case EAST: return Point(pt.getX() + 2, pt.getY());
    }
    return pt;
}

Point getBetweenPoint(Point pt, Direction dir) {
    switch (dir) {
        case NORTH: return Point(pt.getX(), pt.getY() - 1);
        case SOUTH: return Point(pt.getX(), pt.getY() + 1);
        case WEST: return Point(pt.getX() - 1, pt.getY());
        case EAST: return Point(pt.getX() + 1, pt.getY());
    }
    return pt;
}

int pegsNumber(const Grid<State>& board) {
    int res = 0;

    for (State el: board) {
        if (el == PEG)
            res++;
    }

    return res;
}

void getHoles(const Grid<State>& board, Vector<Point>& holes) {
    for (int r = 0; r < board.height(); r++) {
        for (int c = 0; c < board.width(); c++) {
            if (board[r][c] == HOLE) {
                holes.add(Point(c, r));
            }
        }
    }
}
