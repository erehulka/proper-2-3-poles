#include "../implementation.h"
#include <graphs.hpp>
#include <algorithm>
#include "./colorings.hpp"
#include "./distance.hpp"
#include "./removability.hpp"
#include <invariants/girth.hpp>

using namespace ba_graph;

void write_to_file(
    std::vector<multipole_creation> &result,
    const std::string& output_file,
    const std::vector<std::pair<Number, Number>>& removable_vertices,
    const std::vector<std::pair<Location, Location>>& removable_edges,
    Graph &g
) {
    std::ofstream output(output_file);
    if (output.is_open()) {
        output
            << "graph6;edge;vertex;colourings_class;"
            << "distance;removable_vertices;removable_edges"
            << std::endl;
        for (const auto &oneRes : result) {
            int firstRemovable = (int) pair_vertices_removable(oneRes.props.vertices[0], oneRes.props.locs[0].n1(), removable_vertices);
            int secondRemovable = (int) pair_vertices_removable(oneRes.props.vertices[0], oneRes.props.locs[0].n2(), removable_vertices);
            int removable_edges_n = edges_removable_from_23_pole(oneRes.props.locs[0], oneRes.props.vertices[0], removable_edges, g);

            output
                << oneRes.g
                << ";"
                << oneRes.props.locs[0].n1() << ", " << oneRes.props.locs[0].n2()
                << ";"
                << oneRes.props.vertices[0]
                << ";"
                << translate_colouring_to_class(oneRes.possible_colourings)
                << ";"
                << distanceVertexEdge(oneRes.props.vertices[0], oneRes.props.locs[0], g)
                << ";"
                << (firstRemovable + secondRemovable)
                << ";"
                << removable_edges_n
                << std::endl;
        }
    } else std::cerr << "Unable to open file" << std::endl;
}