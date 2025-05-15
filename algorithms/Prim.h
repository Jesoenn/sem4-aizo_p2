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

private:
    GraphType graphType;
    int vertices, edges;
    int* parents;
    Node** adjList;
    int** incMatrix;
    Edge* mstArray;

    void adjListVersion(MinHeap& minHeap);

};



#endif //PRIM_H
