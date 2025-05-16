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

    void addEdge(int vFrom, int vTo, int weight);
    Edge* getEdgeArray();   //returns edge array of matrix
    void print();
    int** getIncMatrix();

private:
    void initialize();

    int lastEdge;   //last added edge index
    GraphDirection graphDirection;
    int edges, vertices;
    int** incMatrix;
};

#endif //PROJEKT2_AIZO_GRAPHINCMATRIX_H
