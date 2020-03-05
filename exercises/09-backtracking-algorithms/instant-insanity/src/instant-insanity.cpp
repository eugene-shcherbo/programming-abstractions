#include <iostream>
#include "console.h"
#include "vector.h"
#include "cube.h"

using namespace std;

const int N_CUBES = 4;
const int N_ROTATIONS = 4;
const int N_CUBE_FACES = 6;

bool solveInstantInsanity(const Vector<Cube>& cubes, Vector<Cube>& sol);
bool isValidPosition(const Vector<Cube>& cubes, const Cube& cube);
void printCubes(const Vector<Cube>& cubes);

void checkSolution(const Vector<Cube>& cubes) {
    Vector<Cube> sol;

    if (solveInstantInsanity(cubes, sol)) {
        cout << "There is solution for this configuration" << endl;
        printCubes(sol);
    } else {
        cout << "There are no solutions" << endl;
    }
}

int main() {
    Vector<Cube> cubes {
        Cube(BLACK, WHITE, BLACK, RED, GREEN, GREEN),
        Cube(GREEN, WHITE, WHITE, BLACK, GREEN, RED),
        Cube(WHITE, RED, RED, BLACK, GREEN, WHITE),
        Cube(RED, GREEN, RED, RED, WHITE, BLACK)
    };

    checkSolution(cubes);

    Vector<Cube> noSol {
        Cube(WHITE, WHITE, GREEN, BLACK, WHITE, RED),
        Cube(RED, RED, BLACK, GREEN, WHITE, BLACK),
        Cube(RED, RED, GREEN, BLACK, WHITE, BLACK),
        Cube(RED, GREEN, GREEN, RED, WHITE, BLACK)
    };

    checkSolution(noSol);

    return 0;
}

bool solveInstantInsanity(const Vector<Cube>& cubes, Vector<Cube>& sol) {
    if (sol.size() == N_CUBES) return true;

    Cube c = cubes[sol.size()];

    for (int f = 0; f < N_CUBE_FACES; f++) {
        c.rotateUntilFace(f);

        for (int r = 0; r < N_ROTATIONS; r++) {
            c.rotateY(r);

            if (isValidPosition(sol, c)) {
                sol.add(c);

                if (solveInstantInsanity(cubes, sol)) {
                    return true;
                }

                sol.removeBack();
            }
        }
    }

    return false;
}

bool isValidPosition(const Vector<Cube>& cubes, const Cube& cube) {
    for (const Cube& c: cubes) {
        if (cube.isIntersected(c)) {
            return false;
        }
    }

    return true;
}

void printCubes(const Vector<Cube>& cubes) {
    for (const Cube& c: cubes) {
        c.print();
    }
}


