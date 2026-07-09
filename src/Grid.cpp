#include "Grid.h"
#include <random>

Grid::Grid(int rows, int cols)
    : rows(rows), cols(cols), startIndex(-1), goalIndex(-1)
{
    cells.resize(rows * cols);

    for(int r = 0; r < rows; r++){
        for(int c = 0; c < cols; c++){
            int idx = getIndex(r,c);
            cells[idx].row = r;
            cells[idx].col = c;
        }
    }
}


int Grid::getIndex(int row, int col) const{
    return row * cols + col;
}

bool Grid::inBounds(int row, int col) const{
    if(row < 0 || row >= rows){
        return false;
    }
    if(col < 0 || col >= cols){
        return false;
    }
    return true;
}

const Cell& Grid::getCell(int index) const {
    return cells[index];
}
Cell& Grid::getCell(int index){
    return cells[index];
}

void Grid::setBlocked(int row, int col, bool blocked){
    if(!inBounds(row,col)){
        return;
    }
    int index = getIndex(row, col);
    Cell& cell = getCell(index);
    cell.blocked = blocked;
    return;
}

void Grid::setStart(int row, int col){
    if(!inBounds(row,col)){
        return;
    }

    int index = getIndex(row,col);
    Cell& cell = getCell(index);

    if(cell.blocked){
        return;
    }

    this->startIndex = index;
    return; 
}

void Grid::setGoal(int row, int col){
    if(!inBounds(row,col)){
        return;
    }

    int index = getIndex(row,col);
    Cell& cell = getCell(index);

    if(cell.blocked){
        return;
    }
    this->goalIndex = index;
    return;
}

std::vector<int> Grid::getNeighbors(int index) const{
    std::vector<int> neighbors;

    int row = index / cols;
    int col = index % cols;
    int upRow = row - 1;
    int upCol = col;
    if(inBounds(upRow, upCol)){
        int upIndex = getIndex(upRow, upCol);
        const Cell& cell = getCell(upIndex);
        if(!cell.blocked){
            neighbors.push_back(upIndex);
        }
    }
    int downRow = row + 1;
    int downCol = col;
    if(inBounds(downRow, downCol)){
        int downIndex = getIndex(downRow, downCol);
        const Cell& cell = getCell(downIndex);
        if(!cell.blocked){
            neighbors.push_back(downIndex);
        }
    }

    int leftRow = row;
    int leftCol = col - 1;
    if(inBounds(leftRow, leftCol)){
        int leftIndex = getIndex(leftRow, leftCol);
        const Cell& cell = getCell(leftIndex);
        if(!cell.blocked){
            neighbors.push_back(leftIndex);
        }
    }

    int rightRow = row;
    int rightCol = col + 1;
    if(inBounds(rightRow, rightCol)){
        int rightIndex = getIndex(rightRow, rightCol);
        const Cell& cell = getCell(rightIndex);
        if(!cell.blocked){
            neighbors.push_back(rightIndex);
        }
    }
    return neighbors;
}

int Grid::getStartIndex() const{
    return this->startIndex;
}

int Grid::getGoalIndex() const{
    return this->goalIndex;
}

int Grid::getRows() const{
    return this->rows;
}

int Grid::getCols() const{
    return this->cols;
}

void Grid::setTerrainCost(int row, int col, int cost){
    if(!inBounds(row, col)){
        return;
    }
    int index = getIndex(row,col);
    Cell& cell = getCell(index);
    cell.terrainCost = cost;
    return;
}

void Grid::generateMap(double obstaclePercentage, int maxTerrainCost) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::uniform_int_distribution<int> costDist(1, maxTerrainCost);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            double randomValue = dist(gen);

            if (randomValue < obstaclePercentage) {
                setBlocked(r, c, true);
            } else {
                int cost = costDist(gen);
                setTerrainCost(r, c, cost);
            }
        }
    }

    if (startIndex != -1) {
        Cell& startCell = getCell(startIndex);
        setBlocked(startCell.row, startCell.col, false);
    }
    if (goalIndex != -1) {
        Cell& goalCell = getCell(goalIndex);
        setBlocked(goalCell.row, goalCell.col, false);
    }
}