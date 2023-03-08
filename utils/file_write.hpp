#include "../implementation.h"
#include <graphs.hpp>
#include <algorithm>
#include "./colorings.hpp"

using namespace ba_graph;

void write_to_file(
    std::vector<multipole_creation> &result,
    const std::string& output_file,
    const std::vector<std::pair<Number, Number>>& removable_vertices
) {
    std::ofstream output(output_file);
    if (output.is_open()) {
        output << "edges;vertices;colourable;perfect;possible colourings;colourings size;colourings class;vertices at least one removable" << std::endl;
        for (const auto &oneRes : result) {
            bool removable = false;
            std::pair<Number, Number> removable_one;
            std::pair<Number, Number> removable_two;
            if (oneRes.props.vertices[0].to_int() < oneRes.props.locs[0].n1().to_int()) {
                removable_one = {oneRes.props.vertices[0], oneRes.props.locs[0].n1()};
            } else {
                removable_one = {oneRes.props.locs[0].n1(), oneRes.props.vertices[0]};
            }
            if (oneRes.props.vertices[0].to_int() < oneRes.props.locs[0].n2().to_int()) {
                removable_two = {oneRes.props.vertices[0], oneRes.props.locs[0].n2()};
            } else {
                removable_two = {oneRes.props.locs[0].n2(), oneRes.props.vertices[0]};
            }

            if(std::find(removable_vertices.begin(), removable_vertices.end(), removable_one) != removable_vertices.end()
                || std::find(removable_vertices.begin(), removable_vertices.end(), removable_two) != removable_vertices.end()) {
                removable = true;
            }

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
                << removable
                << std::endl;
        }
    } else std::cerr << "Unable to open file" << std::endl;
}