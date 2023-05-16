#include "implementation.h"
#include <algorithms/isomorphism/isomorphism.hpp>
#include <snarks/colouring_cvd.hpp>
#include <snarks/colouring.hpp>

#include "multipoles/create_multipole.hpp"
#include "multipole_creator/make_all_5poles.hpp"
#include <snarks/colouring.hpp>
#include "utils/file_write.hpp"
#include "utils/file_parser.hpp"

#include <sys/stat.h>

using namespace ba_graph;

void check_all_possibilities_for_graph(Graph &g, const std::string& outputDir) {
    graph_props_to_delete props;
    std::cout << write_graph6(g, false) << std::endl;
    std::vector<multipole_creation> result = create_all_multipoles_by_removing_1_vertex_1_edge(g,props);

    std::vector<std::pair<Number, Number>> removable_vertices = removable_pairs_vertices<HeuristicsColouriser>(g);
    std::vector<std::pair<Location, Location>> removable_edges = removable_pairs_edges<HeuristicsColouriser>(g);

    std::string outputFile = outputDir + write_graph6(g, false) + ".csv";
    write_to_file(result, outputFile, removable_vertices, removable_edges, g);
}

int main(int argc, char **argv) {
    mkdir("outputs", 0777);
    mkdir("outputs_bicritical", 0777);

    if (argc != 3) {
        std::cerr << "Name of the input file and output directory must be passed" << std::endl;
        return 1;
    }

    std::string fileName(argv[1]);
    std::string outputDir(argv[2]);

    std::vector<Graph> graphs = generate_graphs_from_file(fileName);
    for (auto & graph : graphs) {
        check_all_possibilities_for_graph(graph, outputDir);
    }

    return 0;
}