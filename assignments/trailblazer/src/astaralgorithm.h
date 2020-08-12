#ifndef ASTARALGORITHM_H_
#define ASTARALGORITHM_H_

#include "pathfinder.h"
#include "pqueue.h"

class AStarAlgorithm : public PathFinder {

private:
    PriorityQueue<Vertex*> toProcess;
    virtual double heuristic(Vertex* from, Vertex* to);
    Vertex* nextVertex() override;
    bool canProceed() override;
    void processNeighbourOf(Vertex* vertex, Vertex* neighbour, Vertex* end, BasicGraph& graph) override;
    void init(Vertex* start) override;
};

#endif // ASTARALGORITHM_H_
