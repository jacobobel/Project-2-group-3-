#ifndef PATHRESULT_H
#define PATHRESULT_H

#include <vector>
#include <string>

struct PathResult {
    std::vector<int> path;
    std::vector<int> exploredCells;
    int nodesExplored;
    int pathCost;
    std::string algorithmName;
    bool pathFound;
    double runtimeMs;
};

#endif
