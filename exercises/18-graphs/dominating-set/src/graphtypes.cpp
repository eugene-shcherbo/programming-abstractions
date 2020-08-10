#include <chrono>
#include "strlib.h"
#include "map.h"
#include "set.h"
#include "stack.h"
#include "queue.h"
#include "priorityqueue.h"
#include "graphtypes.h"

constexpr char EDGE_SYMBOL = '-';
constexpr char WEIGHT_SEPARATOR = '(';

enum VertexConnection {
    NOT_CONNECTED = 0,
    BIDIRECTIONAL,
    DIRECTIONAL
};

void readLine(SimpleGraph& g, std::string line);
std::string parseName(std::string line, size_t& pos, char separator);
VertexConnection parseConnection(std::string line, size_t& pos);
int parseWeight(std::string line, size_t& pos);
void addVertex(SimpleGraph& g, std::string vertex);
void addEdge(SimpleGraph& g, std::string vertex1, std::string vertex2, int weigth);

void visitUsingDfs(Vertex* from, Set<Vertex*>& visited);

void dfs(void (*fn)(Vertex*), Vertex* from) {
    Set<Vertex*> visited;
    Stack<Vertex*> neighbours;
    neighbours.push(from);

    while (!neighbours.isEmpty()) {
        Vertex* v = neighbours.pop();
        if (!visited.contains(v)) {
            fn(v);
            visited.add(v);

            for (Edge* e: v->edges) {
                neighbours.push(e->finish);
            }
        }
    }
}

void bfs(void (*fn)(Vertex*), Vertex* start) {
    Set<Vertex*> visited;
    Queue<Vertex*> toVisit;
    toVisit.enqueue(start);
    while (!toVisit.isEmpty()) {
        Vertex* v = toVisit.dequeue();
        fn(v);
        for (Edge* e: v->edges) {
            if (!visited.contains(e->finish)) {
                visited.add(e->finish);
                toVisit.enqueue(e->finish);
            }
        }
    }
}

void readGraph(SimpleGraph& g, std::istream& in) {
    std::string line;
    while (getline(in, line)) {
        readLine(g, line);
    }
}

void writeGraph(SimpleGraph& g, std::ostream& os) {
    Map<Vertex*, Set<Vertex*>> connections;
    Map<Vertex*, Set<Vertex*>> writtenVertexes;

    for (Edge* e: g.edgeSet) {
        connections[e->finish].add(e->start);
    }

    for (Vertex* v: g.vertexSet) {
        if (v->edges.isEmpty() && connections[v].isEmpty()) {
            os << v->name << std::endl;
        } else {
            for (Edge* e: v->edges) {
                if (writtenVertexes[e->finish].contains(e->start)) {
                    continue;
                }

                os << v->name << " -";
                if (!connections[v].contains(e->finish)) {
                    os << ">";
                }
                os << ' ' << e->finish->name;

                if (e->weigth == 0) {
                    os << std::endl;
                } else {
                    os << " (" << e->weigth << ')' << std::endl;
                }
                writtenVertexes[e->start].add(e->finish);
            }
        }
    }
}

void readLine(SimpleGraph& g, std::string line) {
    size_t pos = 0;
    std::string firstVertexName = parseName(line, pos, EDGE_SYMBOL);
    addVertex(g, firstVertexName);

    VertexConnection connection = parseConnection(line, pos);
    if (connection == DIRECTIONAL || connection == BIDIRECTIONAL) {
        std::string secondVertexName = parseName(line, pos, WEIGHT_SEPARATOR);
        int weight = parseWeight(line, pos);
        addVertex(g, secondVertexName);
        addEdge(g, firstVertexName, secondVertexName, weight);

        if (connection == BIDIRECTIONAL) {
            addEdge(g, secondVertexName, firstVertexName, weight);
        }
    }
}

std::string parseName(std::string line, size_t& pos, char separator) {
    std::string name = "";
    while (pos < line.size() && line[pos] != separator) {
        name += line[pos];
        pos++;
    }
    return trim(name);
}

VertexConnection parseConnection(std::string line, size_t& pos) {
    VertexConnection connection = NOT_CONNECTED;

    if (pos < line.size() - 1) {
        if (line[pos] == '-' && line[pos + 1] == '>') {
            pos++;
            connection = DIRECTIONAL;
        } else if (line[pos] == '-') {
            connection = BIDIRECTIONAL;
        } else {
            connection = NOT_CONNECTED;
        }
        pos++;
    }

    return connection;
}

int parseWeight(std::string line, size_t& pos) {
    std::string num = "";
    pos++;
    while (pos < line.size() && line[pos] != ')') {
        num += line[pos];
        pos++;
    }
    return num.empty() ? 0 : stringToInteger(num);
}

