#include "trailblazer.h"
#include "stack.h"
#include "queue.h"
#include "vector.h"
#include "pqueue.h"
#include "bfsalgorithm.h"
#include "dijkstraalgorithm.h"
#include "astaralgorithm.h"
#include "map.h"

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

int findClusterIndex(Vector<Set<Vertex*>>& clusters, Vertex* v) {
    for (int i = 0; i < clusters.size(); i++) {
        if (clusters[i].contains(v)) {
            return i;
        }
    }

    return -1;
}

Set<Edge*> kruskal(BasicGraph& graph) {
    Vector<Set<Vertex*>> clusters;
    int numOfClusters = graph.getVertexSet().size();

    for (Vertex* v: graph.getVertexSet()) {
        Set<Vertex*> cluster;
        cluster.add(v);
        clusters.add(cluster);
    }

    PriorityQueue<Edge*> toProcess;
    for (Edge* edge: graph.getEdgeSet()) {
        toProcess.enqueue(edge, edge->weight);
    }

    Set<Edge*> mst;
    while (numOfClusters > 1) {
        Edge* e = toProcess.dequeue();
        int startClusterIndex = findClusterIndex(clusters, e->start);
        int finishClusterIndex = findClusterIndex(clusters, e->finish);

        if (startClusterIndex != finishClusterIndex) {
            clusters[startClusterIndex].addAll(clusters[finishClusterIndex]);
            clusters.remove(finishClusterIndex);
            mst.add(e);
            numOfClusters--;
        }
    }

    return mst;
}
