#include <iostream>
#include <fstream>
#include "console.h"
#include "graphtypes.h"
#include "vector.h"
#include "filelib.h"
#include "strlib.h"
#include "graph.h"
#include "graphio.h"
#include "pqueue.h"

using namespace std;

Graph<Vertex, Edge>* createGraphFromFile(string filename);
Graph<Vertex, Edge> findMinimumSpanningTree(Graph<Vertex, Edge>& g);

int main() {
    Graph<Vertex, Edge>* graph = createGraphFromFile("cable-system.txt");
    Graph<Vertex, Edge> minimumSpanningTree = findMinimumSpanningTree(*graph);

    return 0;
}

Graph<Vertex, Edge>* createGraphFromFile(string filename) {
    ifstream infile(filename);
    if (infile.fail()) throw "incorrect file name";
    Graph<Vertex, Edge>* g = new Graph<Vertex, Edge>();
    readGraph(*g, infile);
    return g;
}

void addEdge(Graph<Vertex, Edge>& g, Vertex* v1, Vertex* v2, int cost) {
    Edge* newEdge = new Edge();
    newEdge->start = v1;
    newEdge->finish = v2;
    newEdge->weigth = cost;
    v1->edges.add(newEdge);
    g.addArc(newEdge);
}

Graph<Vertex, Edge> findMinimumSpanningTree(Graph<Vertex, Edge>& g) {
    Graph<Vertex, Edge> tree;
    PriorityQueue<Edge*> edges;

    for (Vertex* v: g.getNodeSet()) {
        Vertex* newVertex = new Vertex();
        newVertex->name = v->name;
        tree.addNode(newVertex);
    }

    for (Edge* e: g.getArcSet()) {
        edges.enqueue(e, e->weigth);
    }

    cout << "Process edges in order of cost:" << endl;

    while (!edges.isEmpty()) {
        Edge* e = edges.dequeue();
        Vertex* v1 = tree.getNode(e->start->name);
        Vertex* v2 = tree.getNode(e->finish->name);

        cout << e->weigth << ": " << v1->name << " - " << v2->name;

        if (!pathExists(v1, v2)) {
            addEdge(tree, v1, v2, e->weigth);
            addEdge(tree, v2, v1, e->weigth);
        } else {
            cout << " (not needed) ";
        }

        cout << endl;
    }

    return tree;
}
