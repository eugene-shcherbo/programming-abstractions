#include <iostream>
#include <fstream>
#include "console.h"
#include "graphtypes.h"
#include "vector.h"

using namespace std;

void printIfThereIsWay(Vertex* from, Vertex* to) {
    string way = "from " + from->name + " to " + to->name;
    cout << (pathExists(from, to) ? "There is a way " + way : "There is no way " + way) << endl;
}

int main() {
    SimpleGraph g;
    ifstream infile("airline.txt");
    readGraph(g, infile);
    infile.close();

    Vertex* atlanta = g.vertexMap["Atlanta"];
    Vertex* dallas = g.vertexMap["Dallas"];
    Vertex* boston = g.vertexMap["Boston"];
    Vertex* sa = g.vertexMap["San Francisco"];

    printIfThereIsWay(atlanta, dallas);
    printIfThereIsWay(atlanta, boston);
    printIfThereIsWay(atlanta, sa);

    return 0;
}

