#ifndef COLORINGS
#define COLORINGS

#include <vector>
#include <string>
#include <algorithm>
#include <set>

#include <graphs.hpp>
#include <multipoles.hpp>

#include "../implementation.h"

using namespace ba_graph;

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

std::string translate_colouring_to_class(const std::vector<std::vector<int>>& multipole_colourings) {
    std::map<std::vector<std::vector<int>>, std::string> classes{
            {{{0,1,2,2,2},{0,1,2,1,1},{0,1,1,2,1},{0,1,1,1,2}} , "perfect"},
            {{} , "uncolourable"},
            {{{0,1,2,2,2},{0,1,2,1,1}} , "1A"},
            {{{0,1,2,2,2},{0,1,1,2,1}} , "1A"},
            {{{0,1,2,2,2},{0,1,1,1,2}} , "1A"},
            {{{0,1,2,2,2},{0,1,2,1,1},{0,1,1,2,1}} , "2A"},
            {{{0,1,2,2,2},{0,1,2,1,1},{0,1,1,1,2}} , "2A"},
            {{{0,1,2,2,2},{0,1,1,2,1},{0,1,1,1,2}} , "2A"},
            {{{0,1,2,1,1},{0,1,1,2,1}} , "2B"},
            {{{0,1,2,1,1},{0,1,1,1,2}} , "2B"},
            {{{0,1,1,2,1},{0,1,1,1,2}} , "2B"},
            {{{0,1,2,1,1},{0,1,1,2,1},{0,1,1,1,2}} , "3B"},
            {{{0,1,2,1,1},{0,1,1,2,1},{0,1,1,1,2}} , "3B"},
            {{{0,1,2,1,1},{0,1,1,2,1},{0,1,1,1,2}} , "3B"},
    };

    return classes[multipole_colourings];
}


#endif
