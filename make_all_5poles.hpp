#ifndef MULTIPOLE_CREATOR_HPP
#define MULTIPOLE_CREATOR_HPP

#include <iostream>
#include <vector>
#include <utility>

#include "implementation.h"
#include <algorithms/cyclic_connectivity.hpp>
#include <graphs.hpp>
#include <multipoles.hpp>
#include <invariants.hpp>
#include <snarks.hpp>

#include "../snark_multipoles_deg_6.nosync/create_multipole_deg6.hpp"

using namespace ba_graph;

struct multipole_creation {
    std::string g;
    Multipole *m;
    std::string g_original;
    graph_props_to_delete props;
    std::string deletion_method;
    bool isColorable;

    multipole_creation() = delete;
    multipole_creation(Graph &g, Multipole &m, Graph &g_original, graph_props_to_delete &props, std::string deletion_m) {
        this->g = write_graph6(g, false);
        this->m = &m;
        this->deletion_method = deletion_m;

        this->g_original = write_graph6(g_original, false);

        graph_props_to_delete props_t;
        props_t.vertices = std::vector<Number>(props.vertices);
        props_t.locs = std::vector<Location>(props.locs);
        this->props = props_t;
        this->isColorable = is3EdgeColourable_cvd(g);
    }
};


Multipole create_by_removing_1_vertex_and_edge(Graph &g, struct graph_props_to_delete &props) {

    // ----------- BEGIN correctness check -----------

    if (props.vertices.size() != 1) {
        char result_error[100];
        sprintf(result_error, "Number of vertices must be 1, provided: %lu.", props.vertices.size());
        std::string error_msg = result_error;
        throw std::range_error(error_msg);
    }

    if (props.locs.size() != 1) {
        char result_error[100];
        sprintf(result_error, "Number of edges must be 1, %lu provided.", props.locs.size());
        std::string error_msg = result_error;
        throw std::range_error(error_msg);
    }

    int vertex_n = props.vertices[0].to_int();

    if (
            vertex_n == props.locs[0].n1().to_int() ||
            vertex_n == props.locs[0].n2().to_int() ||
            vertex_n == props.locs[1].n1().to_int() ||
            vertex_n == props.locs[1].n2().to_int()
    ) {
        throw std::invalid_argument("Vertex can't be incident with any edge.");
    }

    // ----------- END correctness check -----------

    std::vector<Connector> connectors;
    connectors.push_back(remove_vertex(g, props.vertices[0]));
    connectors.push_back(remove_edge(g, props.locs[0]));
    return Multipole(get_correct_connectors(g, connectors));
}

std::vector<multipole_creation> create_all_multipoles_by_removing_1_vertex_1_edge(Graph &g, graph_props_to_delete &props) {
    std::vector<multipole_creation> result;

    if (props.vertices.size() == 1) {
        for (int i = 0; i < max_number(g); i++) {
            for (int j = i+1; j < max_number(g); j++) {
                if (!g.contains(Location(i, j))) continue;
                add_edge_to_gprops(props, i, j);

                try {
                    Graph gCopy = copy_identical(g);
                    Multipole m = create_by_removing_1_vertex_and_edge(gCopy,props);

                    Graph g_original = copy_identical(g);
                    result.push_back(multipole_creation(gCopy, m, g_original, props, "1_edge_1_vertex"));
                } catch (const std::exception &e) {
                    // no action
                }

                props.locs.pop_back();
            }
        }
    } else {
        for (int i = 0; i < max_number(g); i++) {
            add_vertex_to_gprops(props, i);

            std::vector<multipole_creation> recursiveResult = create_all_multipoles_by_removing_1_vertex_1_edge(g, props);
            result.insert(result.end(), recursiveResult.begin(), recursiveResult.end());

            props.vertices.pop_back();
        }
    }

    return result;
}

#endif
