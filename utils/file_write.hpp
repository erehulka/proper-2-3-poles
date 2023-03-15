#include "../implementation.h"
#include <graphs.hpp>
#include <algorithm>
#include "./colorings.hpp"
#include "./distance.hpp"
#include "./removability.hpp"

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
            << "edges;vertices;colourable;perfect;possible colourings;colourings size;"
            << "colourings class;distance;vertices at least one removable;vertices both removable;removable_edges;"
            << "essential edges"
            << std::endl;
        for (const auto &oneRes : result) {
            bool firstRemovable = pair_vertices_removable(oneRes.props.vertices[0], oneRes.props.locs[0].n1(), removable_vertices);
            bool secondRemovable = pair_vertices_removable(oneRes.props.vertices[0], oneRes.props.locs[0].n2(), removable_vertices);
            int removable_edges_n = edges_removable_from_23_pole(oneRes.props.locs[0], oneRes.props.vertices[0], removable_edges, g);
            int essential_edges = edges_essential_in_23_pole(oneRes.props.locs[0], oneRes.props.vertices[0], removable_edges, g);

            output
                << oneRes.props.locs
                << ";"
                << oneRes.props.vertices
                << ";"
                << oneRes.isColorable
                << ";"
                << oneRes.isPerfect
                << ";"
                << oneRes.possible_colourings
                << ";"
                << oneRes.possible_colourings.size()
                << ";"
                << translate_colouring_to_class(oneRes.possible_colourings)
                << ";"
                << distanceVertexEdge(oneRes.props.vertices[0], oneRes.props.locs[0], g)
                << ";"
                << (firstRemovable || secondRemovable)
                << ";"
                << (firstRemovable && secondRemovable)
                << ";"
                << removable_edges_n
                << ";"
                << essential_edges
                << std::endl;
        }
    } else std::cerr << "Unable to open file" << std::endl;
}