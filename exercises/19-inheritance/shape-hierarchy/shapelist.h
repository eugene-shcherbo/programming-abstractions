#ifndef SHAPELIST_H
#define SHAPELIST_H

#include "vector.h"
#include "shape.h"

class ShapeList : public Vector<Shape*> {
public:
    void moveToFront(Shape* sp);
    void moveToBack(Shape* sp);
    void moveForward(Shape* sp);
    void moveBackward(Shape* sp);

    void draw(GWindow& window) const;

private:
    void shiftRight(int from, int count);
    void shiftLeft(int from, int count);
    void shiftRight(int from);
    void shiftLeft(int from);
};

#endif // SHAPELIST_H
