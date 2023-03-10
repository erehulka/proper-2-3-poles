#include "implementation.h"
#include <algorithms/isomorphism/isomorphism.hpp>
#include <snarks/colouring_cvd.hpp>
#include <snarks/colouring.hpp>

#include "multipole_creator/create_multipole_deg6.hpp"
#include "multipole_creator/make_all_5poles.hpp"
#include "snarks/create_snarks.hpp"

#include "utils/file_write.hpp"
#include "utils/file_parser.hpp"

#include <sys/stat.h>

using namespace ba_graph;

void check_all_possibilities_for_graph(Graph &g) {
    graph_props_to_delete props;

    // How many multipoles there should be
    //std::cout << (max_number(g).to_int() + 1) * (g.size() - 3) << std::endl;
    std::cout << write_graph6(g, false) << std::endl;

    std::vector<multipole_creation> result = create_all_multipoles_by_removing_1_vertex_1_edge(g,props);

    //std::cout << result.size() << std::endl;

    std::vector<std::pair<Number, Number>> removable_vertices = removable_pairs_vertices<HeuristicsColouriser>(g);
    std::vector<std::pair<Location, Location>> removable_edges = removable_pairs_edges<HeuristicsColouriser>(g);

    std::string outputFile = "./outputs/" + write_graph6(g, false) + ".csv";
    write_to_file(result, outputFile, removable_vertices, removable_edges, g);
}

int main(int argc, char **argv) {
    mkdir("outputs", 0777);

    if (argc != 2) {
        std::cerr << "Name of the input file must be passed" << std::endl;
        return 1;
    }

    std::string path("./inputs/");
    std::string fileName(argv[1]);

    std::vector<Graph> graphs = generate_graphs_from_file(path + fileName);
    for (auto & graph : graphs) {
        check_all_possibilities_for_graph(graph);
    }

    //Graph g = create_blanusa_first();
    //check_all_possibilities_for_graph(g);

    /*std::vector<std::pair<int, int>> temp;
    std::vector<std::vector<std::pair<int, int>>> possible = get_possible_recursive(temp);
    std::cout << translate_colouring(possible) << std::endl;
    std::cout << possible.size() << std::endl; */

    return 0;
}