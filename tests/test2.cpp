#include "Grid.h"
#include "Display.h"
#include "PathResult.h"
#include <iostream>

int main() {
    Grid grid(5, 5);
    grid.setBlocked(2, 2, true);
    grid.setStart(0, 0);
    grid.setGoal(4, 4);

    PathResult result;
    // fill in result.path, result.exploredCells, and whatever else you want for testing

    printGrid(grid, result);

    return 0;
}