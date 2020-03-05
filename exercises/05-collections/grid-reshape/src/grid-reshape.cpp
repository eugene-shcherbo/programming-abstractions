#include <iostream>
#include "grid.h"
#include "console.h"

using namespace std;

void reshape(Grid<int>& grid, int nRows, int nCols);
void testReshape(const Grid<int>& grid, int nRows, int nCols, const Grid<int>& expected);

int main() {
    Grid<int> initialGrid = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    testReshape(initialGrid, 4, 3,
                Grid<int> {
                    {1, 2, 3},
                    {4, 5, 6},
                    {7, 8, 9},
                    {10, 11, 12}
                });

    testReshape(initialGrid, 2, 5,
                Grid<int> {
                    {1, 2, 3, 4, 5},
                    {6, 7, 8, 9, 10}
                });

    testReshape(initialGrid, 3, 5,
                Grid<int> {
                    {1, 2, 3, 4, 5},
                    {6, 7, 8, 9, 10},
                    {11, 12, 0, 0, 0}
                });

    return 0;
}

void testReshape(const Grid<int>& grid, int nRows, int nCols, const Grid<int>& expected) {
    Grid<int> actual = grid;
    reshape(actual, nRows, nCols);

    cout << "Result: " << (actual == expected ? "Success." : "Fail.") << endl << endl;
}

void reshape(Grid<int>& grid, int nRows, int nCols) {
    Vector<int> items;

    for (int val: grid) {
        items.add(val);
    }

    grid.resize(nRows, nCols);

    for (int i = 0; i < items.size(); ++i) {
        int row = i / nCols;
        int col = i % nCols;

        if (!grid.inBounds(row, col)) {
            break;
        }

        grid[row][col] = items[i];
    }
}
