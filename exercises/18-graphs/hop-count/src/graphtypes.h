#ifndef _graphtypes_h_
#define _graphtypes_h_

#include <string>
#include <iostream>
#include "set.h"
#include "map.h"

struct Vertex;
struct Edge;

struct SimpleGraph {
    Set<Vertex*> vertexSet;
    Set<Edge*> edgeSet;
    Map<std::string, Vertex*> vertexMap;
};

struct Vertex {
    std::string name;
    Set<Edge*> edges;
};

struct Edge {
    Vertex* start;
    Vertex* finish;
    int weigth;
};

void readGraph(SimpleGraph& g, std::istream& in);
void writeGraph(SimpleGraph& g, std::ostream& os);

void dfs(void (*fn)(Vertex*), Vertex* start);
void bfs(void (*fn)(Vertex*), Vertex* start);
bool pathExists(Vertex* from, Vertex* to);

#endif
