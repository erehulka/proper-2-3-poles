#include "implementation.h"
#include <algorithms/isomorphism/isomorphism.hpp>
#include <snarks/colouring_cvd.hpp>

#include "create_multipole_deg6.hpp"
#include "make_all_5poles.hpp"
#include "create_snarks.hpp"

#include <sys/stat.h>

using namespace ba_graph;

void write_to_file(std::vector<multipole_creation> &result, const std::string output_file) {
    std::ofstream output(output_file);
    std::cout << output_file << std::endl;
    if (output.is_open()) {
        output << result[0].g_original << std::endl;
        for (const auto &oneRes : result) {
            output
//            << oneRes.g
            << " edges: "
            << oneRes.props.locs
            << ", vertices: "
            << oneRes.props.vertices
            << ", colourable: "
            << oneRes.isColorable
            << ", perfect: "
            << oneRes.isPerfect
            << ", possible colourings: "
            << oneRes.possible_colourings
            << ", distances: "
            << oneRes.distances
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

    std::string outputFile = "./outputs/" + write_graph6(g, false) + ".txt";
    write_to_file(result, outputFile);
}

int main() {
    mkdir("outputs", 0777);

    Graph g = create_blanusa_first();
    check_all_possibilities_for_graph(g);

    /*std::vector<std::pair<int, int>> temp;
    std::vector<std::vector<std::pair<int, int>>> possible = get_possible_recursive(temp);
    std::cout << translate_colouring(possible) << std::endl;
    std::cout << possible.size() << std::endl; */

    return 0;
}