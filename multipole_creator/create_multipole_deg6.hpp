#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-return-braced-init-list"

#ifndef CREATE_MULTIPOLE_DEG_6
#define CREATE_MULTIPOLE_DEG_6

#include <vector>
#include <string>
#include <algorithm>
#include <set>

#include <graphs.hpp>
#include <multipoles.hpp>

#include "../implementation.h"
#include "../multipoles/connector_validator.hpp"

using namespace ba_graph;

struct graph_props_to_delete {
  std::vector<Location> locs;
  std::vector<Number> vertices;
};

/**
 * Functions to modify struct graph_props_to_delete
 * Add edge, vertex, or clear all data from it.
 * TODO add these modifiers to different file, folder utils
 */

void add_edge_to_gprops(struct graph_props_to_delete &props, int from, int to) {
    props.locs.emplace_back(from, to);
}

void add_edge_to_gprops(struct graph_props_to_delete &props, Location edge) {
    props.locs.push_back(edge);
}

void add_vertex_to_gprops(struct graph_props_to_delete &props, const int v_index) {
    props.vertices.emplace_back(v_index);
}

void add_vertex_to_gprops(struct graph_props_to_delete &props, const Number vertex) {
    props.vertices.push_back(vertex);
}

void remove_last_vertex_from_gprops(struct graph_props_to_delete &props) {
    props.vertices.pop_back();
}

void clear_props(struct graph_props_to_delete &props) {
    props.vertices = std::vector<Number>();
    props.locs = std::vector<Location>();
}

/**
 * Functions to remove vertex or edge from graph.
 * Returned values are connectors, with newly created vertices.
 */

Connector remove_edge(Graph &g, Location &edge) {
    if (!g.contains( edge )) {
        throw std::invalid_argument( "Graph does not contain one of provided edges." );
    } else if (g[edge.n1()].degree() != 3 || g[edge.n2()].degree() != 3) {
        throw std::invalid_argument("You can't remove connector vertex.");
    }

    Number first = addMultipleV(g,1);
    Number second = addMultipleV(g,1);
    addE(g,Location(edge.n1(), first));
    addE(g,Location(edge.n2(), second));

    deleteE(g, edge);
    return Connector(std::vector<Number>{first, second});
}

Connector remove_vertex(Graph &g, Number &vertex) {
    if (!g.contains(vertex)) {
        throw std::invalid_argument("Graph does not contain one of provided vertices.");
    } else if (g[vertex].degree() != 3) {
        throw std::invalid_argument("You can't remove connector vertex.");
    }

    std::vector<Number> connecting_vertices;
    for (auto neighbor : g[vertex].neighbours()) {
        if (g[neighbor].degree() == 1) {
            deleteV(g, neighbor);
        } else {
            Number added = addMultipleV(g,1);
            addE(g, Location(neighbor, added));
            connecting_vertices.push_back(added);
        }
    }

    deleteV(g, vertex);
    return Connector(connecting_vertices);
}

/**
 * Simple function to check if vertices in graph props form a path in given graph.
 */
bool is_path(const Graph &g, const struct graph_props_to_delete &props) {
    for (int i = 0; i < (props.vertices.size() - 1); i++) {
        if (!g.contains( Location(props.vertices[i], props.vertices[i+1]) ))
            return false;
    }
    return true;
}

#endif

#pragma clang diagnostic pop