void addVertex(SimpleGraph& g, std::string vertex) {
    if (!g.vertexMap.containsKey(vertex)) {
        Vertex* v = new Vertex;
        v->name = vertex;
        g.vertexSet.add(v);
        g.vertexMap.add(vertex, v);
    }
}

void addEdge(SimpleGraph& g, std::string vertex1, std::string vertex2, int weigth) {
    Vertex* v1 = g.vertexMap[vertex1];
    Vertex* v2 = g.vertexMap[vertex2];

    Edge* e = new Edge;
    e->start = v1;
    e->finish = v2;
    e->weigth = weigth;
    e->start->edges.add(e);
    g.edgeSet.add(e);
}

bool pathExists(Vertex* from, Vertex* to) {
    if (from == to) {
        return true;
    }

    Queue<Vertex*> toVisit;
    Set<Vertex*> visited;
    toVisit.enqueue(from);

    while (!toVisit.isEmpty()) {
        Vertex* vertex = toVisit.dequeue();

        for (Edge* e: vertex->edges) {
            if (e->finish == to) {
                return true;
            } else if (!visited.contains(e->finish)) {
                visited.add(e->finish);
                toVisit.enqueue(e->finish);
            }
        }
    }

    return false;
}

int hopCount(Vertex* from, Vertex* to) {
    if (from == to) {
        return 0;
    }

    Queue<Vertex*> toVisit;
    Set<Vertex*> visited;
    toVisit.enqueue(from);
    int hops = 0;

    while (!toVisit.isEmpty()) {
        hops++;
        Vertex* vertex = toVisit.dequeue();

        for (Edge* e: vertex->edges) {
            if (e->finish == to) {
                return hops;
            } else if (!visited.contains(e->finish)) {
                visited.add(e->finish);
                toVisit.enqueue(e->finish);
            }
        }
    }

    return -1;
}

int getPathCost(Vector<Edge*> path) {
    int cost = 0;
    for (Edge* e: path) {
        cost += e->weigth;
    }
    return cost;
}

Vector<Edge*> findShortestPath(Vertex* start, Vertex* finish) {
    Set<std::string> visited;
    PriorityQueue<Vector<Edge*>> toProceed;
    Vector<Edge*> path;

    while (start != finish) {
        visited.add(start->name);
        for (Edge* e : start->edges) {
            if (!visited.contains(e->finish->name)) {
                path.add(e);
                toProceed.enqueue(path, getPathCost(path));
                path.removeBack();
            }
        }

        if (toProceed.isEmpty()) {
            return Vector<Edge*>();
        }

        path = toProceed.dequeue();
        start = path[path.size() - 1]->finish;
    }

    return path;
}

bool canSplitBetweenSets(Set<Vertex*>& one, Set<Vertex*>& two, Vertex* start, Vertex* finish) {
    return (!one.contains(start) && !one.contains(finish))
           || (!two.contains(start) && !two.contains(finish));
}

void moveVertexToSet(Set<Vertex*>& one, Set<Vertex*>& two, Vertex* v, Vertex* connected) {
    if (one.contains(v) || two.contains(v)) return;

    if (!one.contains(v) && !one.contains(connected)) {
        one.add(v);
    } else if (one.contains(connected)) {
        two.add(v);
    }
}

bool isBipartite(SimpleGraph& g) {
    Set<Vertex*> one;
    Set<Vertex*> two;
    Map<Vertex*, Vertex*> connections;

    for (Edge* e: g.edgeSet) {
        if (connections.containsKey(e->finish) && connections[e->finish] == e->start) continue;
        if (!canSplitBetweenSets(one, two, e->start, e->finish)) return false;

        moveVertexToSet(one, two, e->start, e->finish);
        moveVertexToSet(one, two, e->finish, e->start);

        connections.add(e->start, e->finish);
    }

    return true;
}

bool isRedundant(Vertex* v, Set<Vertex*>& dominationNeighbours) {
    if (!dominationNeighbours.contains(v)) return false;
    for (Edge* e : v->edges) {
        if (!dominationNeighbours.contains(e->finish)) return false;
    }
    return true;
}

Set<Vertex*> findDominatingSet(SimpleGraph& g) {
    Set<Vertex*> dominatingSet;
    Set<Vertex*> dominatingNeighbours;

    PriorityQueue<Vertex*> pq;
    for (Vertex* v : g.vertexSet) {
        pq.enqueue(v, -v->edges.size());
    }

    while (!pq.isEmpty()) {
        Vertex* v = pq.dequeue();
        if (!isRedundant(v, dominatingNeighbours)) {
            dominatingSet.add(v);

            for (Edge* e : v->edges) {
                dominatingNeighbours.add(e->finish);
            }
        }
    }

    return dominatingSet;
}
