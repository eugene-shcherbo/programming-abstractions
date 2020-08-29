#include "error.h"
#include "shapelist.h"

void ShapeList::moveToFront(Shape* sp) {
    for (int i = 0; i < size(); i++) {
        if (get(i) == sp) {
            shiftLeft(i);
            set(size() - 1, sp);
            return;
        }
    }
    error("moveToFront: shape is not in the list");
}

void ShapeList::moveToBack(Shape* sp) {
    for (int i = size() - 1; i >= 0; i--) {
        if (get(i) == sp) {
            shiftRight(i);
            set(0, sp);
            return;
        }
    }
    error("moveToBack: shape is not in the list");
}

void ShapeList::moveForward(Shape* sp) {
    for (int i = 0; i < size(); i++) {
        if (get(i) == sp) {
            shiftLeft(i, 1);
            set(i + 1 < size() ? i + 1 : size() - 1, sp);
        }
    }
}

void ShapeList::moveBackward(Shape* sp) {
    for (int i = 0; i < size(); i++) {
        if (get(i) == sp) {
            shiftRight(i, 1);
            set(i - 1 >= 0 ? i - 1 : 0, sp);
        }
    }
}

void ShapeList::draw(GWindow& window) const {
    for (Shape* sp : *this) {
        sp->draw(window);
    }
}

Shape* ShapeList::getShapeAt(double x, double y) const {
    for (int i = size() - 1; i >= 0; i--) {
        if (get(i)->contains(x, y)) return get(i);
    }
    return nullptr;
}

void ShapeList::shiftRight(int from, int count) {
    int shifted = 0;
    for (int i = from - 1; i >= 0 && shifted < count; i--, shifted++) {
        set(i + 1, get(i));
    }
}

void ShapeList::shiftLeft(int from, int count) {
    int shifted = 0;
    for (int i = from + 1; i < size() && shifted < count; i++, shifted++) {
        set(i - 1, get(i));
    }
}

void ShapeList::shiftRight(int from) {
    shiftRight(from, size());
}

void ShapeList::shiftLeft(int from) {
    shiftLeft(from, size());
}
