#include "graphtypes.h"

void Graph::addNode(node *node) {
    if (node == nullptr) return;
    _nodes.add(node);
    _index.add(node->name, node);
}

void Graph::addArc(arc* arc) {
    if (arc == nullptr) return;
    _arcs.add(arc);
}

void Graph::addArc(node* node1, node* node2) {
    if (!_nodes.contains(node1)) return;
    if (!_nodes.contains(node1)) return;

    arc* arc = new struct arc();
    arc->start = node1;
    arc->finish = node2;

    node1->outgoing.add(arc);
    node2->incoming.add(arc);

    _arcs.add(arc);
}

node* Graph::getNode(std::string nodeName) const {
    if (!_index.containsKey(nodeName)) return nullptr;
    return _index[nodeName];
}

bool Graph::hasNode(std::string nodeName) const {
    return getNode(nodeName) != nullptr;
}

void Graph::clear() {
    for (node* node : getNodes()) {
        cleanNode(node);
        delete node;
    }

    for (arc* arc : getArcs())
        delete arc;

    _nodes.clear();
    _arcs.clear();
    _index.clear();
}

void Graph::cleanNode(node* node) {
    if (node->exp != nullptr)
        delete node->exp;

    for (arc* arc : node->incoming) {
        arc->start->outgoing.remove(arc);
        delete arc;
    }

    node->incoming.clear();
}
