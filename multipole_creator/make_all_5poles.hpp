#ifndef MAKE_ALL_5_POLES_HPP
#define MAKE_ALL_5_POLES_HPP

#include <iostream>
#include <vector>
#include <utility>

#include "../implementation.h"
#include <graphs.hpp>
#include <multipoles.hpp>
#include <invariants.hpp>
#include <snarks.hpp>

#include "../multipoles/create_multipole.hpp"
#include "../multipoles/multipole_colourings.hpp"

using namespace ba_graph;

struct multipole_creation {
    std::string g;
    Multipole *m;
    Graph *g_original;
    graph_props_to_delete props;
    std::vector<std::vector<int>> possible_colourings;


    multipole_creation() = delete;
    multipole_creation(Graph &g, Multipole &m, Graph &g_original, graph_props_to_delete &props) {
        this->g = write_graph6(g, false);
        this->m = &m;

        this->g_original = &g_original;

        graph_props_to_delete props_t;
        props_t.vertices = std::vector<Number>(props.vertices);
        props_t.locs = std::vector<Location>(props.locs);
        this->props = props_t;

        std::vector<std::vector<int>> perfect_result = get_colourings(g, m);
        this->possible_colourings = perfect_result;
    }
};


Multipole create_by_removing_1_vertex_and_edge(Graph &g, struct graph_props_to_delete &props) {
    std::vector<Connector> connectors;
    connectors.push_back(remove_edge(g, props.locs[0]));
    connectors.push_back(remove_vertex(g, props.vertices[0]));
    return Multipole(get_correct_connectors(g, connectors));
}

std::vector<multipole_creation> create_all_multipoles_by_removing_1_vertex_1_edge(Graph &g, graph_props_to_delete &props) {
    std::vector<multipole_creation> result;

    if (props.vertices.size() == 1) {
        for (int i = 0; i <= max_number(g); i++) {
            for (int j = i+1; j <= max_number(g); j++) {
                if (!g.contains(Location(i, j))) continue;
                int vertex_n = props.vertices[0].to_int();

                if (vertex_n == i || vertex_n == j) {
                    continue;
                }
                add_edge_to_gprops(props, i, j);

                try {
                    Graph gCopy = copy_identical(g);
                    Multipole m = create_by_removing_1_vertex_and_edge(gCopy,props);

                    Graph g_original = copy_identical(g);
                    result.emplace_back(gCopy, m, g_original, props);
                } catch (const std::exception &e) {
                    // no action
                }

                props.locs.pop_back();
            }
        }
    } else {
        for (int i = 0; i <= max_number(g); i++) {
            add_vertex_to_gprops(props, i);

            std::vector<multipole_creation> recursiveResult = create_all_multipoles_by_removing_1_vertex_1_edge(g, props);
            result.insert(result.end(), recursiveResult.begin(), recursiveResult.end());

            props.vertices.pop_back();
        }
    }

    return result;
}

#endif
