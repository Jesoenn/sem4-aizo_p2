//
// Created by jakub on 2025-05-13.
//

#ifndef PROJEKT2_AIZO_GRAPHADJLIST_H
#define PROJEKT2_AIZO_GRAPHADJLIST_H
#include "../Edge.h"
#include "../Node.h"
#include "../../enums/GraphDirection.h"


class GraphAdjList {
public:
    GraphAdjList(int edges, int vertices, GraphDirection graphDirection);
    //~GraphAdjList();

    void addEdge(int vFrom, int vTo, int weight);
    void print();
    Edge* getEdgeArray();   //convert list to edge array
    Node** getAdjList();

private:
    void initialize();

    GraphDirection graphDirection;
    int edges, vertices;
    Node** adjList;         //array, each index is vertex, each element is neighbouring edge
};


#endif //PROJEKT2_AIZO_GRAPHADJLIST_H
