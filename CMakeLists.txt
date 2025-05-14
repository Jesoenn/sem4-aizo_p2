cmake_minimum_required(VERSION 3.26)
project(projekt2_aizo)

set(CMAKE_CXX_STANDARD 23)

add_executable(projekt2_aizo main.cpp
        structures/Graph.cpp
        structures/Graph.h
        enums/GraphType.h
        core/Timer.cpp
        enums/AlgorithmType.h
        enums/GraphDirection.h
        algorithms/Kruskal.cpp
        algorithms/Kruskal.h
        structures/Node.cpp
        structures/Node.h
        structures/GraphIncMatrix.cpp
        structures/GraphIncMatrix.h
        structures/GraphAdjList.cpp
        structures/GraphAdjList.h
        structures/Edge.h
        algorithms/HeapSort.h
        algorithms/HeapSort.cpp)
