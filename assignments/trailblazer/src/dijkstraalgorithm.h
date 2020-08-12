#ifndef DIJKSTRAALGORITHM_H_
#define DIJKSTRAALGORITHM_H_

#include "astaralgorithm.h"

class DijkstraAlgorithm : public AStarAlgorithm {
    double heuristic(Vertex* /*from*/, Vertex* /*to*/) override {
        return .0;
    }
};

#endif // DIJKSTRAALGORITHM_H_
