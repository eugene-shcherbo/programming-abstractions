#include <iostream>
#include "grid.h"
#include "console.h"

using namespace std;

const int BORD_SIZE = 4;
const int NO_MOVE = -1;

bool findKnightTour(int step, Grid<int>& board, int row, int col, const int* xMoves, const int* yMoves);
bool findKnightTour(Grid<int>& board, int row, int col);
bool canKnightMove(int row, int col, const Grid<int>& board);
void initBoard(Grid<int>& board);

int main() {
    Grid<int> board(BORD_SIZE, BORD_SIZE);
    initBoard(board);

    if (findKnightTour(board, 0, 0)) {
        cout << "Knight's tour: " << endl;
        cout << board.toString2D() << endl;
    } else {
        cout << "There are no solutions to the problem." << endl;
    }

    return 0;
}

bool findKnightTour(Grid<int>& board, int row, int col) {
    board[0][0] = 1;
    int xMoves[] = {  2, 1, -1, -2, -2, -1,  1,  2 };
    int yMoves[] = {  1, 2,  2,  1, -1, -2, -2, -1 };
    return findKnightTour(1, board, row, col, xMoves, yMoves);
}

bool findKnightTour(int step, Grid<int>& board, int row, int col, const int* xMoves, const int* yMoves) {
    if (step == BORD_SIZE * BORD_SIZE) return true;

    for (int i = 0; i < 8; i++) {
        int r = row + yMoves[i];
        int c = col + xMoves[i];

        if (canKnightMove(r, c, board)) {
            board[r][c] = step + 1;

            if (findKnightTour(step + 1, board, r, c, xMoves, yMoves)) {
                return true;
            }

            board[r][c] = NO_MOVE;
        }
    }

    return false;
}

bool canKnightMove(int row, int col, const Grid<int>& board) {
    return board.inBounds(row, col) && board[row][col] == NO_MOVE;
}

void initBoard(Grid<int>& board) {
    for (int& el: board) {
        el = NO_MOVE;
    }
}
