//
// Created by jakub on 2025-05-26.
//

#ifndef PROJEKT2_AIZO_BELLMANFORD_H
#define PROJEKT2_AIZO_BELLMANFORD_H


#include "../structures/Node.h"
#include "../enums/GraphType.h"

class BellmanFord {
public:
    BellmanFord(int vertices, int edges, int** incMatrix);
    BellmanFord(int vertices, int edges, Node** adjList);
    ~BellmanFord();
    void start();
    void print();
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


#endif //PROJEKT2_AIZO_BELLMANFORD_H
