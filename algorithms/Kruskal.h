//
// Created by jakub on 2025-05-12.
//

#ifndef PROJEKT2_AIZO_KRUSKAL_H
#define PROJEKT2_AIZO_KRUSKAL_H


#include "../structures/Edge.h"
#include "../enums/GraphType.h"
#include "../structures/GraphAdjList.h"
#include "../structures/GraphIncMatrix.h"

class Kruskal {
public:
    Kruskal(int vertices, int edges, Edge* edgeArray);
    ~Kruskal();
    void start();

private:
    int vertices, edges;
    int* parents;                       //index is vertex, key is parent of each vertex
    int* ranks;                         //
    Edge* edgeArray;
    Edge* mstArray;
    GraphType graphType;

    void makeSet(int v);                //set parents for each vertex
    int findSet(int v);
    void unionSets(int v1, int v2);

    void sortEdges();                   //from lowest to highest weight
};

#endif //PROJEKT2_AIZO_KRUSKAL_H
