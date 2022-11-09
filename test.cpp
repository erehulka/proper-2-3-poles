#include <cassert>

#include "implementation.h"
#include <graphs.hpp>
#include <algorithms/isomorphism/isomorphism.hpp>
#include <snarks/colouring_cvd.hpp>

#include "../snark_multipoles_deg_6.nosync/create_multipole_deg6.hpp"
#include "make_all_5poles.hpp"
#include "create_snarks.hpp"

using namespace ba_graph;

void write_to_file(std::vector<multipole_creation> &result, const std::string output_file) {
    std::ofstream output(output_file);
    if (output.is_open()) {
        for (const auto &oneRes : result) {
            output
            << oneRes.deletion_method
            << ' '
            << oneRes.g_original
            << ' '
            << oneRes.g
            << " edges: "
            << oneRes.props.locs
            << ", vertices: "
            << oneRes.props.vertices
            << ", colourable: "
            << oneRes.isColorable
            << std::endl;
        }
    } else std::cerr << "Unable to open file" << std::endl;
}

void check_all_possibilities_for_graph(Graph &g) {
    graph_props_to_delete props;

    // How many multipoles there should be
    std::cout << (max_number(g).to_int() + 1) * (g.size() - 3) << std::endl;

    std::vector<multipole_creation> result = create_all_multipoles_by_removing_1_vertex_1_edge(g,props);

    std::cout << result.size() << std::endl;
    write_to_file(result, "vysledok.txt");
}


int main() {
    Graph g = create_blanusa_second();
    std::cout << g << std::endl;
    std::cout << g.size() << std::endl;

    check_all_possibilities_for_graph(g);

    return 0;
}