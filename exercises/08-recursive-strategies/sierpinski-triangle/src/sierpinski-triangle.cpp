#include <iostream>
#include "console.h"
#include "gwindow.h"

using namespace std;

const int SIZE = 500;

void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order);
void drawTriangle(GWindow& gw, double x, double y, double size);

int main() {
    GWindow gw;
    gw.setColor("black");

    double cx = gw.getWidth() / 2;
    double cy = gw.getHeight() / 2;

    GPoint pt(cx - SIZE / 2, cy + SIZE / 2);
    drawSierpinskiTriangle(gw, pt.getX(), pt.getY(), SIZE, 10);

    char ch;
    cin.get(ch);
    gw.close();

    return 0;
}

void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order) {
    if (order == 0) {
        drawTriangle(gw, x, y, size);
    } else {
        double height = (sqrt(3) / 2) * size;
        drawSierpinskiTriangle(gw, x, y, size / 2, order - 1);
        drawSierpinskiTriangle(gw, x + size / 4, y - height / 2, size / 2, order - 1);
        drawSierpinskiTriangle(gw, x + size / 2, y, size / 2, order - 1);
    }
}

void drawTriangle(GWindow& gw, double x, double y, double size) {
    GPoint pt = gw.drawPolarLine(x, y, size, 60);
    pt = gw.drawPolarLine(pt, size, -60);
    pt = gw.drawPolarLine(pt, size, 180);
}
