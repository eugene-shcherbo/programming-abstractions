#include <iostream>
#include "gwindow.h"

using namespace std;

const int INCH_LENGTH = 200;
const double HALF_INCH_TICK = 0.2;
const double SIXTEENTHS_TICK = HALF_INCH_TICK / 8;

void drawInchRuller(GWindow& gw);
void rullerHelper(GWindow& gw, double tickLength, double xStart, double xEnd, double y);

int main() {
    GWindow gw;
    gw.setExitOnClose(true);
    gw.setColor("black");
    drawInchRuller(gw);

    char ch;
    cin.get(ch);

    gw.close();

    return 0;
}

void drawInchRuller(GWindow& gw) {
    double mid = gw.getWidth() / 2;
    double x = mid - INCH_LENGTH / 2;
    double y = gw.getHeight() / 2;

    gw.drawLine(x, y, x + INCH_LENGTH, y);
    rullerHelper(gw, HALF_INCH_TICK, x, x + INCH_LENGTH, y);
}

void rullerHelper(GWindow& gw, double tickLength, double xStart, double xEnd, double y) {
    if (tickLength > SIXTEENTHS_TICK) {
        double mid = (xStart + xEnd) / 2;
        rullerHelper(gw, tickLength / 2, xStart, mid, y);
        rullerHelper(gw, tickLength / 2, mid, xEnd, y);
        gw.drawPolarLine(mid, y, tickLength * 96, 90);
    }
}


