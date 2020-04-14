#include <iostream>
#include "gtypes.h"
#include "strlib.h"
#include "console.h"
#include "gwindow.h"

using namespace std;

const int N_ACROSS = 3;
const int N_DOWN = 3;
const int DELTA = 3;

void fillPoints(Vector<GPoint>& points, double width, double height);
void fillHorizontally(Vector<GPoint>& points, GPoint startCoord, int num, double distance);
void fillVertically(Vector<GPoint>& points, GPoint startCoord, int num, double distance);
void drawFigure(GWindow& gw, Vector<GPoint>& points);

int main() {
    GWindow gw;
    gw.setColor("black");
    Vector<GPoint> points;
    fillPoints(points, gw.getWidth(), gw.getHeight());
    drawFigure(gw, points);

    char ch;
    cin.get(ch);

    gw.close();

    return 0;
}

void fillPoints(Vector<GPoint>& points, double width, double height) {
    double xDistance = static_cast<int>(width / N_ACROSS);
    double yDistance = static_cast<int>(height / N_DOWN);

    points.add(GPoint(0, 0));
    fillHorizontally(points, points.back(), N_ACROSS, xDistance);
    fillVertically(points, points.back(), N_DOWN, yDistance);
    fillHorizontally(points, points.back(), N_ACROSS, -xDistance);
    fillVertically(points, points.back(), N_DOWN, -yDistance);

    points.removeBack();
}

void fillHorizontally(Vector<GPoint>& points, GPoint startCoord, int num, double distance) {
    double xCoord = startCoord.getX() + distance;
    double yCoord = startCoord.getY();

    for (int i = 0; i < num - 1; i++, xCoord += distance) {
        GPoint pt(xCoord, yCoord);
        points.add(pt);
    }
}

void fillVertically(Vector<GPoint>& points, GPoint startCoord, int num, double distance) {
    double xCoord = startCoord.getX();
    double yCoord = startCoord.getY() + distance;

    for (int i = 0; i < num - 1; i++, yCoord += distance) {
        GPoint pt(xCoord, yCoord);
        points.add(pt);
    }
}

void drawFigure(GWindow& gw, Vector<GPoint>& points) {
    int n = points.size();
    int startIndex = 0;

    do {
        int destIndex = (startIndex + DELTA) % n;
        GPoint start = points[startIndex];
        GPoint dest = points[destIndex];

        gw.drawLine(start, dest);
        startIndex = destIndex;
    } while (startIndex > 0);

    // This is also possible, but not always!

    /*for (int i = 0; i < points.size(); i++) {
        if (i == 0) {
            gw.drawLine(points[i], points[i + (DELTA)]);

       } else {
        gw.drawLine(points[i], points[(i + DELTA) % points.size()]);
       }
    }*/
}
