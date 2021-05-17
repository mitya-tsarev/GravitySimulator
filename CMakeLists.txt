cmake_minimum_required(VERSION 3.15)
project(GravitySimulator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp src/Simulator.cpp src/AbstractUniverse.cpp src/BarnesHutUniverse.cpp
        src/Body.cpp src/vector.cpp src/NeighbourSchemeUniverse.cpp include/NeighbourSchemeUniverse.h src/HermitBody.cpp
        include/HermitBody.h src/SimpleUniverse.cpp include/SimpleUniverse.h src/LinearTimeUniverse.cpp include/LinearTimeUniverse.h
        src/OctTree.cpp include/OctTree.h include/Constants.h include/utilities.h src/utilities.cpp)

enable_testing()
# add_subdirectory(tests)
add_executable(GravitySimulator ${SOURCE_FILES})