#include <iostream>
#include "grid.h"
#include "console.h"
using namespace std;

void fixCounts(const Grid<bool>& mines, Grid<int>& counts);
int getAdjacentMines(const Grid<bool>& mines, int row, int col);
void testFixCounts(const Grid<bool>& mines, const Grid<int>& expected);

int main() {

    testFixCounts(Grid<bool> {
                      {true, false, false, false, false, true},
                      {false, false, false, false, false, true},
                      {true, true, false, true, false, true},
                      {true, false, false, false, false, false},
                      {false, false, true, false, false, false},
                      {false, false, false, false, false, false}
                  }, Grid<int> {
                      {1, 1, 0, 0, 2, 2},
                      {3, 3, 2, 1, 4, 3},
                      {3, 3, 2, 1, 3, 2},
                      {3, 4, 3, 2, 2, 1},
                      {1, 2, 1, 1, 0, 0},
                      {0, 1, 1, 1, 0, 0}
                  });

    return 0;
}

void testFixCounts(const Grid<bool>& mines, const Grid<int>& expected) {
    Grid<int> actual;
    fixCounts(mines, actual);
    cout << "Result: " << (actual == expected ? "Success." : "Failed.") << endl;
}

void fixCounts(const Grid<bool>& mines, Grid<int>& counts) {
    int rows = mines.height();
    int cols = mines.width();

    counts.resize(rows, cols);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            counts[r][c] = getAdjacentMines(mines, r, c);
        }
    }
}

int getAdjacentMines(const Grid<bool>& mines, int row, int col) {
    int res = 0;

    for (int r = row - 1; r <= row + 1; ++r) {
        for (int c = col - 1; c <= col + 1; ++c) {
            if (mines.inBounds(r, c) && mines[r][c]) {
                ++res;
            }
        }
    }

    return res;
}
