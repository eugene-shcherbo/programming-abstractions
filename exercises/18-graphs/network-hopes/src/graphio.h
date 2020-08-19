#ifndef _graph_io_h_
#define _graph_io_h_

#include "graph.h"
#include "graphtypes.h"

constexpr char EDGE_SYMBOL = '-';
constexpr char WEIGHT_SEPARATOR = '(';

enum VertexConnection {
    NOT_CONNECTED = 0,
    BIDIRECTIONAL,
    DIRECTIONAL
};

std::string parseName(std::string line, size_t& pos, char separator);
VertexConnection parseConnection(std::string line, size_t& pos);
int parseWeight(std::string line, size_t& pos);

template <typename VertexType, typename EdgeType>
void readGraph(Graph<VertexType, EdgeType>& g, std::istream& in) {
    std::string line;
    while (getline(in, line)) {
        readLine(g, line);
    }
}

template <typename VertexType, typename EdgeType>
void writeGraph(Graph<VertexType, EdgeType>& /* g */, std::ostream& /* os */) {
    /* not implemented */
}

template <typename VertexType, typename EdgeType>
void readLine(Graph<VertexType, EdgeType>& g, std::string line) {
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

template <typename VertexType, typename EdgeType>
void addVertex(Graph<VertexType, EdgeType>& g, std::string vertex) {
    Vertex* n = g.getNode(vertex);

    if (n == nullptr) {
        g.addNode(vertex);
    }
}

template <typename VertexType, typename EdgeType>
void addEdge(Graph<VertexType, EdgeType>& g, std::string vertex1, std::string vertex2, int weigth){
    VertexType* v1 = g.getNode(vertex1);
    VertexType* v2 = g.getNode(vertex2);

    EdgeType* e = new Edge;
    e->start = v1;
    e->finish = v2;
    e->weigth = weigth;
    e->start->arcs.add(e);

    g.addArc(e);
}


#endif
