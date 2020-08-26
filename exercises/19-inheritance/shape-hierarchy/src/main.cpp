#include <iostream>
#include "strlib.h"
#include "gwindow.h"
#include "console.h"
#include "shape.h"
#include "shapelist.h"

using namespace std;

void testContains(std::string shapeName, Shape* shape, double pointX, double pointY);
void testContains(double width, double height, ShapeList& shapes, Shape* rp, Shape* op);

int main() {
    GWindow gw;
    double width = gw.getWidth();
    double height = gw.getHeight();

    Shape* rp = new Rect(width / 4, height / 4, width / 2, height / 2);
    Shape* op = new Oval(width / 4, height / 4, width / 2, height / 2);
    Shape* cp = new Circle(width / 4, height / 4, 40);
    Shape* sp = new Square(width / 4, height / 4, 40);
    rp->setColor("BLUE");
    op->setColor("GRAY");
    sp->setColor("GREEN");

    ShapeList shapes;
    shapes.add(new Line(0, height / 2, width / 2, 0));
    shapes.add(new Line(width / 2, 0, width, height / 2));
    shapes.add(new Line(width, height / 2, width / 2, height));
    shapes.add(new Line(width / 2, height, 0, height / 2));
    shapes.add(rp);
    shapes.add(op);
    shapes.add(cp);
    shapes.add(sp);
    shapes.draw(gw);

    shapes.moveForward(cp);
    shapes.draw(gw);
    shapes.moveBackward(cp);
    shapes.draw(gw);

    shapes.moveToBack(op);
    shapes.draw(gw);
    shapes.moveToFront(op);
    shapes.draw(gw);

    testContains(width, height, shapes, rp, op);

    for (Shape* sp : shapes) {
        delete sp;
    }

    shapes.clear();

    return 0;
}

void testContains(std::string shapeName, Shape* shape, double pointX, double pointY) {
    cout << shapeName << " contains point (" << pointX << ", " << pointY << ")? "
         << boolToString(shape->contains(pointX, pointY)) << endl;
}

void testContains(double width, double height, ShapeList& shapes, Shape* rp, Shape* op) {
    double pointX = 1;
    double pointY = height / 2;

    testContains("Rectangle", rp, pointX, pointY);
    testContains("Oval", op, pointX, pointY);
    testContains("Line", shapes[0], pointX, pointY);
}


