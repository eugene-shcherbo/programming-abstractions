#include <iostream>
#include <fstream>
#include "console.h"
#include "graphtypes.h"
#include "vector.h"

using namespace std;

void visit(Vertex*);

void measurePerformance(Vertex* start, void (*fn)(void (*)(Vertex*), Vertex*, double&, long long&)) {
    double avgQueueSize = 0;
    long long totalTime = 0L;
    fn(visit, start, avgQueueSize, totalTime);
    cout << "avg queue size: " << avgQueueSize << "; total time: " << totalTime;
}

void testCase(const string& graphFileName) {
    ifstream file(graphFileName);
    SimpleGraph g;
    readGraph(g, file);
    Vertex* randVertex = g.vertexSet.first();

    cout << "Test case for '" << graphFileName << "'. Start Node is " << randVertex->name << endl;
    cout << "\t - without test - ";
    measurePerformance(randVertex, bfs);
    cout << endl << "\t - with test - ";
    measurePerformance(randVertex, bfsEfficient);

    cout << endl << endl;
}

int main() {
    Vector<string> graphFiles {
        "airline.txt",
        "graph-1.txt",
        "graph-2.txt",
        "graph-3.txt"
    };

    for (string file: graphFiles) {
        testCase(file);
    }

    return 0;
}

void visit(Vertex*) {
}

