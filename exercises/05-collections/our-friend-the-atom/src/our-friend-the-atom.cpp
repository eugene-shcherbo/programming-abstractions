#include <iostream>
#include <iomanip>
#include "grid.h"
#include "vector.h"
#include "console.h"

constexpr short ROOM_SIZE = 25;
constexpr short MIN_FLIGHT_TIME = 1;
constexpr short MAX_FLIGHT_TIME = 4;

using namespace std;

void runSimulation(int& timeUnits, int& maxBalls, int& sprungPerc);
void printResult(int timeUnits, int maxBalls, int sprungPerc);

int main() {
    int timeUnits;
    int maxBalls;
    int sprungPerc;
    runSimulation(timeUnits, maxBalls, sprungPerc);
    printResult(timeUnits, maxBalls, sprungPerc);

    return 0;
}

void runSimulation(int& timeUnits, int& maxBalls, int& sprungPerc) {
    setRandomSeed(static_cast<int>((time(NULL))));

    Grid<bool> mousetraps(ROOM_SIZE, ROOM_SIZE, true);
    Vector<int> balls;

    balls.add(randomInteger(MIN_FLIGHT_TIME, MAX_FLIGHT_TIME));

    timeUnits = 0;
    maxBalls = 0;
    sprungPerc = 0;

    int sprungTraps = 0;

    while (!balls.isEmpty()) {
        int ballsNum = balls.size();

        for (int i = ballsNum - 1; i >= 0; --i) {
            if (balls[i] > 0) {
                --balls[i];
            } else {
                int fellRow = randomInteger(0, ROOM_SIZE - 1);
                int fellCol = randomInteger(0, ROOM_SIZE - 1);
                balls.remove(i);

                if (mousetraps[fellRow][fellCol]) {
                    balls.add(randomInteger(MIN_FLIGHT_TIME, MAX_FLIGHT_TIME));
                    balls.add(randomInteger(MIN_FLIGHT_TIME, MAX_FLIGHT_TIME));
                    mousetraps[fellRow][fellCol] = false;
                    ++sprungTraps;
                }
            }
        }

        maxBalls = max(ballsNum, maxBalls);
        ++timeUnits;
    }

    sprungPerc = (sprungTraps * 100) / (ROOM_SIZE * ROOM_SIZE);
}

void printResult(int timeUnits, int maxBalls, int sprungPerc) {
    cout << "\t\t\tSimulation results: " << endl;
    cout << "Time units passed:   " << setw(4) << timeUnits << endl;
    cout << "Max balls amount has been fixed:   " << setw(4) << maxBalls << endl;
    cout << "Percentage of the sprung traps:   " << setw(4) << sprungPerc << endl;
}
