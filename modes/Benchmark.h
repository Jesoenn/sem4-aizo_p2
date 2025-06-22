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
    Benchmark(int graph, int algorithm, int vertices, int density, std::string outputFile, int printGraph);
    void start();

private:
    GraphType graphType;        //IncMatrix/AdjList
    AlgorithmType algorithm;    //Kruskal/Prim/Dijkstra/BellmanFord
    int vertices,edges;         //Number of v/e
    int density;                //0->100 [%]
    std::string outputFile;
    bool printGraph;

    Timer timer;
    int time;           //time it took for algorithm to complete

    Edge* generateEdges(GraphDirection graphDirection);
    int** generateIncMatrix(const Edge* edgeArray, GraphDirection graphDirection) const;
    Node** generateAdjList(const Edge* edgeArray, GraphDirection graphDirection) const;

    void performKruskal(const Edge* edgeArray);
    void performPrim(int** incMatrix, Node** adjList);
    void performDijkstra(int** incMatrix, Node** adjList);
    void performBellmanFord(int** incMatrix, Node** adjList);
    void deleteGraph(int** incMatrix, Node** adjList) const;
};



#endif //BENCHMARK_H
