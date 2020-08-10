#include <iostream>
#include <fstream>
#include "console.h"
#include "graphtypes.h"
#include "vector.h"
#include "filelib.h"

using namespace std;

void prompUserForVertexes(SimpleGraph& g, Vertex*& v1, Vertex*& v2);
string promptUserForVertexName(SimpleGraph& g, string prompt);

int main() {
    ifstream infile;
    promptUserForFile(infile, "enter a filename with a graph: ");

    SimpleGraph graph;
    readGraph(graph, infile);
    infile.close();

    Vertex* start = nullptr;
    Vertex* finish = nullptr;
    prompUserForVertexes(graph, start, finish);
    Vector<Edge*> shortestPath = findShortestPath(start, finish);

    if (shortestPath.size() == 0) {
        cout << "there is no path" << endl;
    } else {
        for (int i = 0; i < shortestPath.size(); i++) {
            cout << shortestPath[i]->start->name << " -> ";
        }
        cout << finish->name << " (" << getPathCost(shortestPath) << ")"  << endl;
    }

    return 0;
}

void prompUserForVertexes(SimpleGraph& g, Vertex*& v1, Vertex*& v2) {
    string vName1 = promptUserForVertexName(g, "enter of name for source vertex: ");
    string vName2 = promptUserForVertexName(g, "enter of name for destination vertex: ");
    v1 = g.vertexMap[vName1];
    v2 = g.vertexMap[vName2];
}

string promptUserForVertexName(SimpleGraph& g, string prompt) {
    while (true) {
        cout << prompt;
        string line;
        getline(cin, line);

        if (g.vertexMap.containsKey(line)) {
            return line;
        }

        cout << "there is no vertexes with that name. Try again." << endl;
    }
}

