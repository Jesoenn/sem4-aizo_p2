//
// Created by jakub on 2025-05-13.
//

#ifndef PROJEKT2_AIZO_GRAPHADJLIST_H
#define PROJEKT2_AIZO_GRAPHADJLIST_H


#include "../enums/GraphDirection.h"
#include "Node.h"

class GraphAdjList {
public:
    GraphAdjList(int edges, int vertices, GraphDirection graphDirection);
    ~GraphAdjList();

    void addEdge(int vFrom, int vTo, int weight);
    void print();

private:
    void initialize();

    GraphDirection graphDirection;
    int edges, vertices;
    Node** adjList;
};


#endif //PROJEKT2_AIZO_GRAPHADJLIST_H
