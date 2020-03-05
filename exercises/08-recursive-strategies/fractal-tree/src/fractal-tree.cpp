#include <iostream>
#include "console.h"
#include "gwindow.h"

using namespace std;

const double SIZE = 300;
const double RATIO = 1.618;

GPoint drawFractalTree(GWindow& gw, double bx, double by, double theta, double size, int order);

int main() {
    GWindow gw(1200, 1000);
    gw.setColor("black");

    double cx = gw.getWidth() / 2;
    double cy = gw.getHeight() / 2;

    drawFractalTree(gw, cx, cy + SIZE / 2, 90, SIZE, 8);

    char ch;
    cin.get(ch);
    gw.close();

    return 0;
}

GPoint drawFractalTree(GWindow& gw, double bx, double by, double theta, double size, int order) {
    if (order == 0) {
        return gw.drawPolarLine(bx, by, size, theta);
    } else {
        GPoint pt = gw.drawPolarLine(bx, by, size, theta);
        drawFractalTree(gw, pt.getX(), pt.getY(), theta + 45, size / RATIO, order - 1);
        drawFractalTree(gw, pt.getX(), pt.getY(), theta - 45, size / RATIO, order - 1);
        return pt;
    }
}
