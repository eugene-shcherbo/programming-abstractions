#include <iostream>
#include "console.h"
#include "gwindow.h"

using namespace std;

const double SIZE = 100;
const int ORDER = 1;

GPoint drawCoastline(GWindow& gw, GPoint pt, double r, double theta, int order = 0);

int main() {
    GWindow gw;
    gw.setColor("black");

    double cx = gw.getWidth() / 2;
    double cy = gw.getHeight() / 2;
    GPoint pt(cx - SIZE / 2, cy - sqrt(3.0) * SIZE / 6);

    pt = drawCoastline(gw, pt, SIZE, 0, ORDER);

    char ch;
    cin.get(ch);

    gw.close();

    return 0;
}

GPoint drawCoastline(GWindow& gw, GPoint pt, double r, double theta, int order) {
    if (order == 0) {
        return gw.drawPolarLine(pt, r, theta);
    } else {
        double angle = randomChance(0.5) ? +60 : -60;
        pt = drawCoastline(gw, pt, r / 3, theta, order - 1);
        pt = drawCoastline(gw, pt, r / 3, theta + angle, order - 1);
        pt = drawCoastline(gw, pt, r / 3, theta - angle, order - 1);

        return drawCoastline(gw, pt, r / 3, theta, order - 1);
    }
}

