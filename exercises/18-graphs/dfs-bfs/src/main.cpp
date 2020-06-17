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

    cout << endl << "---DFS---" << endl;
    dfs(visit, g.vertexSet.first());

    cout << endl << "---BFS---" << endl;
    bfs(visit, g.vertexSet.first());

    return 0;
}

void visit(Vertex* v) {
    cout << "vertex visited = " << v->name << endl;
}

