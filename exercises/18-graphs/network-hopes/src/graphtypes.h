#ifndef _graphtypes_h_
#define _graphtypes_h_

#include <string>
#include <iostream>
#include "set.h"
#include "map.h"
#include "vector.h"
#include "strlib.h"

struct Vertex;
struct Edge;

struct Vertex {
    std::string name;
    Set<Edge*> arcs;

    void updateRoutingTable(Vertex* neighbour) {
        for (Vertex* v: neighbour->routingTable) {
            if (!routingTable.containsKey(v)) {
                routingTable.add(v, neighbour->routingTable[v] + 1);
            } else if (routingTable[v] > neighbour->routingTable[v] + 1) {
                routingTable[v] = neighbour->routingTable[v] + 1;
            }
        }
    }

    void buildRoutingTable(Set<Vertex*> neighbours) {
        for (Vertex* neighbour: neighbours) {
            routingTable.add(neighbour, 1);
        }

        routingTable[this] = 0;
    }

private:
    Map<Vertex*, int> routingTable;
};

struct Edge {
    Vertex* start;
    Vertex* finish;
    int weigth;
};

void dfs(void (*fn)(Vertex*), Vertex* start);
void bfs(void (*fn)(Vertex*), Vertex* start);
bool pathExists(Vertex* from, Vertex* to);
int hopCount(Vertex* from, Vertex* to);

int getPathCost(Vector<Edge*> path);
Vector<Edge*> findShortestPath(Vertex* v1, Vertex* v2);

#endif
