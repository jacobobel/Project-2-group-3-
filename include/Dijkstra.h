#pragma once
#include "Grid.h"
#include "PathResult.h"
#include <vector>

// same shape as AStar (static findPath(grid)) so main.cpp can call both
// the same way and just compare the two PathResults
class Dijkstra {
public:
    static PathResult findPath(const Grid& grid);
private:
    static std::vector<int> buildPath(const std::vector<int>& parent, int start, int goal);
};
