#include "implementation.h"
#include <algorithms/isomorphism/isomorphism.hpp>
#include <snarks/colouring_cvd.hpp>

#include "../snark_multipoles_deg_6.nosync/create_multipole_deg6.hpp"
#include "make_all_5poles.hpp"
#include "create_snarks.hpp"

using namespace ba_graph;

void write_to_file(std::vector<multipole_creation> &result, const std::string output_file) {
    std::ofstream output(output_file);
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
    write_to_file(result, "vysledok.txt");
}

template <typename T,typename U>
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {
    return {(l.first+r.first) % 2,(l.second+r.second) % 2};
}
std::vector<std::vector<std::pair<int, int>>> get_possible_recursive(std::vector<std::pair<int, int>> temp) {
    std::vector<std::pair<int, int>> colours = {{0,1},{1,0},{1,1}};
    std::vector<std::vector<std::pair<int, int>>> result;
    if (temp.size() == 5) {
        std::pair<int, int> first = temp[0] + temp[1];
        std::pair<int, int> second = temp[2] + temp[3] + temp[4];

        if (
                first == second &&
                first != std::pair<int, int>(0,0) &&
                second != std::pair<int, int>(0,0)
            ) {
            result.push_back(temp);
        }
    } else {
        for (auto colour : colours) {
            temp.push_back(colour);
            std::vector<std::vector<std::pair<int, int>>> tmp_result = get_possible_recursive(temp);
            result.insert(result.end(), tmp_result.begin(), tmp_result.end());
            temp.pop_back();
        }
    }

    return result;
}


std::vector<std::vector<int>> translate_colouring(std::vector<std::vector<std::pair<int, int>>> input) {
    std::vector<std::vector<int>> result;
    for (auto colouring : input) {
        std::vector<int> temp_colouring;
        for (auto colour : colouring) {
            int colour_final = colour.first * 2 + colour.second;
            temp_colouring.push_back(colour_final);
        }
        result.push_back(temp_colouring);
    }

    return result;
}

int main() {
    Graph g = create_petersen();
    check_all_possibilities_for_graph(g);

    /*std::vector<std::pair<int, int>> temp;
    std::vector<std::vector<std::pair<int, int>>> possible = get_possible_recursive(temp);
    std::cout << translate_colouring(possible) << std::endl;
    std::cout << possible.size() << std::endl; */

    return 0;
}