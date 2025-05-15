//
// Created by jakub on 2025-05-13.
//

#ifndef PROJEKT2_AIZO_GRAPHINCMATRIX_H
#define PROJEKT2_AIZO_GRAPHINCMATRIX_H
#include "../Edge.h"
#include "../../enums/GraphDirection.h"


class GraphIncMatrix {
public:
    GraphIncMatrix(int edges, int vertices, GraphDirection graphDirection);
    ~GraphIncMatrix();

    //Edge* getEdgeArray();   //Zwraca tablice wszystkich krawedzi
    void addEdge(int vFrom, int vTo, int weight);
    Edge* getEdgeArray();
    void print();

private:
    void initialize();

    int lastEdge;
    GraphDirection graphDirection;
    int edges, vertices;
    int** incMatrix;
};

#endif //PROJEKT2_AIZO_GRAPHINCMATRIX_H
