# builds the whole project - the app itself plus one test executable
# per part, so a broken piece doesn't stop the others from building.
#
# to build everything: cmake -B build && cmake --build build
# then run whichever one you want, e.g. ./build/test_dijkstra

cmake_minimum_required(VERSION 3.10)
project(PathfindingProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# the actual program - grid + both algorithms + display
add_executable(app
    src/main.cpp
    src/Grid.cpp
    src/Dijkstra.cpp
    src/AStar.cpp
    src/Display.cpp
    src/PathResult.cpp
)

# jacobo's grid test
add_executable(test_grid
    tests/test1.cpp
    src/Grid.cpp
)

# joseph's dijkstra tests
add_executable(test_dijkstra
    tests/test3.cpp
    src/Grid.cpp
    src/Dijkstra.cpp
)
# these tests rely on assert() actually running, so don't let a Release
# build sneak NDEBUG in and turn them into no-ops
target_compile_options(test_dijkstra PRIVATE -UNDEBUG)

# anat's A* test - heads up, this one won't build yet, AStar.cpp still
# references result.found / result.totalCost which don't exist on the
# current PathResult (should be pathFound / pathCost). leaving the
# target here so it just starts working once that gets fixed.
add_executable(test_astar
    tests/test2.cpp
    src/Grid.cpp
    src/AStar.cpp
)
