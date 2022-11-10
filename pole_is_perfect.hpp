#ifndef POLE_IS_PERFECT_HPP
#define POLE_IS_PERFECT_HPP

#include <map>

#include "implementation.h"
#include <graphs.hpp>
#include <invariants.hpp>
#include <multipoles.hpp>

using namespace ba_graph;

const std::vector<std::vector<int>> colourings = {{1,2,3,3,3}, {1,3,3,3,2}, {1,3,3,2,3}, {1,3,2,3,3}, {3,1,3,3,2}, {3,1,3,2,3}, {3,1,2,3,3}};

std::pair<bool, std::vector<std::vector<int>>> is_perfect(Graph &g, Multipole &m) {
    // all possible colourings are (for a1, a2, b1, b2, b3):
    // 12333
    // 21333
    // 13332, 13323, 13233, 13222
    // 31332, 31323, 31233, 31222
    // 23331, 23313, 23133, 23111
    // 32331, 32313, 32133, 32111

    // when we remove isomorphic colourings:
    // 12333, 13332, 13323, 13233, 31332, 31323, 31233
    std::map<Edge, int> preColouring;
    bool isPerfect = true;
    std::vector<std::vector<int>> possible_colourings;
    for (auto colouring : colourings) {
        preColouring = std::map<Edge, int>();
        for (int i = 0 ; i < 2 ; i++) {
            Number neighbor = *(g[m.connectors[0][i]].neighbours().begin());
            Edge e = g[m.connectors[0][i]].find(Location(m.connectors[0][i], neighbor))->e();
            preColouring[e] = colouring[i];
        }

        for (int i = 0 ; i < 3 ; i++) {
            Number neighbor = *(g[m.connectors[1][i]].neighbours().begin());
            Edge e = g.find(Location(m.connectors[1][i].to_int(), neighbor.to_int()))->e();
            preColouring[e] = colouring[i+2];
        }

        if (!is_edge_colourable_basic(g, 3, preColouring)) {
            isPerfect = false;
        } else {
            possible_colourings.push_back(colouring);
        }
    }

    return {isPerfect, possible_colourings};
}

#endif