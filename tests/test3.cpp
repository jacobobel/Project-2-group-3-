// test file for Dijkstra, same idea as test1.cpp but for our part.
// each case builds a small grid where we know what the answer should be
// and asserts on it - if something's wrong the program stops right there
// and tells us which line failed.
//
// needs to be compiled without NDEBUG or the asserts get skipped (see
// the root CMakeLists.txt)

#include "Grid.h"
#include "Dijkstra.h"
#include <iostream>
#include <cassert>
#include <cmath>

// checks a path is actually walkable: starts/ends where expected, every
// step is a real neighbor, and nothing in it is blocked
void assertPathIsValid(const Grid& grid, int startIdx, int goalIdx, const std::vector<int>& path) {
    assert(!path.empty());
    assert(path.front() == startIdx);
    assert(path.back() == goalIdx);

    for (size_t i = 0; i < path.size(); i++) {
        assert(!grid.getCell(path[i]).blocked);

        if (i > 0) {
            int prevRow = grid.getCell(path[i - 1]).row;
            int prevCol = grid.getCell(path[i - 1]).col;
            int curRow = grid.getCell(path[i]).row;
            int curCol = grid.getCell(path[i]).col;

            int rowDiff = std::abs(curRow - prevRow);
            int colDiff = std::abs(curCol - prevCol);
            assert(rowDiff + colDiff == 1); // one step, one direction
        }
    }
}

// no obstacles, so the cheapest path is just manhattan distance.
// (0,0) to (9,9) -> 9+9 = 18
void test_no_obstacles() {
    Grid grid(10, 10);
    grid.setStart(0, 0);
    grid.setGoal(9, 9);

    PathResult result = Dijkstra::findPath(grid);

    assert(result.pathFound);
    assert(result.pathCost == 18);
    assert(result.path.size() == 19);
    assertPathIsValid(grid, grid.getStartIndex(), grid.getGoalIndex(), result.path);

    std::cout << "test_no_obstacles: OK\n";
}

// wall across row 5, one gap at col 7 - only way across is through it
void test_with_obstacles() {
    Grid grid(10, 10);
    for (int col = 0; col < 10; col++) {
        if (col != 7) grid.setBlocked(5, col, true);
    }
    grid.setStart(0, 0);
    grid.setGoal(9, 9);

    PathResult result = Dijkstra::findPath(grid);

    assert(result.pathFound);
    assertPathIsValid(grid, grid.getStartIndex(), grid.getGoalIndex(), result.path);

    int gapIndex = grid.getIndex(5, 7);
    bool wentThroughTheGap = false;
    for (int idx : result.path) {
        if (idx == gapIndex) wentThroughTheGap = true;
    }
    assert(wentThroughTheGap);

    std::cout << "test_with_obstacles: OK\n";
}

// goal is boxed in on all 4 sides, so there's no way in
void test_no_path() {
    Grid grid(10, 10);
    grid.setStart(0, 0);
    grid.setGoal(5, 5);

    grid.setBlocked(4, 5, true);
    grid.setBlocked(6, 5, true);
    grid.setBlocked(5, 4, true);
    grid.setBlocked(5, 6, true);

    PathResult result = Dijkstra::findPath(grid);

    assert(!result.pathFound);
    assert(result.path.empty());

    std::cout << "test_no_path: OK\n";
}

// start and goal are the same cell - cost 0, path of just that one cell
void test_start_equals_goal() {
    Grid grid(10, 10);
    grid.setStart(4, 4);
    grid.setGoal(4, 4);

    PathResult result = Dijkstra::findPath(grid);

    assert(result.pathFound);
    assert(result.pathCost == 0);
    assert(result.path.size() == 1);
    assert(result.path[0] == grid.getStartIndex());
    assert(result.nodesExplored == 1);

    std::cout << "test_start_equals_goal: OK\n";
}

// start and goal are neighbors, so it's one move
void test_adjacent_cells() {
    Grid grid(10, 10);
    grid.setStart(2, 2);
    grid.setGoal(2, 3);

    PathResult result = Dijkstra::findPath(grid);

    assert(result.pathFound);
    assert(result.pathCost == grid.getCell(grid.getGoalIndex()).terrainCost);
    assert(result.path.size() == 2);

    std::cout << "test_adjacent_cells: OK\n";
}

// this one's the important one - proves we're doing real weighted
// dijkstra and not just counting steps like a plain BFS would.
// direct route across row 0 costs 5 per cell (4 cells = 21 total, 5 moves)
// vs dropping to row 1 and back, all cost 1 (7 total, 7 moves)
// dijkstra has to pick the actually cheaper one even with more steps
void test_variable_cost() {
    Grid grid(10, 10);
    for (int col = 1; col <= 4; col++) {
        grid.setTerrainCost(0, col, 5);
    }
    grid.setStart(0, 0);
    grid.setGoal(0, 5);

    PathResult result = Dijkstra::findPath(grid);

    assert(result.pathFound);
    assert(result.pathCost == 7);
    assertPathIsValid(grid, grid.getStartIndex(), grid.getGoalIndex(), result.path);

    std::cout << "test_variable_cost: OK\n";
}

// bigger grid, mostly just to make sure nothing falls apart before the
// real 320x320 map. row 0 and the last column are kept obstacle-free so
// there's always at least an L-shaped route available
void test_large_map() {
    const int size = 100;
    Grid grid(size, size);

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            bool guaranteedOpenBorder = (row == 0) || (col == size - 1);
            if (!guaranteedOpenBorder && (row + col) % 5 == 0) {
                grid.setBlocked(row, col, true);
            }
        }
    }

    grid.setStart(0, 0);
    grid.setGoal(size - 1, size - 1);

    PathResult result = Dijkstra::findPath(grid);

    assert(result.pathFound);
    assertPathIsValid(grid, grid.getStartIndex(), grid.getGoalIndex(), result.path);
    assert(result.nodesExplored > 0);
    assert(result.runtimeMs >= 0.0);

    std::cout << "test_large_map: OK (nodes explored=" << result.nodesExplored
              << ", time=" << result.runtimeMs << "ms)\n";
}

int main() {
    test_no_obstacles();
    test_with_obstacles();
    test_no_path();
    test_start_equals_goal();
    test_adjacent_cells();
    test_variable_cost();
    test_large_map();

    std::cout << "\nall dijkstra tests passed\n";
    return 0;
}
