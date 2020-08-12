#include "pathfinder.h"

Vector<Vertex*> PathFinder::search(BasicGraph& graph, Vertex* start, Vertex* end) {
    initGraph(graph);
    init(start);

    while (canProceed()) {
        Vertex* v = nextVertex();
        visitVertex(v);
        if (v == end) break;

        for (Vertex* n: graph.getNeighbors(v)) {
            if (n->visited) continue;
            processNeighbourOf(v, n, end, graph);
        }
    }

    return reconstructPath(end);
}

bool PathFinder::isEnqueued(Vertex* v) {
    return v->getColor() == YELLOW;
}

void PathFinder::initGraph(BasicGraph& graph) {
    graph.resetData();
    for (Vertex* v: graph.getVertexSet())
        v->cost = POSITIVE_INFINITY;
}

void PathFinder::visitVertex(Vertex* v) {
    v->setColor(GREEN);
    v->visited = true;
}

Vector<Vertex*>& PathFinder::reconstructPath(Vertex* end) {
    if (!end->visited) return path;

    Stack<Vertex*> tempPath;
    for (Vertex* curr = end; curr != nullptr; curr = curr->previous)
        tempPath.push(curr);

    while (!tempPath.isEmpty())  path.add(tempPath.pop());

    return path;
}
