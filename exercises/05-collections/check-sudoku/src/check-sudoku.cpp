#include <iostream>
#include "grid.h"
#include "set.h"
#include "console.h"

using namespace std;

constexpr int SUDOKU_SIZE = 9;

bool checkSudokuSolution(const Grid<int>& puzzle);
void testCheckSudokuSolution(const Grid<int>& puzzle, bool expected);
bool isRowValid(const Grid<int>& puzzle, int rowNum);
bool isColValid(const Grid<int>& puzzle, int colNum);
bool isSquareValid(const Grid<int>& puzzle, int rowNum);

int main() {
    Grid<int> validSudoku = {
        {3, 9, 2,/**/4, 6, 5,/**/8, 1, 7},
        {7, 4, 1,/**/8, 9, 3,/**/6, 2, 5},
        {6, 8, 5,/**/2, 7, 1,/**/4, 3, 9},
        // ------------------------------
        {2, 5, 4,/**/1, 3, 8,/**/7, 9, 6},
        {8, 3, 9,/**/6, 2, 7,/**/1, 5, 4},
        {1, 7, 6,/**/9, 5, 4,/**/2, 8, 3},
        // -------------------------------
        {9, 6, 7,/**/5, 8, 2,/**/3, 4, 1},
        {4, 2, 3,/**/7, 1, 9,/**/5, 6, 8},
        {5, 1, 8,/**/3, 4, 6,/**/9, 7, 2}
    };

    Grid<int> invalidSudoku = {
        {3, 9, 2,/**/4, 5, 6,/**/8, 1, 7},
        {7, 4, 1,/**/8, 9, 3,/**/6, 2, 5},
        {6, 8, 5,/**/2, 7, 1,/**/4, 3, 9},
        // ------------------------------
        {2, 5, 4,/**/1, 3, 8,/**/7, 9, 6},
        {8, 3, 9,/**/6, 2, 7,/**/1, 5, 4},
        {1, 7, 6,/**/9, 5, 4,/**/2, 8, 3},
        // -------------------------------
        {9, 6, 7,/**/5, 8, 2,/**/3, 4, 1},
        {4, 2, 3,/**/7, 1, 9,/**/5, 6, 8},
        {5, 1, 8,/**/3, 4, 6,/**/9, 7, 2}
    };

    testCheckSudokuSolution(validSudoku, true);
    testCheckSudokuSolution(invalidSudoku, false);

    return 0;
}

void testCheckSudokuSolution(const Grid<int>& puzzle, bool expected) {
    bool actual = checkSudokuSolution(puzzle);
    cout << "Puzzle " << puzzle.toString2D() << endl;
    cout << " is solved " << (actual ? "" : "not ") << "correctly." << endl;
    cout << "Result: " << (actual == expected ? "SUCCESS." : "FAILED.") << endl;
}

bool checkSudokuSolution(const Grid<int>& puzzle) {
    for (int i = 0; i < SUDOKU_SIZE; ++i) {
        bool isSudokuItemValid = isRowValid(puzzle, i)
                && isSquareValid(puzzle, i)
                && isColValid(puzzle, i);

        if (!isSudokuItemValid) {
            return false;
        }
    }

    return true;
}

bool isRowValid(const Grid<int>& puzzle, int rowNum) {
    Set<int> items;

    for (int i = 0; i < SUDOKU_SIZE; ++i) {
        items.add(puzzle[rowNum][i]);
    }

    return items.size() == SUDOKU_SIZE;
}

bool isColValid(const Grid<int>& puzzle, int colNum) {
    Set<int> items;

    for (int i = 0; i < SUDOKU_SIZE; ++i) {
        items.add(puzzle[i][colNum]);
    }

    return items.size() == SUDOKU_SIZE;
}

bool isSquareValid(const Grid<int>& puzzle, int squareNum) {
    Set<int> items;

    int rowNum = (squareNum / 3) * 3;
    int colNum = (squareNum % 3) * 3;

    for (int r = rowNum; r < rowNum + 3; ++r) {
        for (int c = colNum; c < colNum + 3; ++c) {
            items.add(puzzle[r][c]);
        }
    }

    return items.size() == SUDOKU_SIZE;
}
