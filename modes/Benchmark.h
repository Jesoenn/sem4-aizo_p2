//
// Created by jakub on 30.05.2025.
//

#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <string>

#include "../core/FileManager.h"
#include "../core/Timer.h"
#include "../enums/AlgorithmType.h"
#include "../enums/GraphDirection.h"
#include "../enums/GraphType.h"
#include "../structures/Node.h"


class Benchmark {
public:
    //projekt2_aizo.exe --test <graph> <algorithm> <vertices> <density> <outputfile>
    Benchmark(int graph, int algorithm, int vertices, int density, std::string outputFile);
    void start();

private:
    GraphType graphType;
    AlgorithmType algorithm;
    int vertices,edges;
    int density;
    std::string outputFile;

    Timer timer;
    int time;
    int algorithmTime;

    Edge* generateEdges(GraphDirection graphDirection);
    int** generateIncMatrix(Edge* edgeArray, GraphDirection graphDirection);
    Node** generateAdjList(Edge* edgeArray, GraphDirection graphDirection);
    void performKruskal(Edge* edgeArray);
    void performPrim(int** incMatrix, Node** adjList);            // Kruskal/Prim
    void performDijkstra(int** incMatrix, Node** adjList);
    void performBellmanFord(int** incMatrix, Node** adjList);
    void deleteGraph(int** incMatrix, Node** adjList);

};



#endif //BENCHMARK_H
