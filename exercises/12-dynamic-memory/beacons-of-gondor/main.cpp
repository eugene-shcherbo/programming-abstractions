#include <iostream>

using namespace std;

struct Tower {
    string name;
    Tower* link;
};

Tower* createBeaconsOfGondor();
Tower* createTower(string name, Tower* link);
void signal(Tower* start);
void freeBeacons(Tower* start);

int main()
{
    Tower* list = createBeaconsOfGondor();
    signal(list);
    freeBeacons(list);

    return 0;
}

Tower* createBeaconsOfGondor() {
    Tower* tp = createTower("Rohan", nullptr);
    tp = createTower("Halifirien", tp);
    tp = createTower("Calenhand", tp);
    tp = createTower("Min-Rimon", tp);
    tp = createTower("Erelas", tp);
    tp = createTower("Nardol", tp);
    tp = createTower("Eilenach", tp);
    tp = createTower("Amon Din", tp);

    return createTower("Minas Tirith", tp);
}

Tower* createTower(string name, Tower* link) {
    return new Tower{name, link};
}

void signal(Tower* start) {
    for (Tower* tp = start; tp != nullptr; tp = tp->link) {
        cout << "Lighting " << tp->name << endl;
    }
}

void freeBeacons(Tower* start) {
    if (start != nullptr) {
        freeBeacons(start->link);
        delete start;
    }
}
