#include "trailblazer.h"
#include "stack.h"
#include "queue.h"
#include "vector.h"
#include "pqueue.h"
#include "bfsalgorithm.h"
#include "dijkstraalgorithm.h"
#include "astaralgorithm.h"

using namespace std;

bool findPathUsingDfs(BasicGraph& graph, Vertex* curr, Vertex* end, Vector<Vertex*>& path);
void visitVertex(Vertex* v, Vector<Vertex*>& path);
void makeVertexDeadEnd(Vertex* v, Vector<Vertex*>& path);

Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    Vector<Vertex*> path;
    findPathUsingDfs(graph, start, end, path);
    return path;
}

bool findPathUsingDfs(BasicGraph& graph, Vertex* curr, Vertex* end, Vector<Vertex*>& path) {
    visitVertex(curr, path);
    if (curr == end) return true;

    for (Vertex* n : graph.getNeighbors(curr)) {
        if (!n->visited && findPathUsingDfs(graph, n, end, path))
            return true;
    }

    makeVertexDeadEnd(curr, path);
    return false;
}

void visitVertex(Vertex* v, Vector<Vertex*>& path) {
    path.add(v);
    v->setColor(GREEN);
    v->visited = true;
}

void makeVertexDeadEnd(Vertex* v, Vector<Vertex*>& path) {
    path.remove(path.size() - 1);
    v->setColor(GRAY);
}

Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    return BFSAlgorithm().search(graph, start, end);
}

Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    return DijkstraAlgorithm().search(graph, start, end);
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    return AStarAlgorithm().search(graph, start, end);
}

Set<Edge*> kruskal(BasicGraph& graph) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty set so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Set<Edge*> mst;
    return mst;
}
