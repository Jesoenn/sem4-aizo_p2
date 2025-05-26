//
// Created by jakub on 2025-05-12.
//

#ifndef PROJEKT2_AIZO_KRUSKAL_H
#define PROJEKT2_AIZO_KRUSKAL_H


#include "../structures/Edge.h"
#include "../enums/GraphType.h"
#include "../structures/graphs/GraphAdjList.h"
#include "../structures/graphs/GraphIncMatrix.h"

class Kruskal {
public:
    Kruskal(int vertices, int edges, Edge* edgeArray);
    ~Kruskal();
    void start();
    void print();

private:
    int vertices, edges;
    int* parents;                       //index is vertex, key is parent of each vertex
    int* ranks;
    Edge* edgeArray;
    Edge* mstArray;

    void makeSet(int v);                //set parents for each vertex
    int findSet(int v);                 //find root of given vertex
    void unionSets(int v1, int v2);     //combine sets

    void sortEdges();                   //from lowest to highest weight
};

#endif //PROJEKT2_AIZO_KRUSKAL_H
