#include "implementation.h"
#include <graphs.hpp>

using namespace ba_graph;

inline Graph create_blanusa_first(Factory &f = static_factory) {
    Graph g(empty_graph(18, f));
    //outer cycle
    for (int i = 0; i < 16; i++) {
        addE(g, Location(i, i+1), f);
    }
    addE(g, Location(16, 0), f);

    // connect middle vertex
    addE(g, Location(0, 17), f);
    addE(g, Location(3, 17), f);
    addE(g, Location(14, 17), f);

    // connect remaining
    addE(g, Location(2, 7), f);
    addE(g, Location(4, 16), f);
    addE(g, Location(5, 9), f);
    addE(g, Location(6, 11), f);
    addE(g, Location(8, 12), f);
    addE(g, Location(10, 15), f);
    addE(g, Location(1, 13), f);
    return g;
}

inline Graph create_blanusa_second(Factory &f = static_factory) {
    Graph g(empty_graph(18, f));
    //outer cycle
    for (int i = 0; i < 5; i++) {
        addE(g, Location(i, i+1), f);
    }
    addE(g, Location(5, 0), f);

    // inner cycle
    for (int i = 6; i < 13; i++) {
        addE(g, Location(i, i+1), f);
    }
    addE(g, Location(13, 6), f);

    // connect inner vertices to outer points
    addE(g, Location(0, 17), f);
    addE(g, Location(1, 14), f);
    addE(g, Location(2, 8), f);
    addE(g, Location(3, 15), f);
    addE(g, Location(4, 16), f);
    addE(g, Location(5, 12), f);

    // connect 6 and 10
    addE(g, Location(6, 10), f);

    // finish right star
    addE(g, Location(7, 15), f);
    addE(g, Location(9, 14), f);
    addE(g, Location(14, 15), f);

    // finish left star
    addE(g, Location(11, 17), f);
    addE(g, Location(13, 16), f);
    addE(g, Location(16, 17), f);

    return g;
}
