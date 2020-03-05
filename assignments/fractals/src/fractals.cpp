/*
 * File: fractals.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains fractal problems for CS106X.
 */


#include "fractals.h"
#include <cmath>
#include "gbufferedimage.h"
#include "plasmacolor.h"

using namespace std;

/**
 * Function: drawEquilateralTriangle
 * --------------------------------------------------------
 * Draws an Equliateral Triangle starting in the ('x', 'y')
 * with provided 'sideLength'
 */
void drawEquilateralTriangle(GWindow& gw, double x, double y, double sideLength);

bool isInputValid(double x, double y, double sideLength, int order) {
    return x >= 0 && y >= 0 && sideLength >= 0 && order >= 0;
}

/**
 * Draws a Sierpinski triangle of the specified size and order, placing its
 * bottom-left corner at position (x, y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the Sierpinski triangle.
 * @param x - The x coordinate of the bottom-left corner of the triangle.
 * @param y - The y coordinate of the bottom-left corner of the triangle.
 * @param sideLength - The length of one side of the triangle.
 * @param order - The order of the fractal.
 */
void drawSierpinskiTriangle(GWindow& window, double x, double y, double sideLength, int order) {
    if (!isInputValid(x, y, sideLength, order)) {
        throw "invalid input";
    } else if (order == 0) {
        drawEquilateralTriangle(window, x, y, sideLength);
    } else {
        double height = (sqrt(3) / 2) * sideLength;
        drawSierpinskiTriangle(window, x, y, sideLength / 2, order - 1);
        drawSierpinskiTriangle(window, x + sideLength / 4, y - height / 2, sideLength / 2, order - 1);
        drawSierpinskiTriangle(window, x + sideLength / 2, y, sideLength / 2, order - 1);
    }
}

void drawEquilateralTriangle(GWindow& gw, double x, double y, double sideLength) {
    gw.drawPolarLine(x, y, sideLength, 0);
    gw.drawPolarLine(x, y, sideLength, 60);
    gw.drawPolarLine(x + sideLength, y, sideLength, 120);
}

void drawTree(GWindow& gw, double x, double y, double size, double theta, int order) {
    if (order == 1) {
        gw.setColor("#2e8b57");
        gw.drawPolarLine(x, y, size, theta);
    } else if (order > 1) {
        gw.setColor("#8b7765");
        GPoint pt = gw.drawPolarLine(x, y, size, theta);
        for (int i = 0; i < 7; ++i) {
            drawTree(gw, pt.getX(), pt.getY(), size / 2,  theta - 45 + 15 * i, order - 1);
        }
    }
}

/**
 * Draws a recursive tree fractal image of the specified size and order,
 * placing the bounding box's top-left corner at position (x,y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the recursive tree.
 * @param x - The x coordinate of the top-left corner of the bounding box.
 * @param y - The y coordinate of the top-left corner of the bounding box.
 * @param size - The length of one side of the bounding box.
 * @param order - The order of the fractal.
 */
void drawTree(GWindow& window, double x, double y, double size, int order) {
    drawTree(window, x + size / 2, y + size, size / 2, 90, order);
}

bool isMandelbrotNumber(const Complex& c, const Complex& z, int iterations) {
    if (iterations == 0) {
        return true;
    } else {
        Complex curr = z * z + c;
        return curr.abs() <= 4.0 && isMandelbrotNumber(c, curr, iterations - 1);
    }
}

bool isMandelbrotNumber(const Complex& c, int iterations) {
    return isMandelbrotNumber(c, Complex(0, 0), iterations);
}

double linearTransform(double minA, double maxA, double minB, double maxB, int val) {
    return (val - minA) / (maxA - minA) * (maxB - minB) + minB;
}

/**
 * Draws a Mandelbrot Set in the graphical window at the specified location/size,
 * with maxIterations and in a given color.
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the Mandelbrot set.
 * @param leftX - The x coordinate of the top-left corner of the bounding box.
 * @param topY - The y coordinate of the top-left corner of the bounding box.
 * @param min - the minimum Complex number you should examine
 * @param max - the maximum Complex number you should examine
 * @param iterations - The maximum number of iterations to run recursive step
 * @param color - The color of the fractal
 */
