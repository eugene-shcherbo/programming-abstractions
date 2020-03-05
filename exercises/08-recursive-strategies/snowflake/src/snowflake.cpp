#include <iostream>
#include "gwindow.h"

using namespace std;

const double SIZE = 200;
const int ORDER  = 4;

/**
 * Function drawFractalLine
 * ------------------------
 * Draws a fractal edge starting from pt and extending r units in direction
 * theta. If order > 0, the edge is divided into four fractal edges of the
 * next lower order. The function returns the endpoint of the line.
 */
GPoint drawFractalLine(GWindow& gw, GPoint pt, double r, double theta, int order);

int main() {
    GWindow gw;
    gw.setColor("black");
    gw.setLineWidth(3);
    gw.setExitOnClose(true);
    cout << "Program to draw a snowflake fractal." << endl;
    double cx = gw.getWidth() / 2;
    double cy = gw.getHeight() / 2;
    GPoint pt(cx - SIZE / 2, cy - sqrt(3.0) * SIZE / 6);
    pt = drawFractalLine(gw, pt, SIZE, 0, ORDER);
    pt = drawFractalLine(gw, pt, SIZE, -120, ORDER);
    pt = drawFractalLine(gw, pt, SIZE, 120, ORDER);

    char ch;
    cin.get(ch);

    return 0;
}

GPoint drawFractalLine(GWindow& gw, GPoint pt, double r, double theta, int order) {
    if (order == 0) {
        return gw.drawPolarLine(pt, r, theta);
    } else {
        pt = drawFractalLine(gw, pt, r / 3, theta, order - 1);
        pt = drawFractalLine(gw, pt, r / 3, theta + 60, order - 1);
        pt = drawFractalLine(gw, pt, r / 3, theta - 60, order - 1);
        return drawFractalLine(gw, pt, r / 3, theta, order - 1);
    }
}
