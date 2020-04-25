#include "recursionproblems.h"
#include <cmath>
#include <iostream>
#include "hashmap.h"
#include "map.h"
#include "random.h"

using namespace std;

bool inBounds(int row, int col, const Vector<Vector<double> >& weights) {
    if (row < 0 || row > weights.size() - 1) {
        return false;
    } else if (col < 0 || col > weights[row].size() - 1) {
        return false;
    }

    return true;
}

double weightOnKnees(int row, int col, const Vector<Vector<double> >& weights) {
    if (!inBounds(row, col, weights)) {
        return .0;
    } else if (row == 0) {
        return weights[row][0];
    } else {
        double leftPerson = weightOnKnees(row - 1, col - 1, weights) / 2;
        double rightPerson = weightOnKnees(row - 1, col, weights) / 2;

        return weights[row][col] + leftPerson + rightPerson;
    }
}

double weightOnKneesFaster(int row, int col, const Vector<Vector<double> >& weights,
                           Vector<Vector<double> >& memos) {

    if (!inBounds(row, col, weights)) {
        return .0;
    } else if (memos[row][col] == .0) {
        double leftPerson = 0.5 * weightOnKneesFaster(row - 1, col - 1, weights, memos);
        double rightPerson = 0.5 * weightOnKneesFaster(row - 1, col, weights, memos);
        memos[row][col] = weights[row][col] + leftPerson + rightPerson;
    }

    return memos[row][col];
}

double weightOnKneesFaster(int row, int col, const Vector<Vector<double> >& weights) {
    Vector<Vector<double>> memos;

    for (int r = 0; r < weights.size(); r++) {
        memos.add(Vector<double>());
        for (int c = 0; c < weights[r].size(); c++) {
            memos[r].add(.0);
        }
    }

    return weightOnKneesFaster(row, col, weights, memos);
}

void drawTriangle(GWindow& gw, double x, double y, int size) {
    double height = (sqrt(3) / 2) * size;
    gw.drawLine(x, y, x + size, y);
    gw.drawLine(x, y, x + size / 2, y + height);
    gw.drawLine(x + size, y, x + size / 2, y + height);
}

void drawSierpinskiTriangle(GWindow& gw, double x, double y, int size, int order) {
    if (x < 0 || y < 0 || size < 0 || order < 0) {
        throw "drawSierpinskiTriangle: negative arguments are not applicable";
    } if (order == 0) {
        return;
    } else if (order == 1) {
        drawTriangle(gw, x, y, size);
    } else {
        double height = (sqrt(3) / 2) * size;
        drawSierpinskiTriangle(gw, x, y, size / 2, order - 1);
        drawSierpinskiTriangle(gw, x + size / 2, y, size / 2, order - 1);
        drawSierpinskiTriangle(gw, x + size / 4, y + height / 2, size / 2, order - 1);
    }
}

