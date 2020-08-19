#include <iostream>
#include <fstream>
#include "console.h"
#include "graphtypes.h"
#include "graph.h"
#include "graphio.h"
#include "queue.h"

using namespace std;

Graph<Vertex, Edge>* createGraphFromFile(string filename);

void dvaHelper(Vertex* previous, Vertex* vertex, Graph<Vertex, Edge>& network, Set<Vertex*>& visited) {
    if (visited.contains(vertex)) return;
    visited.add(vertex);

    for (Vertex* n: network.getNeighbors(vertex)) {
        n->updateRoutingTable(vertex);
        dvaHelper(vertex, n, network, visited);
    }

    previous->updateRoutingTable(vertex);
}

void distanceVectorAlgorithm2(Graph<Vertex, Edge>& network) {
    Vertex* start = network.getNodeSet().first();

    for (Vertex* n: network.getNeighbors(start)) {
        Set<Vertex*> visited;
        n->updateRoutingTable(start);
        dvaHelper(start, n, network, visited);
    }
}

void distanceVectorAlgorithm1(Graph<Vertex, Edge>& network) {
    for (Vertex* v: network.getNodeSet()) v->buildRoutingTable(network.getNeighbors(v));

    for (int i = 0; i < network.getNodeSet().size() - 1; i++) {
        for (Vertex* v: network.getNodeSet()) {
            for (Vertex* n: network.getNeighbors(v)) {
                v->updateRoutingTable(n);
            }
        }
    }
}

int main() {
    Graph<Vertex, Edge>* graph = createGraphFromFile("large-graph.txt");
    distanceVectorAlgorithm1(*graph);
    distanceVectorAlgorithm2(*graph);

    delete graph;

    return 0;
}

Graph<Vertex, Edge>* createGraphFromFile(string filename) {
    ifstream infile(filename);
    if (infile.fail()) throw "incorrect file name";
    Graph<Vertex, Edge>* g = new Graph<Vertex, Edge>();
    readGraph(*g, infile);
    return g;
}
