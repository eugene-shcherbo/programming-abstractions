/*
 * File: fauxtoshop.cpp
 * --------------------
 * This program implements simple photo editor with advanced features
 * like green screen, "scatter" blur effect, and edge detection.
 */

#include <iostream>
#include <string>
#include <cmath>

#include "console.h"
#include "gwindow.h"
#include "grid.h"
#include "vector.h"
#include "simpio.h"
#include "strlib.h"
#include "gbufferedimage.h"
#include "gevents.h"

using namespace std;

static constexpr int WHITE = 0xFFFFFF;
static constexpr int BLACK = 0x000000;
static constexpr int GREEN = 0x00FF00;

/**
 * Function: performFilter
 * -----------------------
 * Asks the user which filter to apply in the image 'img' and apply the filter if the user's answer is valid.
 */
static void performFilter(GBufferedImage& img);

/**
 * Function: scatter
 * ----------------------
 * Makes the blur effect in the image scattering 'pixels' depending on the given 'degree'.
 */
static void scatter(Grid<int>& pixels, int degree);

/**
 * Function: getPixelInRange
 * -------------------------
 * Sets 'row' and 'col' representing pixel in the 'pixels' grid. The values are calculated randomly and must be
 * in the range ['centerRow' - 'radius', 'centerRow' + 'radius'] and ['centerCol' - 'radius', 'centerCol' + 'radius'].
 * The function tries to calculate values until they are bounds in the 'pixels' grid.
 */
static void getPixelInRange(const Grid<int>& pixels, int& row, int& col, int centerRow, int centerCol, int radius);

/**
  * Function: detectEdges
  * ---------------------
  * Sets all the edges pixels from the 'pixels' grid to black and others to white. A decision whether a pixel is an edge
  * or not is made depending on the 'threshold' value.
  */
static void detectEdges(Grid<int>& pixels, int threshold);

/**
 * Function: isPixelEdge
 * ---------------------
 * Returns true if a pixel represented by 'row' and 'col' in the 'pixels' grid is an edge. A decision whether a pixel
 * is an edge or not is made depending on the 'threshold' value.
 */
static bool isPixelEdge(const Grid<int>& pixels, int row, int col, int threshold);

/**
 * Function: getLocationToPlaceSticker
 * --------------------
 * Asks the user to provide a coordinates either entering coordinates manually in the such format - (row,col)
 * or offers to click somewhere to get coordinates from the mouse click position. Resulting coordinates are set
 * into the 'row' and 'col' parameters.
 */
static void getLocationToPlaceSticker(int& row, int& col);

/**
 * Function: parsePosition
 * -------------------------------
 * Parses the given string 'pos' which must be in the format (row,col) and sets 'row' and 'col'
 * with parsed values.
 */
static void parsePosition(int& row, int& col, const string& pos);

/**
 * Function: applyGreenSreen
 * -----------------------------------
 * Puts the 'sticker' image to the 'bgImg' in the 'row' and 'col' position so that any pixels
 * in the 'sticker' picture differ from pure green color on the 'threshold' value will be put
 * onto the 'bgImg' and others pixels are jsut ignored.
 */
static void applyGreenSreen(Grid<int>& bgImg, const Grid<int>& sticker, int threshold, int row, int col);

/**
 * Function: getDiffBetweenColors
 * ------------------------------
 * Calculates the difference between 'color1' and 'color2'.
 */
static int getDiffBetweenColors(int color1, int color2);

/**
 * Function: compareImages
 * -----------------------
 * Compares two images and prints how many pixels they differ.
 */
static void compareImages(const GBufferedImage& img1, GBufferedImage& img2);

/**
 * Function: promptUserIntegerInRange
 * ----------------------------------
 * Asks the user with the given 'prompt' for the integer until the value is in the range ['from', 'to'].
 */
static int promptUserForIntegerInRange(const string& prompt, int from, int to = INT_MAX);

/**
 * Function: promptUserForImage
 * ----------------------------
 * Prompts the user for the image name with the 'prompt' and tries to open the image and load into
 * the 'img' parameters. If 'isRequired' set to true, it will prompt the user until the image is
 * loaded successfully. Otherwise, user can enter blank line and the function returns to the caller.
 */
static string promptUserForImage(GBufferedImage& img, const string& prompt, bool isRequired);

/**
 * Function: openImageFromFilename
 * -------------------------------
 * Attempts to open the image file 'filename'. This function returns
 * true when the image file was successfully opened and the 'img' object
 * now contains that image, otherwise it returns false.
 */
