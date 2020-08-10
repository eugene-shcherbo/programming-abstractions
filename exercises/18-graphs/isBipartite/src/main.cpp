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
    SimpleGraph* bipartiteGraph = createGraphFromFile("bipartite.txt");
    SimpleGraph* nonBipartiteGraph = createGraphFromFile("nonBipartite.txt");

    cout << "isBipartite? TRUE == " << boolToString(isBipartite(*bipartiteGraph)) << "?" << endl;
    cout << "isBipartite? FALSE == " << boolToString(isBipartite(*nonBipartiteGraph)) << "?" << endl;

    return 0;
}

SimpleGraph* createGraphFromFile(string filename) {
    ifstream infile(filename);
    if (infile.fail()) throw "incorrect file name";
    SimpleGraph* g = new SimpleGraph();
    readGraph(*g, infile);
    return g;
}

