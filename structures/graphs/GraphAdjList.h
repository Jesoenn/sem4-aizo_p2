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

    void addEdge(int vFrom, int vTo, int weight) const;
    void print() const;
    [[nodiscard]] Edge* getEdgeArray() const;   //convert list to edge array (UNDIRECTED)
    [[nodiscard]] Node** getAdjList() const;

private:
    void initialize();

    GraphDirection graphDirection;
    int edges, vertices;
    Node** adjList;         //array, each index is vertex, each element is neighbouring edge
};


#endif //PROJEKT2_AIZO_GRAPHADJLIST_H
