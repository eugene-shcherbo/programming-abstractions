#include <iostream>
#include "strlib.h"
#include "gwindow.h"
#include "console.h"
#include "shape.h"
#include "shapelist.h"
#include "goptionpane.h"

using namespace std;

void testGetShapeAt(ShapeList& shapes, GWindow& gw);
void testMoving(ShapeList& shapes, GWindow& gw);
ShapeList* createShapes(GWindow& gw);

int main() {
    GWindow gw;

    ShapeList* shapes = createShapes(gw);
    shapes->draw(gw);
    testMoving(*shapes, gw);
    testGetShapeAt(*shapes, gw);

    for (Shape* sp : *shapes) delete sp;

    shapes->clear();

    return 0;
}

void testGetShapeAt(ShapeList& shapes, GWindow& gw) {
    while (true) {
        GMouseEvent mouseEvent = waitForEvent(MOUSE_EVENT);

        if (mouseEvent.getEventType() == MOUSE_DOUBLE_CLICKED) return;

        if (mouseEvent.getEventType() == MOUSE_CLICKED) {
            double x = mouseEvent.getX();
            double y = mouseEvent.getY();

            Shape* shape = shapes.getShapeAt(x, y);

            if (shape != nullptr) {
                shape->setColor(randomColorString());
                shape->draw(gw);
            }
        }
    }
}

ShapeList* createShapes(GWindow& gw) {
    double width = gw.getWidth();
    double height = gw.getHeight();

    Shape* rp = new Rect(width / 4, height / 4, width / 2, height / 2);
    Shape* op = new Oval(width / 4, height / 4, width / 2, height / 2);
    Shape* cp = new Circle(width / 4, height / 4, 40);
    Shape* sp = new Square(width / 4, height / 4, 40);
    rp->setColor("BLUE");
    op->setColor("GRAY");
    sp->setColor("GREEN");

    ShapeList* shapes = new ShapeList();
    shapes->add(new Line(0, height / 2, width / 2, 0));
    shapes->add(new Line(width / 2, 0, width, height / 2));
    shapes->add(new Line(width, height / 2, width / 2, height));
    shapes->add(new Line(width / 2, height, 0, height / 2));
    shapes->add(rp);
    shapes->add(op);
    shapes->add(cp);
    shapes->add(sp);

    return shapes;
}

void testMoving(ShapeList& shapes, GWindow& gw) {
    Shape* shape = shapes[1];

    shapes.moveForward(shape);
    shapes.draw(gw);
    shapes.moveBackward(shape);
    shapes.draw(gw);

    shapes.moveToBack(shape);
    shapes.draw(gw);
    shapes.moveToFront(shape);
    shapes.draw(gw);
}


