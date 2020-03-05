#include <iostream>
#include "vector.h"
#include "grid.h"
#include "console.h"

using namespace std;

void fillGrid(Grid<int>& grid, const Vector<int>& values);
void testFillGrid(Grid<int>& grid, const Vector<int>& values, const Grid<int>& expected);

int main() {
    Grid<int> matrix(3, 3);

    testFillGrid(matrix,
                 Vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 },
                 Grid<int> { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });

    matrix.resize(1, 5);
    testFillGrid(matrix,
                 Vector<int>{ 1, 2, 3, 4 },
                 Grid<int> { {1, 2, 3, 4, 0 } });
    return 0;
}

void testFillGrid(Grid<int>& grid, const Vector<int>& values, const Grid<int>& expected) {
    fillGrid(grid, values);
    cout << "Grid " << grid << endl;
    cout << "Result: " << (grid == expected ? "SUCCESS." : "FAILED.") << endl << endl;
}

void fillGrid(Grid<int>& grid, const Vector<int>& values) {
    int cols = grid.numCols();
    int rows = grid.numRows();

    for (int i = 0; i < values.size(); ++i) {
        int row = i / cols;
        int cell = i % cols;

        if (row >= rows) {
            break;
        }

        grid[row][cell] = values[i];
    }
}
