#include <iostream>
#include "grid.h"
#include "console.h"

using namespace std;

const char Q = 'Q';
const char W = 'W';
const char B = 'B';
const int N = 15;

bool placeQueens(Grid<char>& board, int col);
void initChessBoard(Grid<char>& board);
bool isWhiteCell(int row, int col);
bool canPlaceQueen(const Grid<char>& board, int row, int col);

int main() {
    Grid<char> board(N, N);
    initChessBoard(board);

    if (placeQueens(board, 0)) {
        cout << "There is at least one solution to place " << N << " queens on the " << endl;
        cout << board.toString2D() << endl;
    } else {
        cout << "There are no solutions." << endl;
    }

    return 0;
}

bool placeQueens(Grid<char>& board, int col) {
    if (col >= N) return true;

    for (int r = 0; r < N; r++) {
        if (canPlaceQueen(board, r, col)) {
            board[r][col] = Q;

            if (placeQueens(board, col + 1)) {
                return true;
            }

            board[r][col] = isWhiteCell(r, col) ? W : B;
        }
    }

    return false;
}

void initChessBoard(Grid<char>& board) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (isWhiteCell(r, c)) {
                board[r][c] = W;
            } else {
                board[r][c] = B;
            }
        }
    }
}

bool isWhiteCell(int row, int col) {
    return (row + col) % 2 != 0;
}

bool canPlaceQueen(const Grid<char>& board, int row, int col) {
    for (int c = 0; c < col; c++) {
        if (board[row][c] == Q) {
            return false;
        }
    }

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < col; c++) {
            if (r - c == row - col && board[r][c] == Q) {
                return false;
            }

            if (r + c == row + col && board[r][c] == Q) {
                return false;
            }
        }
    }

    return true;
}
