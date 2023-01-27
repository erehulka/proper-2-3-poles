#ifndef POLE_IS_PERFECT_HPP
#define POLE_IS_PERFECT_HPP

#include <map>

#include "implementation.h"
#include <graphs.hpp>
#include <invariants.hpp>
#include <multipoles.hpp>

using namespace ba_graph;

/*const std::vector<std::vector<int>> colourings = {
        {1,2,3,3,3},
        {1,2,2,2,3},
        {1,2,2,3,2},
        {1,2,3,2,2},
        {1,2,1,1,3},
        {1,2,1,3,1},
        {1,2,3,1,1}
};*/

const std::vector<std::vector<int>> colourings = {
        {0,1,2,2,2},
        {0,1,1,1,2},
        {0,1,1,2,1},
        {0,1,2,1,1},
        {0,1,0,0,2},
        {0,1,0,2,0},
        {0,1,2,0,0}
};

std::pair<bool, std::vector<std::vector<int>>> is_perfect(Graph &g, Multipole &m) {
    // all possible colourings are (for a1, a2, b1, b2, b3):
    // [[1 2 1 1 3] [1 2 1 3 1] [1 2 2 2 3] [1 2 2 3 2] [1 2 3 1 1] [1 2 3 2 2]
    // [1 2 3 3 3] [1 3 1 1 2] [1 3 1 2 1] [1 3 2 1 1] [1 3 2 2 2] [1 3 2 3 3] [1 3 3 2 3]
    // [1 3 3 3 2] [2 1 1 1 3] [2 1 1 3 1] [2 1 2 2 3] [2 1 2 3 2] [2 1 3 1 1] [2 1 3 2 2]
    // [2 1 3 3 3] [2 3 1 1 1] [2 3 1 2 2] [2 3 1 3 3] [2 3 2 1 2] [2 3 2 2 1] [2 3 3 1 3]
    // [2 3 3 3 1] [3 1 1 1 2] [3 1 1 2 1] [3 1 2 1 1] [3 1 2 2 2] [3 1 2 3 3] [3 1 3 2 3]
    // [3 1 3 3 2] [3 2 1 1 1] [3 2 1 2 2] [3 2 1 3 3] [3 2 2 1 2] [3 2 2 2 1] [3 2 3 1 3]
    // [3 2 3 3 1]]

    // when we remove isomorphic colourings:
    // 12113, 12131, 12223, 12232, 12311, 12322, 12333,
    std::map<Edge, int> preColouring;
    bool isPerfect = true;
    std::vector<std::vector<int>> possible_colourings;

    for (auto colouring : colourings) {
        Graph gCopy = copy_identical(g);
        preColouring = std::map<Edge, int>();
        for (int i = 0 ; i < 2 ; i++) {
            Number neighbor = *(gCopy[m.connectors[0][i]].neighbours().begin());
            Edge e = gCopy.find(Location(m.connectors[0][i], neighbor))->e();
            preColouring[e] = colouring[i];
        }

        for (int i = 0 ; i < 3 ; i++) {
            Number neighbor = *(gCopy[m.connectors[1][i]].neighbours().begin());
            Edge e = gCopy.find(Location(m.connectors[1][i], neighbor))->e();
            preColouring[e] = colouring[i+2];
        }

        if (!is_edge_colourable_basic(gCopy, 3, preColouring)) {
            isPerfect = false;
        } else {
            possible_colourings.push_back(colouring);
        }
    }

    return {isPerfect, possible_colourings};
}

#endif