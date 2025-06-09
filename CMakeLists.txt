cmake_minimum_required(VERSION 3.30)
project(projekt2_aizo)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_FLAGS "-static")

add_executable(projekt2_aizo main.cpp
        enums/GraphType.h
        core/Timer.cpp
        enums/AlgorithmType.h
        enums/GraphDirection.h
        algorithms/Kruskal.cpp
        algorithms/Kruskal.h
        structures/Node.cpp
        structures/Node.h
        structures/graphs/GraphIncMatrix.cpp
        structures/graphs/GraphIncMatrix.h
        structures/graphs/GraphAdjList.cpp
        structures/graphs/GraphAdjList.h
        structures/Edge.h
        algorithms/HeapSort.h
        algorithms/HeapSort.cpp
        algorithms/Prim.cpp
        algorithms/Prim.h
        algorithms/Dijkstra.cpp
        algorithms/Dijkstra.h
        algorithms/BellmanFord.cpp
        algorithms/BellmanFord.h
        structures/MinHeap.cpp
        structures/MinHeap.h
        core/Generator.cpp
        core/Generator.h
        core/FileManager.cpp
        core/FileManager.h
        modes/Benchmark.cpp
        modes/Benchmark.h
)
