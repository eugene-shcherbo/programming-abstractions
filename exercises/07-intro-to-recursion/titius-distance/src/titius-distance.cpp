#include <iostream>
#include "vector.h"
#include "console.h"

using namespace std;

const Vector<string> PLANETS {
    "Mercury",
    "Venus",
    "Earth",
    "Mars",
    "?",
    "Jupiter",
    "Saturn",
    "Uranus"
};

void printTitusDistance();
double getTitiusBodeDistance(int k);
int twiceSequence(int k);

int main() {
    printTitusDistance();

    return 0;
}

void printTitusDistance() {
    for (int i = 0; i < PLANETS.size(); ++i) {
        cout << PLANETS[i] << '\t' << getTitiusBodeDistance(i + 1) << " AU" << endl;
    }
}

double getTitiusBodeDistance(int k) {
    return (4 + static_cast<double>(twiceSequence(k))) / 10;
}

int twiceSequence(int k) {
    if (k <= 1) {
        return k;
    } else if (k == 2) {
        return 3;
    } else {
        return 2 * twiceSequence(k - 1);
    }
}
