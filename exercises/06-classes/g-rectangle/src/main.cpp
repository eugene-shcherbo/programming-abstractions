#include <iostream>
#include "grectangle.h"
#include "console.h"
#include "strlib.h"

using namespace std;

int main() {
    graphics::GRectangle empty1;
    graphics::GRectangle empty2(1, 1, 0, 5);
    graphics::GRectangle empty3(1, 1, 5, 0);
    graphics::GRectangle rect(20, 20, 50, 50);

    cout << empty1 << endl
         << rect << endl;

    cout << empty1 << "empty? " << boolToString(empty1.isEmpty()) << endl;
    cout << empty2 << "empty? " << boolToString(empty2.isEmpty()) << endl;
    cout << empty3 << "empty? " << boolToString(empty3.isEmpty()) << endl;
    cout << rect << "empty? " << boolToString(rect.isEmpty()) << endl;

    GPoint pt1(15, 55);
    GPoint pt2(22, 55);

    cout << pt1 << " in " << rect << "? " << boolToString(rect.contains(pt1)) << endl;
    cout << pt2 << " in " << rect << "? " << boolToString(rect.contains(pt2)) << endl;

    return 0;
}
