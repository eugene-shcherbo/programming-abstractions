#include <iostream>
#include "console.h"
#include "grid.h"
#include "gcolor.h"
#include "gwindow.h"
#include "direction.h"

using namespace std;

void fillRegion(Grid<bool>& pixels, int row, int col);
int adjustRow(Direction dir, int row);
int adjustCol(Direction dir, int col);

int main() {
    Grid<bool> pixels {
        { false, false, false, false, true, true, true, false },
        { false, true, true, true, true, false, true, false },
        { false, true, false, true, true, true, true, false },
        { false, true, true, true, false, false, false, false },
        { false, false, false, false, false, false, false, false },
        { false, false, false, false, false, false, false, false }
    };

    fillRegion(pixels, 1, 0);
    cout << pixels.toString2D() << endl;

    char ch;
    cin.get(ch);

    return 0;
}

void fillRegion(Grid<bool>& pixels, int row, int col) {
    if (!pixels.inBounds(row, col)) return;
    if (pixels[row][col]) return;

    pixels[row][col] = true;

    for (Direction dir = NORTH; dir <= WEST; dir++) {
        fillRegion(pixels, adjustRow(dir, row), adjustCol(dir, col));
    }
}

int adjustRow(Direction dir, int row) {
    switch (dir) {
        case NORTH:
            return --row;
        case SOUTH:
            return ++row;
        case EAST: case WEST:
            return row;
    }
}

int adjustCol(Direction dir, int col) {
    switch (dir) {
        case NORTH: case SOUTH:
            return col;
        case EAST:
            return ++col;
        case WEST:
            return --col;
    }
}
