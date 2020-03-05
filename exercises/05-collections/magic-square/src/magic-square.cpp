#include <iostream>
#include "grid.h"
#include "console.h"

using namespace std;

bool isMagicSquare(const Grid<int>& square);
void testMagicSquare(const Grid<int>& square, bool expected);
int getFirstRowSum(const Grid<int>& square);
bool isSumInRowsAndColumnsEqualsTo(const Grid<int>& square, int sum);
bool isSumInDiagonalsEqualsTo(const Grid<int>& square, int sum);

int main() {
    testMagicSquare(
                Grid<int> {
                    {8, 1, 6},
                    {3, 5, 7},
                    {4, 9, 2}
                }, true);

    testMagicSquare(
                Grid<int> {
                    {16, 3, 2, 13},
                    {5, 10, 11, 8},
                    {9, 6, 7, 12},
                    {4, 15, 14, 1}
                }, true);

    testMagicSquare(
                Grid<int> {
                    {1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9}
                }, false);

    testMagicSquare(
                Grid<int> {
                    {1, 2},
                    {3, 4},
                    {5, 6}
                }, false);

    return 0;
}

void testMagicSquare(const Grid<int>& square, bool expected) {
    bool actual = isMagicSquare(square);

    cout << "The grid " << square << " is " << (actual ? "" : "not ")
         << "a magic square." << endl;
    cout << "Result: " << (actual == expected ? "SUCCESS." : "FAILED.")
         << endl << endl;
}

bool isMagicSquare(const Grid<int>& square) {
    int rows = square.height();
    int cols = square.width();

    if (rows != cols) {
        return false;
    }

    int sum = getFirstRowSum(square);

    return isSumInRowsAndColumnsEqualsTo(square, sum)
            && isSumInDiagonalsEqualsTo(square, sum);
}

int getFirstRowSum(const Grid<int>& square) {
    int sum = 0;

    for (int i = 0; i < square.numCols(); ++i) {
        sum += square[0][i];
    }

    return sum;
}

bool isSumInRowsAndColumnsEqualsTo(const Grid<int>& square, int sum) {
    int rows = 0;
    int cols = 0;

    int dimension = square.numRows();

    for (int i = 0; i < dimension; ++i) {
        rows = 0;
        cols = 0;

        for (int j = 0; j < dimension; ++j) {
            rows += square[i][j];
            cols += square[j][i];
        }

        if (rows != sum || cols != sum) {
            return false;
        }
    }

    return true;
}

bool isSumInDiagonalsEqualsTo(const Grid<int>& square, int sum) {
    int mainDiagonal = 0;
    int secondDiagonal = 0;

    int dimension = square.numRows();

    for (int i = 0; i < dimension; ++i) {
        mainDiagonal += square[i][i];
        secondDiagonal += square[i][square.numCols() - 1 - i];
    }

    return  mainDiagonal == secondDiagonal
            && secondDiagonal == sum;
}