static bool openImageFromFilename(GBufferedImage& img, const string& filename);

/**
 * Function: offerToSaveImg
 * ------------------------
 * Asks the user with the 'prompt' whether to save the image 'img' or not and tries to save
 * it with the file name the user entered.
 */
static void offerToSaveImg(const GBufferedImage& img, const string& prompt);

/**
 * Function: saveImageToFilename
 * -----------------------------
 * Attempts to save the image file to 'filename'. This function returns
 * true when the image was successfully saved to the file specified,
 * otherwise it returns false.
 */
static bool saveImageToFilename(const GBufferedImage& img, const string& filename);

/**
 * Function: getMouseClickLocation
 * -------------------------------
 * Waits for a mouse click in the GWindow and reports click location. When
 * this function returns, row and col are set to the row and column where
 * a mouse click was detected.
 */
static void getMouseClickLocation(int& row, int& col);

/**
 * Function: main
 * --------------
 * Provides the entry point of the entire program.
 */
int main() {
    GWindow gw;
    gw.setTitle("Fauxtoshop");
    gw.setVisible(true);
    cout << "Welcome to Fauxtoshop!" << endl;

    while (true) {
        GBufferedImage img;
        string imgFilename = promptUserForImage(img, "Enter name of image file to open (or blank to quit): ", false);

        if (imgFilename.empty()) {
            break;
        }

        gw.setSize(img.getWidth(), img.getHeight());
        gw.add(&img,0,0);
        performFilter(img);
        offerToSaveImg(img, "Enter filename to save image (or blank line to skip saving): ");
        gw.clear();

        cout << endl;
    }

    return 0;
}

static string promptUserForImage(GBufferedImage& img, const string& prompt, bool isRequired) {
    while (true) {
        string filename = getLine(prompt);

        if ((!isRequired && filename.empty()) || openImageFromFilename(img, filename)) {
            return filename;
        }

        cout << "Unable to open an image from that filename. Try again." << endl;
    }
}

static bool openImageFromFilename(GBufferedImage& img, const string& filename) {
    try {
        img.load(filename);
    } catch (...) {
        return false;
    }
    return true;
}

static void performFilter(GBufferedImage& img) {
    int choice;

    while (true) {
        cout << "Which image filter would you like to apply?" << endl
             << "\t 1 - Scatter" << endl
             << "\t 2 - Edge detection" << endl
             << "\t 3 - \"Green screen\" with another image" << endl
             << "\t 4 - Compare image with another image" << endl;

        choice = getInteger("Your choice: ");

        if (choice > 0 && choice < 5) {
            break;
        }

        cout << "Not valid menu choice. Try again." << endl;
    }

    Grid<int> pixels = img.toGrid();

    switch (choice) {
        case 1:
        {
            int degree = promptUserForIntegerInRange("Enter degree of scatter [1-100]: ", 1, 100);
            scatter(pixels, degree);
            break;
        }
        case 2:
        {
            int threshold = promptUserForIntegerInRange("Enter threshold for edge detection: ", 0);
            detectEdges(pixels, threshold);
            break;
        }
        case 3:
        {
            cout << "Now choose another file to add to you background image" << endl;
            GBufferedImage sticker;
            promptUserForImage(sticker, "Enter  name of image file to open: ", true);
            int threshold = getInteger("Now choose a tolerance threshold: ");
            int row;
            int col;
            getLocationToPlaceSticker(row, col);
            applyGreenSreen(pixels, sticker.toGrid(), threshold, row, col);
            break;
        }
        case 4:
        {
            cout << "Now choose another image file to compare to." << endl;
            GBufferedImage imgToCompare;
            promptUserForImage(imgToCompare, "Enter name of image file to open: ", true);
            compareImages(img, imgToCompare);
            break;
        }
    }

    img.fromGrid(pixels);
}

static void scatter(Grid<int>& pixels, int degree) {
    Grid<int> scatteredPixels(pixels.height(), pixels.width());

    for (int r = 0; r < scatteredPixels.height(); ++r) {
        for (int c = 0; c < scatteredPixels.width(); ++c) {
            int newPixelRow;
            int newPixelCol;
            getPixelInRange(pixels, newPixelRow, newPixelCol, r, c, degree);
            scatteredPixels[r][c] = pixels[newPixelRow][newPixelCol];
        }
    }

    pixels = scatteredPixels;
}

