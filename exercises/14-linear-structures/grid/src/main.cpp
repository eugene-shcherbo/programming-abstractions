#include <iostream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "grid.h"
using namespace std;

template <typename ValueType>
void printGrid(const collections::Grid<ValueType>& grid) {
    for (int r = 0; r < grid.height(); r++) {
        for (int c = 0; c < grid.width(); c++) {
            cout << "(" << r << "," << c << ")th " << "element=" << grid.get(r, c) << endl;
        }
    }
}

int main() {
    collections::Grid<string> board;
    assert(board.isEmpty());
    assert(board.size() == 0);
    board.resize(10, 15);
    assert(board.size() == 150);
    assert(board.height() == 10);
    assert(board.width() == 15);
    for (int r = 0; r < board.height(); r++) {
        for (int c = 0; c < board.width(); c++) {
            assert(board.get(r, c).empty());
        }
    }

    collections::Grid<int> intBoard(3, 5, 5);
    assert(!intBoard.isEmpty());
    assert(intBoard.height() == 3);
    assert(intBoard.width() == 5);
    assert(intBoard.size() == 15);
    printGrid(intBoard);

    cout << endl;

    for (int r = 0; r < intBoard.height(); r++) {
        for (int c = 0; c < intBoard.width(); c++) {
            intBoard.set(r, c, r + c);
        }
    }

    cout << intBoard << endl;

    collections::Grid<int> copy = intBoard;
    copy.set(0, 0, 100500);
    assert(copy.get(0, 0) == 100500);
    assert(intBoard.get(0, 0) == 0);

    copy = intBoard;
    copy.set(0, 0, 100500);
    assert(copy.get(0, 0) == 100500);
    assert(intBoard.get(0, 0) == 0);

    return 0;
}
