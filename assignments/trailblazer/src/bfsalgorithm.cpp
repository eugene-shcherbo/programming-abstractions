#include "bfsalgorithm.h"

void BFSAlgorithm::init(Vertex* start) {
    toProcess.enqueue(start);
}

Vertex* BFSAlgorithm::nextVertex() {
    return toProcess.dequeue();
}

bool BFSAlgorithm::canProceed() {
    return !toProcess.isEmpty();
}

void BFSAlgorithm::processNeighbourOf(Vertex* vertex, Vertex* neighbour, Vertex* end, BasicGraph& graph) {
    if (!isEnqueued(neighbour)) {
        toProcess.enqueue(neighbour);
        neighbour->setColor(YELLOW);
        neighbour->previous = vertex;
    }
}
