#ifndef DISTANCE
#define DISTANCE

#include "../implementation.h"
#include <invariants/distance.hpp>
#include <graphs.hpp>

using namespace ba_graph;

int distanceVertexEdge(Number vertex, Location edge, Graph& g) {
    return std::min(distance(g, vertex, edge.n1()), distance(g, vertex, edge.n2()));
}

#endif
