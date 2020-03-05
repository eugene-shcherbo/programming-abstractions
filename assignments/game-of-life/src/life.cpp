/**
 * File: life.cpp
 * --------------
 * Implements the Game of Life.
 */

#include <iostream>  // for cout
#include <fstream>
#include <cmath>
using namespace std;

#include "console.h" // required of all files that contain the main function
#include "simpio.h"  // for getLine
#include "gevents.h" // for mouse event detection
#include "strlib.h"
#include "filelib.h"
#include "gtimer.h"
#include "grid.h"

#include "life-constants.h"  // for kMaxAge
#include "life-graphics.h"   // for class LifeDisplay

/* Constants */
constexpr char COMMENT_MARK = '#';
constexpr char ALIVE_CELL = 'X';
constexpr int START_SPEED = 10;

/**
 * Function: welcome
 * -----------------
 * Introduces the user to the Game of Life and its rules.
 */
static void welcome() {
    cout << "Welcome to the game of Life, a simulation of the lifecycle of a bacteria colony." << endl;
    cout << "Cells live and die by the following rules:" << endl << endl;
    cout << "\tA cell with 1 or fewer neighbors dies of loneliness" << endl;
    cout << "\tLocations with 2 neighbors remain stable" << endl;
    cout << "\tLocations with 3 neighbors will spontaneously create life" << endl;
    cout << "\tLocations with 4 or more neighbors die of overcrowding" << endl << endl;
    cout << "In the animation, new cells are dark and fade to gray as they age." << endl << endl;
    getLine("Hit [enter] to continue....   ");
}

/**
 * Function: proceedSimulations
 * ----------------------------
 * Prompt the user to start a new simulation. Return boolean
 * depending on what the user's answer - yes or no.
 */
static bool proceedSimulations() {
    while (true) {
        string answer = getLine("Would you like to run another?");
        string lowerCaseAnswer = toLowerCase(answer);

        if (lowerCaseAnswer != "yes" && lowerCaseAnswer != "no") {
            cout << "Please enter \"yes\" or \"no\"." << endl;
        } else {
            return lowerCaseAnswer == "yes";
        }
    }
}

/**
 * Function: seedColony
 * --------------------
 * Asks the user how to seed the given colony - from file or randomly. If user choose
 * seeding from file the function will check if the file exists and if not it will ask
 * for a file again.
 */
static void seedColony(Grid<int>& colony);

/**
 * Function: seedRandomly
 * --------------------
 * Initialized the given colony with random height and width, as well as
 * random values for cells' age.
 */
static void seedRandomly(Grid<int>& colony);


/**
 * Function: isFileAbleToBeOpened
 * --------------------
 * Checks if the file with the given filename exists. Returns true or false
 * depending on existanse of the file.
 */
static bool isFileAbleToBeOpened(const string& filename);

/**
 * Function: isFileAbleToBeOpened
 * --------------------
 * Seed the given colony from the file with given filename. The file must have
 * strict structure. The function assumes that the file exists.
 */
static void seedFromFile(const string& filename, Grid<int>& colony);

/**
 * Function: chooseModeAndStartSimulation
 * -----------------------
 * Asks the user which mode to use - manual or animated
 * and start simulation on the given display for the given colony.
 * If animated it also provides several options for animation speed.
 */
static void chooseModeAndStartSimulation(LifeDisplay& display, Grid<int>& colony);

/**
 * Function: runInHandyMode
 * -----------------------
 * Advance the given colony with the given display in handy mode
 * which means that to continue simulation the user must to hit [RETURN]
 * and write "quit" to stop.
 */
static void runInHandyMode(LifeDisplay& display, Grid<int>& colony);

/**
 * Function: runAnimation
 * -----------------------
 * Advance the given colony with the given display automatically in
 * animated way with pauses between animations equals to ms
 * until the colony is stable or user clicks the mouse.
 */
static void runAnimation(LifeDisplay& display, Grid<int>& colony, int ms);


/**
 * Function: advanceColony
 * -----------------------
 * Advance the given colony to the next generation with the given display.
 * Return true if the colony becomes stable.
 */
static bool advanceColony(LifeDisplay& display, Grid<int>& colony);

/**
 * Function: calculateNextGeneration
 * -----------------------
 * Calculate the next generation for the given colony and set the colony
 * to the new generation. Set isStable to true if the colony becomes stable.
 */
static void calculateNextGeneration(Grid<int>& colony, bool& isStable);

/**
 * Function: getAliveNeighbors
 * -----------------------
 * Calculates alive cells in the given colony for the cell described with
 * the given row and col.
 */
static int getAliveNeighbors(const Grid<int>& colony, int row, int col);

/**
 * Function: isColonyStable
 * -----------------------
 * Compares two consecutive generation and checks if the colony is stable.
 * Returns true if the colony is stable and false otherwise.
 */
static bool isColonyStable(const Grid<int>& oldColony, const Grid<int>& advancedColony);

/**
 * Function: displayColony
 * -----------------------
 * Prints the given colony on the given display.
 */
static void displayColony(LifeDisplay& display, const Grid<int>& colony);

/**
 * Function: main
 * --------------
 * Provides the entry point of the entire program.
 */
