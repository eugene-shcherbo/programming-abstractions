#include <iostream>
#include <fstream>

using namespace std;

struct Tower {
    string name;
    Tower* link;
};

Tower* readBeaconsFromFile(const string& filename);
Tower* readBeaconsHelper(ifstream& infile);
Tower* createTower(string name, Tower* link);
void signal(Tower* start);
void freeBeacons(Tower* start);

int main() {
    Tower* list = readBeaconsFromFile("BeaconsOfGondor.txt");
    signal(list);
    freeBeacons(list);

    return 0;
}

Tower* readBeaconsFromFile(const string& filename) {
    ifstream infile(filename);
    Tower* tower = readBeaconsHelper(infile);

    if (infile.is_open()) infile.close();

    return tower;
}

Tower* readBeaconsHelper(ifstream& infile) {
    string line;

    if (getline(infile, line)) {
        return createTower(line, readBeaconsHelper(infile));
    } else {
        return nullptr;
    }
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
