#include <sstream>
#include "point.h"

Point::Point() {
    x = y = 0;
}

Point::Point(int cx, int cy) {
    x = cx;
    y = cy;
}

int Point::getX() {
    return x;
}

int Point::getY() {
    return y;
}

std::string integerToString(int x) {
    std::ostringstream os;
    os << x;
    return os.str();
}

std::string Point::toString() const {
    return "(" + integerToString(x) + ", " + integerToString(y) + ")";
}

std::ostream& operator<< (std::ostream& os, const Point& pt) {
    return os << pt.toString();
}

bool operator== (const Point& pt1, const Point& pt2) {
    return pt1.x == pt2.x && pt1.y == pt2.y;
}

bool operator!= (const Point& pt1, const Point& pt2) {
    return !(pt1 == pt2);
}
