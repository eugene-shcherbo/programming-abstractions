#include "trailblazer.h"
#include "stack.h"
#include "queue.h"
#include "vector.h"
#include "pqueue.h"

using namespace std;

bool findPathUsingDfs(BasicGraph& graph, Vertex* curr, Vertex* end, Vector<Vertex*>& path);
void visitVertex(Vertex* v, Vector<Vertex*>& path);
void makeVertexDeadEnd(Vertex* v, Vector<Vertex*>& path);

Vector<Vertex*>& makeSingleStepPath(Vector<Vertex*>& path, Vertex* step);
void initBFS(BasicGraph& graph, Queue<Vertex*>& toProcess, Vertex* start);
Vector<Vertex*>& reconstructPath(Vector<Vertex*>& path, Vertex* end);

void initDijkstra(BasicGraph& graph, PriorityQueue<Vertex*>& toProcess, Vertex* start);
void visitVertex(Vertex* v);

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
    Vector<Vertex*> path;
    Queue<Vertex*> toProcess;
    initBFS(graph, toProcess, start);

    if (start == end) return makeSingleStepPath(path, start);

    while (!toProcess.isEmpty() && !end->visited) {
        Vertex* v = toProcess.dequeue();
        visitVertex(v);

        for (Vertex* n: graph.getNeighbors(v)) {
            if (!n->visited && n->getColor() != YELLOW) {
                toProcess.enqueue(n);
                n->previous = v;
                n->setColor(YELLOW);
            }
        }
    }

    return reconstructPath(path, end);
}

Vector<Vertex*>& makeSingleStepPath(Vector<Vertex*>& path, Vertex* step) {
    path.add(step);
    return path;
}

void initBFS(BasicGraph& graph, Queue<Vertex*>& toProcess, Vertex* start) {
    graph.resetData();
    toProcess.enqueue(start);
    start->setColor(GREEN);
}

Vector<Vertex*>& reconstructPath(Vector<Vertex*>& path, Vertex* end) {
    if (!end->visited) return path;

    Stack<Vertex*> tempPath;
    for (Vertex* curr = end; curr != nullptr; curr = curr->previous)
        tempPath.push(curr);

    while (!tempPath.isEmpty())  path.add(tempPath.pop());

    return path;
}

Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    Vector<Vertex*> path;
    PriorityQueue<Vertex*> toProcess;
    initDijkstra(graph, toProcess, start);

    while (!toProcess.isEmpty()) {
        Vertex* v = toProcess.dequeue();
        visitVertex(v);

        if (v == end) break;

        for (Vertex* n: graph.getNeighbors(v)) {
            if (n->visited) continue;

            double cost = v->cost + graph.getEdge(v, n)->cost;

            if (n->getColor() == UNCOLORED) {
                toProcess.enqueue(n, cost);
                n->setColor(YELLOW);
            }

            if (cost <= n->cost) {
                n->cost = cost;
                n->previous = v;
                toProcess.changePriority(n, cost);
            }
        }

    }

    return reconstructPath(path, end);
}

void initDijkstra(BasicGraph& graph, PriorityQueue<Vertex*>& toProcess, Vertex* start) {
    graph.resetData();

    for (Vertex* v: graph.getVertexSet())
        v->cost = POSITIVE_INFINITY;

    start->cost = 0;
    toProcess.enqueue(start, start->cost);
}

void visitVertex(Vertex* v) {
    v->setColor(GREEN);
    v->visited = true;
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Vector<Vertex*> path;
    return path;
}

Set<Edge*> kruskal(BasicGraph& graph) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty set so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Set<Edge*> mst;
    return mst;
}
