/**
 * File: graphtypes.h
 * ------------------
 * This file defines low-level data structures that represent graphs.
 * You are free to modify this header file to help accomodate the needs to
 * your Stanford 1-2-3 application.
 */

#pragma once
#include <string>
#include "gtypes.h"
#include "map.h"
#include "set.h"

/**
 * Type: node
 * ----------
 * This type represents an individual node and consists of the
 * name of the node and the set of arcs from this node. Outgoing arcs
 * are those ones which are dependent on the node. Incoming arcs are
 * those ones which impact on the node. In fact, they are represented by
 * the pointers to the same arcs.
 *
 * For example, consider node A3 and A1, where A1 = A3. We would have
 * one edge, from A3 to A1, which is in outgoing for A3 and in incoming
 * for A1.
 */

struct node {
   std::string name;
   Set<struct arc *> outgoing;
   Set<struct arc *> incoming;
};

/**
 * Type: arc
 * ---------
 * This type represents an individual arc and consists of pointers
 * to the endpoints.  This particular version excludes the cost, since
 * the dependency graphs you'll be building won't require it.
 */

struct arc {
   node *start;
   node *finish;
};

/**
 * Type: graph
 * -----------
 * This type represents a graph and consists of a set of nodes, a set of
 * arcs, and a map that creates an association between names and nodes.
 */
struct graph {
   Set<node *> nodes;
   Set<arc *> arcs;
   Map<std::string, node *> index;
};
