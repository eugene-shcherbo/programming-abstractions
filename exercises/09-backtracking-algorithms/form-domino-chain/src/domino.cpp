#include <sstream>
#include "domino.h"
#include "strlib.h"

Domino::Domino() {
    _left = 0;
    _right = 0;
}

Domino::Domino(int left, int right) {
    if (left < 0 || left > 6 || right < 0 || right > 6) {
        throw "Domino ctr: dots should be in the range [0; 6]";
    }

    _left = left;
    _right = right;
}

std::string Domino::toString() const {
    return integerToString(_left) + "-" + integerToString(_right);
}

int Domino::getLeftDots() const {
    return _left;
}

int Domino::getRightDots() const {
    return _right;
}

std::ostream& operator<< (std::ostream& os, const Domino& d) {
    return os << d.toString();
}

bool operator== (const Domino& d1, const Domino& d2) {
    return (d1._left == d2._left && d1._right == d2._right)
            || (d1._left == d2._right && d1._right == d2._left);
}

bool operator!= (const Domino& d1, const Domino& d2) {
    return !(d1 == d2);
}

bool operator< (const Domino& d1, const Domino& d2) {
    return d1.getLeftDots() < d2.getLeftDots()
            || (d1.getLeftDots() == d2.getLeftDots() && d1.getRightDots() < d2.getRightDots());
}

bool operator<= (const Domino& d1, const Domino& d2) {
    return d1 < d1 || d1 == d2;
}

bool operator> (const Domino& d1, const Domino& d2) {
    return !(d1 <= d2);
}

bool operator>= (const Domino& d1, const Domino& d2) {
    return d1 > d2 || d1 == d2;
}
