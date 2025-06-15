//
// Created by jakub on 15.06.2025.
//

#ifndef FILETEST_H
#define FILETEST_H
#include <string>

#include "../core/Timer.h"
#include "../enums/AlgorithmType.h"
#include "../enums/GraphDirection.h"
#include "../enums/GraphType.h"
#include "../structures/Edge.h"
#include "../structures/Node.h"


class FileTest {
public:
    // projekt2_aizo.exe --file <graph> <algorithm> <inputFile> <printAnswer> <outputFile> [startVertex] [EndVertex]
    FileTest(int graph, int algorithm, std::string inputFile, int printAnswer, std::string outputFile, int startVertex, int endVertex);
    void start();

private:
    GraphType graphType;        //IncMatrix/AdjList
    AlgorithmType algorithm;    //Kruskal/Prim/Dijkstra/BellmanFord
    int vertices,edges;         //Number of v/e
    std::string inputFile,outputFile;
    bool printAnswer;
    int startVertex,endVertex;

    Timer timer;
    int time;           //time it took for algorithm to complete

    int** generateIncMatrix(Edge* edgeArray, GraphDirection graphDirection);
    Node** generateAdjList(Edge* edgeArray, GraphDirection graphDirection);

    Edge* performKruskal(Edge* edgeArray, int &answerEdges);
    Edge* performPrim(int** incMatrix, Node** adjList, int &answerEdges);
    Edge* performDijkstra(int** incMatrix, Node** adjList, int &answerEdges);
    Edge* performBellmanFord(int** incMatrix, Node** adjList, int &answerEdges);
    void deleteGraph(int** incMatrix, Node** adjList);
};



#endif //FILETEST_H
