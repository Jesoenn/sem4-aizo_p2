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

    void addEdge(int vFrom, int vTo, int weight);
    [[nodiscard]] Edge* getEdgeArray() const;   //returns edge array from incidence matrix (UNDIRECTED)
    void print() const;
    [[nodiscard]] int** getIncMatrix() const;

private:
    void initialize();

    int lastEdge;   //last added edge index
    GraphDirection graphDirection;
    int edges, vertices;
    int** incMatrix;
};

#endif //PROJEKT2_AIZO_GRAPHINCMATRIX_H
