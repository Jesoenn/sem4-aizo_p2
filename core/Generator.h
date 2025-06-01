//
// Created by jakub on 21.05.2025.
//

#ifndef GENERATOR_H
#define GENERATOR_H
#include "../enums/GraphDirection.h"
#include "../structures/Edge.h"


class Generator {
public:
    Generator(int vertices, int density, GraphDirection graphDirection);
    ~Generator();
    void start();
    Edge* getEdges();
    int getEdgeCount();

private:
    int vertices, edges, currentEdge;
    GraphDirection graphDirection;
    Edge* edgeArray;
    bool** adjMatrix;

    void generateConnectedGraph();
    void generateEdges();
};



#endif //GENERATOR_H