int main() {
    setConsoleOutputColor("white");
    LifeDisplay display;
    display.setTitle("Game of Life");
    welcome();

    while (true) {
        cout << "You can start your colony with random cells or read from a prepared file." << endl;
        Grid<int> colony;
        seedColony(colony);
        display.setDimensions(colony.height(), colony.width());
        displayColony(display, colony);
        chooseModeAndStartSimulation(display, colony);

        if (!proceedSimulations()) {
            break;
        }
    }

    return 0;
}

static void seedColony(Grid<int>& colony) {
    string filename = getLine("Enter a name of colony file (or RETURN to seed randomly): ");
    if (filename.empty()) {
        seedRandomly(colony);
    } else if (isFileAbleToBeOpened(filename)) {
        seedFromFile(filename, colony);
    } else {
        cout << "Unable to open the file named \"" << filename << "\". Please select another file." << endl;
    }
}

static void seedRandomly(Grid<int>& colony) {
    setRandomSeed(int(time(NULL)));
    int width = randomInteger(40, 60);
    int height = randomInteger(40, 60);
    colony.resize(height, width, false);

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            bool isOccupied = randomChance(0.5);

            if (isOccupied) {
                colony[r][c] = randomInteger(1, kMaxAge);
            }
        }
    }
}

static bool isFileAbleToBeOpened(const string& filename) {
    ifstream file(filename);
    return !file.fail();
}

static void seedFromFile(const string& filename, Grid<int>& colony) {
    ifstream infile(filename);

    string line;
    while (getline(infile, line) && line.at(0) == COMMENT_MARK);

    int rows = stringToInteger(line);
    getline(infile, line);
    int cols = stringToInteger(line);
    colony.resize(rows, cols);

    for (int r = 0; r < rows && getline(infile, line); ++r) {
        for (int c = 0; c < line.length() && c < cols; ++c) {
            if (line[c] == ALIVE_CELL) {
                colony[r][c] = 1;
            }
        }
    }

    infile.close();
}

static void chooseModeAndStartSimulation(LifeDisplay& display, Grid<int>& colony) {
    cout << "You can choose how fast to run the simulation." << endl;
    cout << "\t 1 = As fasth as this chip can go!" << endl
         << "\t 2 = Not too fast, this is a school zone." << endl
         << "\t 3 = Nice and slow so I can watch everything that happens." << endl
         << "\t 4 = Require enter key be pressed before advancing to next generation." << endl;

    int choise = getInteger("");

    if (choise == 4) {
        runInHandyMode(display, colony);
    } else {
        runAnimation(display, colony, pow(START_SPEED, choise));
    }
}

static void runInHandyMode(LifeDisplay& display, Grid<int>& colony) {
    while (true) {
        string line = getLine("Please return to advance [or type out \"quit\" to end]: ");
        if (line == "quit"
                || advanceColony(display, colony)) {
            break;
        }
    }
}

static void runAnimation(LifeDisplay& display, Grid<int>& colony, int ms) {
    GTimer timer(ms);
    timer.start();
    while (true) {
        GEvent e = waitForEvent(TIMER_EVENT + MOUSE_EVENT);
        if (e.getEventClass() == TIMER_EVENT) {
            if (advanceColony(display, colony)) {
                break;
            }
        } else if (e.getEventType() == MOUSE_PRESSED) {
             break;
        }
    }
    timer.stop();
}

static bool advanceColony(LifeDisplay& display, Grid<int>& colony) {
    bool isStable = false;
    calculateNextGeneration(colony, isStable);
    displayColony(display, colony);
    return isStable;
}

static void calculateNextGeneration(Grid<int>& colony, bool& isStable) {
    Grid<int> nextGeneration(colony.height(), colony.width(), 0);

    for (int r = 0; r < nextGeneration.height(); ++r) {
        for (int c = 0; c < nextGeneration.width(); ++c) {
            int aliveNeighbors = getAliveNeighbors(colony, r, c);

            if (aliveNeighbors == 2 && colony[r][c] > 0) {
                nextGeneration[r][c] = colony[r][c] + 1;
            } else if (aliveNeighbors == 3) {
                nextGeneration[r][c] = colony[r][c] + 1;
            } else if (aliveNeighbors > 3) {
                nextGeneration[r][c] = 0;
            }
        }
    }

    isStable = isColonyStable(colony, nextGeneration);
    colony = nextGeneration;
}

static int getAliveNeighbors(const Grid<int>& colony, int row, int col) {
    int aliveCells = 0;

    for (int r = row - 1; r <= row + 1; ++r) {
        for (int c = col - 1; c <= col + 1; ++c) {
            if (colony.inBounds(r, c) && colony[r][c] > 0) {
                ++aliveCells;
            }
        }
    }

    return colony[row][col] > 0 ? aliveCells - 1 : aliveCells;
}

static bool isColonyStable(const Grid<int>& oldColony, const Grid<int>& advancedColony) {
    for (int r = 0; r < advancedColony.height(); ++r) {
        for (int c = 0; c < advancedColony.width(); ++c) {
            auto oldCell = oldColony[r][c];
            auto newCell = advancedColony[r][c];

            if (oldCell != newCell && newCell < kMaxAge) {
                return false;
            }
        }
    }

    return true;
}

static void displayColony(LifeDisplay& display, const Grid<int>& colony) {
    for (int i = 0; i < colony.height(); ++i) {
        for (int j = 0; j < colony.width(); ++j) {
            display.drawCellAt(i, j, colony[i][j]);
        }
    }
    display.repaint();
}
