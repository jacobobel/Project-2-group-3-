#ifndef PATHRESULT_H
#define PATHRESULT_H

#include <vector>
#include <string>

struct PathResult {
    std::vector<int> path;
    std::vector<int> exploredCells;
    int nodesExplored = 0;
    int pathCost = 0;
    std::string algorithmName;
    bool pathFound = false;
    double runtimeMs = 0.0;
};

#endif