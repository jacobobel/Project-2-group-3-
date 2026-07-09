#pragma once
#include "Grid.h"
#include "PathResult.h"
#include <vector>

class AStar {
public:
    static PathResult findPath(const Grid& grid);
private:
    static int manhattan(const Grid& grid, int current, int goal);
    static std::vector<int> buildPath(const std::vector<int>& parent, int start, int goal);
};