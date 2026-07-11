#include "Grid.h"
#include "Dijkstra.h"
#include "AStar.h"
#include "Display.h"
#include <iostream>

void printStats(const PathResult& result) {
    std::cout << "--- " << result.algorithmName << " ---" << std::endl;
    std::cout << "Path found: " << (result.pathFound ? "yes" : "no") << std::endl;
    std::cout << "Runtime: " << result.runtimeMs << " ms" << std::endl;
    std::cout << "Nodes explored: " << result.nodesExplored << std::endl;
    std::cout << "Path length: " << result.path.size() << std::endl;
    std::cout << "Path cost: " << result.pathCost << std::endl;
    std::cout << std::endl;
}

int main() {
    Grid grid(320, 320);
    grid.generateMap(0.2, 5);
    grid.setStart(0, 0);
    grid.setGoal(319, 319);

    PathResult dijkstraResult = Dijkstra::findPath(grid);
    PathResult astarResult = AStar::findPath(grid);

    printStats(dijkstraResult);
    printStats(astarResult);

    return 0;
}