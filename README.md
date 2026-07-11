# Dijkstra's Algorithm vs. A* Pathfinding

Project 2 for COP3530 (Data Structures and Algorithms), Summer C 2026 — University of Florida.

## Overview

This project compares Dijkstra's Algorithm and A* Search on the same shortest-path problem: navigating
a large grid that contains obstacles and cells with different movement costs. Both algorithms run on
the exact same generated grid, with the same start and goal points, so their results (path cost,
runtime, nodes explored) can be directly compared.

## Features

- 320x320 grid (102,400 cells) with randomly generated obstacles and terrain costs
- Dijkstra's Algorithm and A* Search, both implemented from scratch using a binary min-heap
- Shared `PathResult` output (path, explored cells, path cost, nodes explored, runtime) so both
  algorithms' results line up for comparison
- Text-based grid display showing obstacles, start/goal, and the final path
- Console comparison output: runtime, nodes explored, path length, and path cost for both algorithms

## Project Structure

```
include/        Header files (Grid.h, Cell.h, PathResult.h, Dijkstra.h, AStar.h, Display.h)
src/            Implementation files (Grid.cpp, Dijkstra.cpp, AStar.cpp, Display.cpp, main.cpp)
tests/          Individual test files for Grid, Dijkstra, and A*
CMakeLists.txt  Build configuration
```

## Requirements

- A C++17-compatible compiler (e.g. clang++ or g++)
- CMake 3.10 or newer

On macOS, if you don't have CMake installed:
```
brew install cmake
```

## Building and Running

From the project root:

```
cmake -B build
cmake --build build --target app
./build/app
```

This builds and runs the main program, which generates a 320x320 grid, runs both Dijkstra and A* on
it, and prints a comparison of their results to the console.

### Running the individual tests

```
cmake --build build --target test_grid
./build/test_grid

cmake --build build --target test_dijkstra
./build/test_dijkstra

cmake --build build --target test_astar
./build/test_astar
```

## Team

- Jacobo Belilty ([jacobobel](https://github.com/jacobobel)) — Grid, PathResult, Display, integration, build system
- Joseph Gedaly ([josephgedaly](https://github.com/josephgedaly)) — Dijkstra's Algorithm
- Anat Bimblich — A* Search

## References

- Cormen, Thomas H., et al. *Introduction to Algorithms*.
- Hart, Peter E., Nils J. Nilsson, and Bertram Raphael. "A Formal Basis for the Heuristic
  Determination of Minimum Cost Paths." 1968.