#ifndef BFSALGORITHM_H_
#define BFSALGORITHM_H_

#include "pathfinder.h"
#include "queue.h"

class BFSAlgorithm : public PathFinder {

private:
    Queue<Vertex*> toProcess;

    virtual void init(Vertex* start);

    virtual Vertex* nextVertex();
    virtual bool canProceed();
    virtual void processNeighbourOf(Vertex* vertex, Vertex* neighbour, Vertex* end, BasicGraph& graph);
};

#endif // BFSALGORITHM_H_
