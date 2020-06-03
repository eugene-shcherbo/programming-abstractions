#include <iostream>
#include <fstream>
#include "console.h"
#include "graphtypes.h"

using namespace std;

void visit(Vertex* v);

int main() {
    SimpleGraph g;
    ifstream infile("airline.txt");
    readGraph(g, infile);
    infile.close();
    writeGraph(g, cout);

    cout << endl << "---DFS RECURSIVE---" << endl;
    dfsTraverseRecursive(g.vertexSet.first());

    cout << endl << "---DFS ITERATIVE---" << endl;
    dfsTraverseIterative(g.vertexSet.first());

    return 0;
}

void visit(Vertex* v) {
    cout << "vertex visited = " << v->name << endl;
}

