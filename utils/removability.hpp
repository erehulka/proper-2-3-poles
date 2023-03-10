#ifndef REMOVABILITY
#define REMOVABILITY

#include "../implementation.h"
#include <graphs.hpp>
#include <snarks/colouring.hpp>

using namespace ba_graph;

bool pair_vertices_removable(Number v1, Number v2, std::vector<std::pair<Number, Number>> removable_vertices) {
    std::pair<Number, Number> removable;
    if (v1.to_int() < v2.to_int()) {
        removable = {v1, v2};
    } else {
        removable = {v2, v1};
    }

    return std::find(removable_vertices.begin(), removable_vertices.end(), removable) != removable_vertices.end();
}

bool pair_edges_removable(Location l1, Location l2, std::vector<std::pair<Location, Location>> removable_edges) {
    std::pair<Location, Location> removableOne{l1, l2};
    std::pair<Location, Location> removableTwo{l2, l1};

    return std::find(removable_edges.begin(), removable_edges.end(), removableOne) != removable_edges.end()
        || std::find(removable_edges.begin(), removable_edges.end(), removableTwo) != removable_edges.end();
}

int edges_removable_from_23_pole(Location l1, Number n, std::vector<std::pair<Location, Location>> removable_edges, Graph& g) {
    int result = 0;

    for (auto neighbor : g[n].neighbours()) {
        int min_n = std::min(n.to_int(), neighbor.to_int());
        int max_n = std::max(n.to_int(), neighbor.to_int());
        Location l2 = Location(min_n, max_n);

        if (pair_edges_removable(l1, l2, removable_edges)) result++;
    }

    return result;
}

#endif