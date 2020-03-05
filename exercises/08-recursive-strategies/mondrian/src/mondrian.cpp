#include <iostream>
#include "gwindow.h"

using namespace std;

const double MIN_AREA = 10000;
const double MIN_EDGE = 20;

void subdivideCanvas(GWindow& gw, double x, double y,
                     double width, double height);

int main() {
    GWindow gw;
    gw.setExitOnClose(true);
    gw.setColor("black");
    gw.setLineWidth(5);
    subdivideCanvas(gw, 0, 0, gw.getWidth(), gw.getHeight());

    return 0;
}

void subdivideCanvas(GWindow& gw, double x, double y,
                     double width, double height) {
    if (width * height >= MIN_AREA) {
        if (width > height) {
            double mid = randomReal(MIN_EDGE, width - MIN_EDGE);
            subdivideCanvas(gw, x, y, mid, height);
            subdivideCanvas(gw, x + mid, y, width - mid, height);
            gw.drawLine(x + mid, y, x + mid, y + height);
        } else {
            double mid = randomReal(MIN_EDGE, height - MIN_EDGE);
            subdivideCanvas(gw, x, y, width, mid);
            subdivideCanvas(gw, x, y + mid, width, height - mid);
            gw.drawLine(x, y + mid, x + width, y + mid);
        }
    }
}
