#include "AStar.h"
#include <queue>
#include <vector>
#include <chrono>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

struct AStarNode {
    int index;
    int priority;
};

struct CompareNode {
    bool operator()(AStarNode a, AStarNode b) {
        return a.priority > b.priority;
    }
};

int AStar::manhattan(const Grid& grid, int current, int goal) {
    Cell currentCell = grid.getCell(current);
    Cell goalCell = grid.getCell(goal);

    return abs(currentCell.row - goalCell.row) + abs(currentCell.col - goalCell.col);
}

vector<int> AStar::buildPath(const vector<int>& parent, int start, int goal) {
    vector<int> path;
    int current = goal;

    while (current != -1) {
        path.push_back(current);

        if (current == start) {
            break;
        }

        current = parent[current];
    }

    reverse(path.begin(), path.end());
    return path;
}

PathResult AStar::findPath(const Grid& grid) {
    auto begin = chrono::high_resolution_clock::now();

    PathResult result;

    int start = grid.getStartIndex();
    int goal = grid.getGoalIndex();
    int size = grid.getRows() * grid.getCols();

    vector<int> cost(size, INT_MAX);
    vector<int> parent(size, -1);
    vector<bool> visited(size, false);

    priority_queue<AStarNode, vector<AStarNode>, CompareNode> pq;

    cost[start] = 0;
    pq.push({start, manhattan(grid, start, goal)});

    while (!pq.empty()) {
        int current = pq.top().index;
        pq.pop();

        if (visited[current]) {
            continue;
        }

        visited[current] = true;
        result.nodesExplored++;

        if (current == goal) {
            result.found = true;
            result.totalCost = cost[goal];
            result.path = buildPath(parent, start, goal);
            break;
        }

        vector<int> neighbors = grid.getNeighbors(current);

        for (int next : neighbors) {
            Cell nextCell = grid.getCell(next);

            int newCost = cost[current] + nextCell.terrainCost;

            if (newCost < cost[next]) {
                cost[next] = newCost;
                parent[next] = current;

                int priority = newCost + manhattan(grid, next, goal);
                pq.push({next, priority});
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time = end - begin;
    result.runtimeMs = time.count();

    return result;
}