static void getPixelInRange(const Grid<int>& pixels, int& row, int& col, int centerRow, int centerCol, int radius) {
    while (true) {
        row = randomInteger(centerRow - radius, centerRow + radius);
        col = randomInteger(centerCol - radius, centerCol + radius);

        if (pixels.inBounds(row, col)) {
            return;
        }
    }
}

static void detectEdges(Grid<int>& pixels, int threshold) {
    Grid<int> edges(pixels.height(), pixels.width());

    for (int r = 0; r < edges.height(); ++r) {
        for (int c = 0; c < edges.width(); ++c) {
            if (isPixelEdge(pixels, r, c, threshold)) {
                edges[r][c] = BLACK;
            } else {
                edges[r][c] = WHITE;
            }
        }
    }

    pixels = edges;
}

static bool isPixelEdge(const Grid<int>& pixels, int row, int col, int threshold) {
    for (int r = row - 1; r <= row + 1; ++r) {
        for (int c = col - 1; c <= col + 1; ++c) {
            if (!pixels.inBounds(r, c)) {
                continue;
            }

            int diff = getDiffBetweenColors(pixels[row][col], pixels[r][c]);

            if (diff > threshold) {
                return true;
            }
        }
    }

    return false;
}

static void getLocationToPlaceSticker(int& row, int& col) {
    while (true) {
        cout << "Enter location to place image as \"(row,col)\" (or blank to use mouse): ";

        string line;
        getline(cin, line);

        if (line.empty()) {
            break;
        }
        parsePosition(row, col, line);

        if (row < 0 || col < 0) {
            cout << "The (row,col) values must be positive. Try again." << endl;
        } else {
            return;
        }
    }

    cout << "Now click the background image to place new image: " << endl;
    getMouseClickLocation(row, col);
    cout << "You choose (" << row << "," << col << ")" << endl;
}

static void parsePosition(int& row, int& col, const string& pos) {
    auto delimeter = pos.find(',');
    row = stringToInteger(pos.substr(1, delimeter - 1));
    col = stringToInteger(pos.substr(delimeter + 1, pos.length() - delimeter - 2));
}

static void applyGreenSreen(Grid<int>& bgImg, const Grid<int>& sticker, int threshold, int row, int col) {
    for (int r = row; r <= bgImg.height(); ++r) {
        for (int c = col; c <= bgImg.width(); ++c) {
            if (!(sticker.inBounds(r - row, c - col) & bgImg.inBounds(r, c))) {
                continue;
            }

            int diff = getDiffBetweenColors(sticker[r - row][c - col], GREEN);

            if (diff > threshold) {
                bgImg[r][c] = sticker[r - row][c - col];
            }
        }
    }
}

static int getDiffBetweenColors(int color1, int color2) {
    int red1, red2;
    int green1, green2;
    int blue1, blue2;

    GBufferedImage::getRedGreenBlue(color1, red1, green1, blue1);
    GBufferedImage::getRedGreenBlue(color2, red2, green2, blue2);

    int diffRed = abs(red1 - red2);
    int diffGreen = abs(green1 - green2);
    int diffBlue = abs(blue1 - blue2);

    return max(diffBlue, max(diffRed, diffGreen));
}

static void compareImages(const GBufferedImage& img1, GBufferedImage& img2) {
    int diffpixels = img1.countDiffPixels(img2);

    if (diffpixels > 0) {
        cout << "These images differ in " << diffpixels << " locations!" << endl;
    } else {
        cout << "These images are the same!" << endl;
    }
}

static void offerToSaveImg(const GBufferedImage& img, const string& prompt) {
    while (true) {
        auto filename = getLine(prompt);

        if (filename.empty() || saveImageToFilename(img, filename)) {
            return;
        }

        cout << "Unable to save into that file. Try again." << endl;
    }
}

static int promptUserForIntegerInRange(const string& promt, int from, int to) {
    while (true) {
        int val = getInteger(promt);

        if (val >= from && val <= to) {
            return val;
        }

        cout << "Integer isn't in the interval [" << from << ", " << to << "]. Try again." << endl;
    }
}

static bool saveImageToFilename(const GBufferedImage& img, const string& filename) {
    try {
        img.save(filename);
    } catch (...) {
        return false;
    }
    return true;
}

static void getMouseClickLocation(int& row, int& col) {
    GMouseEvent me;
    do {
        me = getNextEvent(MOUSE_EVENT);
    } while (me.getEventType() != MOUSE_CLICKED);
    row = me.getY();
    col = me.getX();
}
