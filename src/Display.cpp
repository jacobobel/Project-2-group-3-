#include "Display.h"
#include <iostream>
#include <algorithm>

void printGrid(const Grid& grid, const PathResult& result){
    for(int r = 0; r < grid.getRows(); r++){
        for(int c = 0; c < grid.getCols(); c++){
            int index = grid.getIndex(r,c);
            if(index == grid.getStartIndex()){
                std::cout << 'S';
            }
            else if(index == grid.getGoalIndex()){
                std::cout << 'G';
            }
            else if(grid.getCell(index).blocked){
                std::cout << '#';
            }
            else if(std::find(result.path.begin(), result.path.end(), index) != result.path.end()){
                std::cout << '*';
            }
            else if(std::find(result.exploredCells.begin(), result.exploredCells.end(), index) != result.exploredCells.end()){
                std::cout << 'o';
            }
            else{
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
}