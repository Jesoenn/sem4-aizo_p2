//
// Created by jakub on 15.05.2025.
//

#ifndef PRIM_H
#define PRIM_H
#include "../enums/GraphType.h"
#include "../structures/Node.h"
#include "iostream"
#include "../structures/Edge.h"
#include "../structures/MinHeap.h"


class Prim {
public:
    Prim(int vertices, int edges, int** incMatrix);
    Prim(int vertices, int edges, Node** adjList);
    ~Prim();
    void start();
    void print();

private:
    GraphType graphType;
    int vertices, edges, interval, progress;
    int* parents;           //parent of each vertex
    Node** adjList;
    int** incMatrix;
    Edge* mstArray;
    int mstEdges = 0;

    void adjListVersion(MinHeap& minHeap);
    void incMatrixVersion(MinHeap& minHeap);
    void addToMST(int u, int weight);
};



#endif //PRIM_H