void drawMandelbrotSet(GWindow& window, double leftX, double topY, double size,
                       const Complex& min, const Complex& max,
                       int iterations, int color) {
    GBufferedImage image(size, size, 0xffffff);
    window.add(&image, leftX, topY);
    Grid<int> pixels = image.toGrid(); // Convert image to grid

    for (int y = 0; y < pixels.height(); ++y) {
        for (int x = 0; x < pixels.width(); ++x) {
            double real = linearTransform(leftX, leftX + size, min.real(), max.real(), leftX + x);
            double imaginary = linearTransform(topY, topY + size, min.imag(), max.imag(), topY + y);

            if (isMandelbrotNumber(Complex(real, imaginary), iterations)) {
                pixels[y][x] = color;
            }
        }
    }

    image.fromGrid(pixels); // Converts and puts the grid back into the image onscreen
}

/**
 * Generates a random displacement value you can add to a color to randomly shift it.
 *
 * You should call this function when calculating middle color values.
 *
 * @param newWidth - the width of the subdivided rectangles you are creating at that moment
 * @param newHeight - the height of the subdivided rectangles you are creating at that moment
 * @param totalWidth - the width of the entire plasma fractal (not just the part you are filling in at the moment)
 * @param totalHeight - the height of the entire plasma fractal (not just the part you are filling in at the moment)
 */
double displace(double newWidth, double newHeight, double totalWidth, double totalHeight) {
    double max = 3 * (newWidth + newHeight) / (totalWidth + totalHeight);
    return (randomReal(0, 1) - 0.5) * max;
}

void drawPlasma(Grid<int>& pixels, double topX, double topY, double height, double width,
                double totalHeight, double totalWidth, PlasmaColor c1, PlasmaColor c2, PlasmaColor c3, PlasmaColor c4) {
    PlasmaColor avg = (c1 + c2 + c3 + c4) / 4;

    if (width <= 1 || height <= 1) {
        pixels[static_cast<int>(topY)][static_cast<int>(topX)] = avg.toRGBColor();
    } else {
        double halfHeight = height / 2;
        double halfWidth = width / 2;

        PlasmaColor topEdge = (c1 + c3) / 2;
        PlasmaColor leftEdge = (c1 + c2) / 2;
        PlasmaColor rightEdge = (c3 + c4) / 2;
        PlasmaColor bottomEdge = (c2 + c4) / 2;
        PlasmaColor mid = avg + displace(halfWidth, halfHeight, totalWidth, totalHeight);

        drawPlasma(pixels, topX, topY, halfHeight, halfWidth, totalHeight, totalWidth, c1, leftEdge, topEdge, mid);
        drawPlasma(pixels, topX + halfWidth, topY, halfHeight, halfWidth, totalHeight, totalWidth, topEdge, mid, c3, rightEdge);
        drawPlasma(pixels, topX, topY + halfHeight, halfHeight, halfWidth, totalHeight, totalWidth, leftEdge, c2, mid, bottomEdge);
        drawPlasma(pixels, topX + halfWidth, topY + halfHeight, halfHeight, halfWidth, totalHeight, totalWidth, mid, bottomEdge, rightEdge, c4);
    }
}

/**
 * Draws a Plasma Fractal in the graphical window at the specified location/size.
 *
 * This will be called by fractalgui.cpp.
 *
 * @param window - The window in which to draw the fractal.
 * @param x - The x coordinate of the top-left corner of the bounding box.
 * @param y - The y coordinate of the top-left corner of the bounding box.
 * @param size - The length of one side of the bounding box.
 */
void drawPlasma(GWindow &window, double x, double y, double size) {
    GBufferedImage image(size, size, 0xffffff);
    window.add(&image, x, y);
    Grid<int> pixels = image.toGrid(); // Convert image to grid

    drawPlasma(pixels, 0, 0, pixels.height(), pixels.width(), pixels.height(), pixels.width(),
               PlasmaColor(), PlasmaColor(), PlasmaColor(), PlasmaColor());

    image.fromGrid(pixels); // Converts and puts the grid back into the image onscreen
}
