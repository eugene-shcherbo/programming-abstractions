#include <iostream>
#include "vector.h"
#include "domino.h"
#include "console.h"

using namespace std;

int main() {
    Vector<Domino> fullDominoSet;

    for (int left = 0; left <= 6; left++) {
        for (int right = left; right <= 6; right++) {
            fullDominoSet.add(Domino(left, right));
        }
    }

    for (const Domino& d: fullDominoSet) {
        cout << d << endl;
    }

    return 0;
}

