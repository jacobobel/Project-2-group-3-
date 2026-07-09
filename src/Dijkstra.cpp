#include "Dijkstra.h"
#include <queue>
#include <vector>
#include <chrono>
#include <algorithm>
#include <climits>

using namespace std;

struct DijkstraNode {
    int index;
    int priority; // just cost-so-far here, no heuristic like AStar has
};

struct CompareNode {
    bool operator()(DijkstraNode a, DijkstraNode b) {
        return a.priority > b.priority;
    }
};

vector<int> Dijkstra::buildPath(const vector<int>& parent, int start, int goal) {
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

PathResult Dijkstra::findPath(const Grid& grid) {
    auto begin = chrono::high_resolution_clock::now();

    PathResult result;
    result.pathFound = false;
    result.nodesExplored = 0;
    result.pathCost = 0;
    result.algorithmName = "Dijkstra";

    int start = grid.getStartIndex();
    int goal = grid.getGoalIndex();
    int size = grid.getRows() * grid.getCols();

    vector<int> cost(size, INT_MAX);
    vector<int> parent(size, -1);
    vector<bool> visited(size, false);

    priority_queue<DijkstraNode, vector<DijkstraNode>, CompareNode> pq;

    cost[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        int current = pq.top().index;
        pq.pop();

        if (visited[current]) {
            continue;
        }

        visited[current] = true;
        result.nodesExplored++;
        result.exploredCells.push_back(current);

        if (current == goal) {
            result.pathFound = true;
            result.pathCost = cost[goal];
            result.path = buildPath(parent, start, goal);
            break;
        }

        vector<int> neighbors = grid.getNeighbors(current);

        for (int next : neighbors) {
            if (visited[next]) {
                continue;
            }

            const Cell& nextCell = grid.getCell(next);
            int newCost = cost[current] + nextCell.terrainCost;

            if (newCost < cost[next]) {
                cost[next] = newCost;
                parent[next] = current;
                pq.push({next, newCost});
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> time = end - begin;
    result.runtimeMs = time.count();

    return result;
}
