#include <iostream>
#include "console.h"
#include "gwindow.h"

using namespace std;

const int H_SIZE = 300;
const int ORDER = 4;

void drawHFractal(GWindow& gw, double x, double y, double size, int order);

int main() {
    GWindow gw;

    gw.setColor("black");

    double cx = gw.getWidth() / 2;
    double cy = gw.getHeight() / 2;
    drawHFractal(gw, cx, cy, H_SIZE, ORDER);

    char ch;
    cin.get(ch);
    gw.close();

    return 0;
}

void drawHFractal(GWindow& gw, double x, double y, double size, int order) {
    if (order == 0) {
        gw.drawPolarLine(x - size / 2, y, size, 0);
        gw.drawPolarLine(x - size / 2, y + size / 2, size, 90);
        gw.drawPolarLine(x + size / 2, y + size / 2, size, 90);
    } else {
        drawHFractal(gw, x, y, size, order - 1);
        drawHFractal(gw, x - size / 2, y - size / 2, size / 2, order - 1);
        drawHFractal(gw, x + size / 2, y - size / 2, size / 2, order - 1);
        drawHFractal(gw, x - size / 2, y + size / 2, size / 2, order - 1);
        drawHFractal(gw, x + size / 2, y + size / 2, size / 2, order - 1);
    }
}

