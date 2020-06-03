#include "strlib.h"
#include "map.h"
#include "set.h"
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
    return stringToInteger(num);
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
