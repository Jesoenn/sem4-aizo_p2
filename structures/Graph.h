//
// Created by jakub on 2025-05-12.
//

#ifndef PROJEKT2_AIZO_GRAPH_H
#define PROJEKT2_AIZO_GRAPH_H


#include "../enums/GraphType.h"
#include "../enums/GraphDirection.h"
#include "Node.h"

class Graph {
public:
    Graph(int edges, int vertices, GraphType graphType, GraphDirection graphDirection);
    ~Graph();

    void addEdge(int vFrom, int vTo, int weight);
    void printGraph();

private:
    void initializeMatrix();
    void initializeAdjList();
    void addEdgeAdjList(int vFrom, int vTo, int weight);
    void addEdgeMatrix(int vFrom, int vTo, int weight);
    void printMatrix();
    void printList();


    int lastEdge;
    GraphType graphType;
    GraphDirection graphDirection;
    int edges, vertices;
    int** incMatrix;
    Node** adjList;
    //adj list here
};


#endif //PROJEKT2_AIZO_GRAPH_H
