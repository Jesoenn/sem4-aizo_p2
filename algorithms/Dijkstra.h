//
// Created by jakub on 2025-05-26.
//

#ifndef PROJEKT2_AIZO_DIJKSTRA_H
#define PROJEKT2_AIZO_DIJKSTRA_H


#include "../enums/GraphType.h"
#include "../structures/Edge.h"
#include "../structures/Node.h"

class Dijkstra {
public:
    Dijkstra(int vertices, int edges, int** incMatrix);
    Dijkstra(int vertices, int edges, Node** adjList);
    ~Dijkstra();
    void start();
    void print();
    Edge* getPath(int startV, int endV, bool print);
    int getPathLength(int startV, int endV);

private:
    void initializeSingleSource();
    void incMatrixVersion();
    void adjListVersion();
    bool relax(int u, int v, int w);

    GraphType graphType;
    int vertices,edges;

    Node** adjList;
    int** incMatrix;

    int* parent;    // pi
    int* weights;   // d
};


#endif //PROJEKT2_AIZO_DIJKSTRA_H
