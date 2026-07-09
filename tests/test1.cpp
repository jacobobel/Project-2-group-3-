#include "Grid.h"
#include <iostream>

int main() {
    Grid grid(5, 5);

    grid.setBlocked(2, 2, true);
    grid.setStart(0, 0);
    grid.setGoal(4, 4);

    std::cout << "Start index: " << grid.getStartIndex() << " (expected: 0)" << std::endl;
    std::cout << "Goal index: " << grid.getGoalIndex() << " (expected: 24)" << std::endl;

    // Cell (2,1) is directly left of the blocked cell (2,2).
    // Its neighbors are (1,1) up, (3,1) down, (2,0) left, (2,2) right — but (2,2) is blocked.
    int testIndex = grid.getIndex(2, 1);
    std::vector<int> neighbors = grid.getNeighbors(testIndex);

    std::cout << "Neighbors of (2,1): ";
    for (int n : neighbors) {
        Cell& c = grid.getCell(n);
        std::cout << "(" << c.row << "," << c.col << ") ";
    }
    std::cout << std::endl;
    std::cout << "Expected: (1,1) (3,1) (2,0) -- should NOT include (2,2)" << std::endl;

    return 0;
}