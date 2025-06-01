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
    int vertices;
    int density;
    std::string outputFile;

    Timer timer;
    int algorithmTime;

    int** generateIncMatrix(GraphDirection graphDirection);
    Node** generateAdjList(GraphDirection graphDirection);
    void startMST();            // Kruskal/Prim
    void startPath();           // Dijkstra/Bellman-Ford

};



#endif //BENCHMARK_H
