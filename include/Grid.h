#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include <vector>

class Grid {
private:
    int rows;
    int cols;
    int startIndex;
    int goalIndex;
    std::vector<Cell> cells;

public:
    Grid(int rows, int cols);

    int getIndex(int row, int col) const;
    Cell& getCell(int index);
    const Cell& getCell(int index) const;

    bool inBounds(int row, int col) const;

    std::vector<int> getNeighbors(int index) const;

    void setBlocked(int row, int col, bool blocked);

    void setStart(int row, int col);
    void setGoal(int row, int col);

    int getStartIndex() const;
    int getGoalIndex() const;
    int getRows() const;
    int getCols() const;
    
    void setTerrainCost(int row, int col, int cost);
    void generateMap(double obstaclePercentage, int maxTerrainCost);
};

#endif