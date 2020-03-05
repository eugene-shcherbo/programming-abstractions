/**
 * File: maze-generator.cpp
 * ------------------------
 * Presents an adaptation of Kruskal's algorithm to generate mazes.
 */

#include <iostream>
using namespace std;

#include "console.h"
#include "simpio.h"
#include "maze-graphics.h"
#include "maze-types.h"

/**
 * Function: getMazeDimension
 * --------------------------
 * Asks the user to enter a dimension of a maze to be generated with the 'prompt'
 * and ensure that the number the user entered lies in the range ['min', 'max'].
 */
static int getMazeDimension(const string& prompt, int min = 7, int max = 50);


/**
 * Function: generateWallsAndChambers
 * ----------------------------------
 * Generates walls and chambers for a maze of the given gimension. Generated walls
 * and chambers are written into the given vectors.
 */
static void generateWallsAndChambers(Vector<wall>& walls, Vector<Set<cell>>& chambers, int dimension);

/**
 * Function: drawWalls
 * -------------------
 * Draws the given vector of 'walls' on the maze 'view'.
 */
static void drawWalls(const Vector<wall>& walls, MazeGeneratorView& view);

/**
 * Function: shuffleWalls
 * ----------------------
 * Reorders the given vector of 'walls' in the random way.
 */
static void shuffleWalls(Vector<wall>& walls);


/**
 * Function: removeWalls
 * ---------------------
 * Actually generates a maze by removing 'walls' from the maze 'view' and merging 'chambers'.
 */
static void removeWalls(const Vector<wall>& walls, Vector<Set<cell>>& chambers, MazeGeneratorView& view);

/**
 * Function: isTheSameChamber
 * --------------------------
 * Test if the given 'wall' splits different chambers.
 */
static bool isTheSameChamber(const wall& wall, const Vector<Set<cell>>& chambers);

/**
 * Function: mergeChambers
 * -----------------------
 * Merges two chambers in the 'chambers' vector if they are splitted by the given 'wall'.
 */
static void mergeChambers(const wall& wall, Vector<Set<cell>>& chambers);

int main() {
    MazeGeneratorView mazeView;

    while (true) {
        int dimension = getMazeDimension("What should the dimension of your maze be [0 to exit]? ", 1);
        if (dimension == 0) {
            break;
        }

        mazeView.setDimension(dimension);

        Vector<wall> walls;
        Vector<Set<cell>> chambers;
        generateWallsAndChambers(walls, chambers, dimension);
        drawWalls(walls, mazeView);
        shuffleWalls(walls);
        removeWalls(walls, chambers, mazeView);
    }

    return 0;
}

static int getMazeDimension(const string& prompt, int min, int max) {
    while (true) {
        int response = getInteger(prompt);
        if (response == 0 || (response >= min && response <= max)) {
            return response;
        }

        cout << "Please enter a number between " << min << " and " << max << ", inclusive." << endl;
    }
}

static void generateWallsAndChambers(Vector<wall>& walls, Vector<Set<cell>>& chambers, int dimension) {
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            cell current;
            current.row = i;
            current.col = j;

            cell right;
            right.row = i;
            right.col = j + 1;

            cell down;
            down.row = i + 1;
            down.col = j;

            wall vert;
            vert.one = current;
            vert.two = right;

            wall horiz;
            horiz.one = current;
            horiz.two = down;

            if (i != dimension - 1) {
                walls.add(horiz);
            }

            if (j != dimension - 1) {
                walls.add(vert);
            }

            Set<cell> chamber { current };
            chambers.add(chamber);
        }
    }
}

static void drawWalls(const Vector<wall>& walls, MazeGeneratorView& view) {
    view.addAllWalls(walls);
    view.repaint();
}

static void shuffleWalls(Vector<wall>& walls) {
    for (int i = 0; i < walls.size(); ++i) {
        int randomIndex = randomInteger(i, walls.size() - 1);
        if (i != randomIndex) {
            wall current = walls[i];
            walls[i] = walls[randomIndex];
            walls[randomIndex] = current;
        }
    }
}

static void removeWalls(const Vector<wall>& walls, Vector<Set<cell>>& chambers, MazeGeneratorView& view) {
    for (wall w: walls) {
        if (!isTheSameChamber(w, chambers)) {
            view.removeWall(w);
            view.repaint();
            mergeChambers(w, chambers);
        }
    }
}

static bool isTheSameChamber(const wall& wall, const Vector<Set<cell>>& chambers) {
    for (Set<cell> ch: chambers) {
        if (ch.contains(wall.one) && ch.contains(wall.two)) {
            return true;
        }
    }

    return false;
}

static void mergeChambers(const wall& wall, Vector<Set<cell>>& chambers) {
    Set<cell> merged;

    for (int i = chambers.size() - 1; i >= 0; --i) {
        auto ch = chambers[i];
        if (ch.contains(wall.one) || ch.contains(wall.two)) {
            merged += ch;
            chambers.remove(i);
        }
    }

    chambers.add(merged);
}
