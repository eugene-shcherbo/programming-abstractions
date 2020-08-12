#include "astaralgorithm.h"

void AStarAlgorithm::init(Vertex* start) {
    start->cost = 0;
    toProcess.enqueue(start, start->cost);
}

bool AStarAlgorithm::canProceed() {
    return !toProcess.isEmpty();
}

void AStarAlgorithm::processNeighbourOf(Vertex* vertex, Vertex* neighbour, Vertex* end, BasicGraph& graph) {
    double cost = vertex->cost + graph.getEdge(vertex, neighbour)->cost;

    if (cost <= neighbour->cost) {
        neighbour->cost = cost;
        neighbour->previous = vertex;

        if (isEnqueued(neighbour)) {
            toProcess.changePriority(neighbour, neighbour->cost + heuristic(neighbour, end));
        } else {
            toProcess.enqueue(neighbour, neighbour->cost + heuristic(neighbour, end));
            neighbour->setColor(YELLOW);
        }
    }
}

double AStarAlgorithm::heuristic(Vertex* from, Vertex* to) {
    return heuristicFunction(from, to);
}

Vertex* AStarAlgorithm::nextVertex() {
    return toProcess.dequeue();
}
