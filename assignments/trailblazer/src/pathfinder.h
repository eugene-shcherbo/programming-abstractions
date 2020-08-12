#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include "vector.h"
#include "basicgraph.h"
#include "trailblazer.h"

class PathFinder {
public:
    Vector<Vertex*> search(BasicGraph& graph, Vertex* start, Vertex* end);

protected:
    bool isEnqueued(Vertex* v);
    virtual void init(Vertex* start) = 0;
    virtual bool canProceed() = 0;
    virtual void processNeighbourOf(Vertex* vertex, Vertex* neighbour, Vertex* end, BasicGraph& graph) = 0;
    virtual Vertex* nextVertex() = 0;

private:
    Vector<Vertex*> path;
    void initGraph(BasicGraph& graph);
    void visitVertex(Vertex* v);
    Vector<Vertex*>& reconstructPath(Vertex* end);

};

#endif // PATHFINDER_H_
