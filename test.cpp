#include "implementation.h"
#include <algorithms/isomorphism/isomorphism.hpp>
#include <snarks/colouring_cvd.hpp>

#include "create_multipole_deg6.hpp"
#include "make_all_5poles.hpp"
#include "create_snarks.hpp"

#include "utils/file_write.hpp"
#include "utils/file_parser.hpp"

#include <sys/stat.h>

using namespace ba_graph;

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

    std::vector<Graph> graphs = generate_graphs_from_file("./inputs/Generated_graphs.20.05.sn.cyc4.g6");
    for (int i = 0; i < graphs.size(); i++) {
        check_all_possibilities_for_graph(graphs[i]);
    }

    //Graph g = create_blanusa_first();
    //check_all_possibilities_for_graph(g);

    /*std::vector<std::pair<int, int>> temp;
    std::vector<std::vector<std::pair<int, int>>> possible = get_possible_recursive(temp);
    std::cout << translate_colouring(possible) << std::endl;
    std::cout << possible.size() << std::endl; */

    return 0;
}