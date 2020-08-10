#include <iostream>
#include <fstream>
#include "console.h"
#include "graphtypes.h"
#include "vector.h"
#include "filelib.h"
#include "strlib.h"

using namespace std;

SimpleGraph* createGraphFromFile(string filename);

int main() {
    SimpleGraph* graph = createGraphFromFile("graph.txt");
    Set<Vertex*> dominatingSet = findDominatingSet(*graph);

    for (Vertex* v: dominatingSet) {
        cout << v->name << endl;
    }

    return 0;
}

SimpleGraph* createGraphFromFile(string filename) {
    ifstream infile(filename);
    if (infile.fail()) throw "incorrect file name";
    SimpleGraph* g = new SimpleGraph();
    readGraph(*g, infile);
    return g;
}

