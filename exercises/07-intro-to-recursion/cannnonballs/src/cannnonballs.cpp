#include <iostream>
#include "console.h"

using namespace std;

int cannonballs(int height);
void testCannonballs(int height, int expected);

int main() {
    testCannonballs(0, 0);
    testCannonballs(1, 1);
    testCannonballs(2, 5);
    testCannonballs(3, 14);
    testCannonballs(4, 30);

    return 0;
}

void testCannonballs(int height, int expected) {
    int actual = cannonballs(height);
    cout << "Number of cannonballs in pyramid of height " << height
         << " is " << actual << endl;
    cout << "Result: " << (actual == expected ? "success. " : "failed.") << endl;
}

int cannonballs(int height) {
    if (height <= 1) {
        return height;
    } else {
        return height * height + cannonballs(height - 1);
    }
}
