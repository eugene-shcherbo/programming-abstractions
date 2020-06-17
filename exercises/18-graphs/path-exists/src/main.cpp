#include <iostream>
#include <fstream>
#include "console.h"
#include "graphtypes.h"
#include "vector.h"

using namespace std;

void printHops(Vertex* from, Vertex* to) {
    cout << "hops from " << from->name << " to " << to->name << " = " << hopCount(from, to) << endl;
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

    printHops(atlanta, dallas);
    printHops(atlanta, boston);
    printHops(atlanta, sa);

    return 0;
}

