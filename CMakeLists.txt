
cmake_minimum_required(VERSION 3.10)
project(PathfindingProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(app
    src/main.cpp
    src/Grid.cpp
    src/Dijkstra.cpp
    src/AStar.cpp
    src/Display.cpp
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

target_compile_options(test_dijkstra PRIVATE -UNDEBUG)


add_executable(test_astar
    tests/test2.cpp
    src/Grid.cpp
    src/AStar.cpp
)
