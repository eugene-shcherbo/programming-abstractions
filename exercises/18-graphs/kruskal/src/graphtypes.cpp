#include <chrono>
#include "strlib.h"
#include "map.h"
#include "set.h"
#include "stack.h"
#include "queue.h"
#include "priorityqueue.h"
#include "graphtypes.h"

void visitUsingDfs(Vertex* from, Set<Vertex*>& visited);

void dfs(void (*fn)(Vertex*), Vertex* from) {
    Set<Vertex*> visited;
    Stack<Vertex*> neighbours;
    neighbours.push(from);

    while (!neighbours.isEmpty()) {
        Vertex* v = neighbours.pop();
        if (!visited.contains(v)) {
            fn(v);
            visited.add(v);

            for (Edge* e: v->edges) {
                neighbours.push(e->finish);
            }
        }
    }
}

void bfs(void (*fn)(Vertex*), Vertex* start) {
    Set<Vertex*> visited;
    Queue<Vertex*> toVisit;
    toVisit.enqueue(start);
    while (!toVisit.isEmpty()) {
        Vertex* v = toVisit.dequeue();
        fn(v);
        for (Edge* e: v->edges) {
            if (!visited.contains(e->finish)) {
                visited.add(e->finish);
                toVisit.enqueue(e->finish);
            }
        }
    }
}

bool pathExists(Vertex* from, Vertex* to) {
    if (from == to) {
        return true;
    }

    Queue<Vertex*> toVisit;
    Set<Vertex*> visited;
    toVisit.enqueue(from);

    while (!toVisit.isEmpty()) {
        Vertex* vertex = toVisit.dequeue();

        for (Edge* e: vertex->edges) {
            if (e->finish == to) {
                return true;
            } else if (!visited.contains(e->finish)) {
                visited.add(e->finish);
                toVisit.enqueue(e->finish);
            }
        }
    }

    return false;
}

int hopCount(Vertex* from, Vertex* to) {
    if (from == to) {
        return 0;
    }

    Queue<Vertex*> toVisit;
    Set<Vertex*> visited;
    toVisit.enqueue(from);
    int hops = 0;

    while (!toVisit.isEmpty()) {
        hops++;
        Vertex* vertex = toVisit.dequeue();

        for (Edge* e: vertex->edges) {
            if (e->finish == to) {
                return hops;
            } else if (!visited.contains(e->finish)) {
                visited.add(e->finish);
                toVisit.enqueue(e->finish);
            }
        }
    }

    return -1;
}

int getPathCost(Vector<Edge*> path) {
    int cost = 0;
    for (Edge* e: path) {
        cost += e->weigth;
    }
    return cost;
}

Vector<Edge*> findShortestPath(Vertex* start, Vertex* finish) {
    Set<std::string> visited;
    PriorityQueue<Vector<Edge*>> toProceed;
    Vector<Edge*> path;

    while (start != finish) {
        visited.add(start->name);
        for (Edge* e : start->edges) {
            if (!visited.contains(e->finish->name)) {
                path.add(e);
                toProceed.enqueue(path, getPathCost(path));
                path.removeBack();
            }
        }

        if (toProceed.isEmpty()) {
            return Vector<Edge*>();
        }

        path = toProceed.dequeue();
        start = path[path.size() - 1]->finish;
    }

    return path;
}

bool canSplitBetweenSets(Set<Vertex*>& one, Set<Vertex*>& two, Vertex* start, Vertex* finish) {
    return (!one.contains(start) && !one.contains(finish))
           || (!two.contains(start) && !two.contains(finish));
}

void moveVertexToSet(Set<Vertex*>& one, Set<Vertex*>& two, Vertex* v, Vertex* connected) {
    if (one.contains(v) || two.contains(v)) return;

    if (!one.contains(v) && !one.contains(connected)) {
        one.add(v);
    } else if (one.contains(connected)) {
        two.add(v);
    }
}

bool isBipartite(SimpleGraph& g) {
    Set<Vertex*> one;
    Set<Vertex*> two;
    Map<Vertex*, Vertex*> connections;

    for (Edge* e: g.edgeSet) {
        if (connections.containsKey(e->finish) && connections[e->finish] == e->start) continue;
        if (!canSplitBetweenSets(one, two, e->start, e->finish)) return false;

        moveVertexToSet(one, two, e->start, e->finish);
        moveVertexToSet(one, two, e->finish, e->start);

        connections.add(e->start, e->finish);
    }

    return true;
}

bool isRedundant(Vertex* v, Set<Vertex*>& dominationNeighbours) {
    if (!dominationNeighbours.contains(v)) return false;
    for (Edge* e : v->edges) {
        if (!dominationNeighbours.contains(e->finish)) return false;
    }
    return true;
}

Set<Vertex*> findDominatingSet(SimpleGraph& g) {
    Set<Vertex*> dominatingSet;
    Set<Vertex*> dominatingNeighbours;

    PriorityQueue<Vertex*> pq;
    for (Vertex* v : g.vertexSet) {
        pq.enqueue(v, -v->edges.size());
    }

    while (!pq.isEmpty()) {
        Vertex* v = pq.dequeue();
        if (!isRedundant(v, dominatingNeighbours)) {
            dominatingSet.add(v);

            for (Edge* e : v->edges) {
                dominatingNeighbours.add(e->finish);
            }
        }
    }

    return dominatingSet;
}
