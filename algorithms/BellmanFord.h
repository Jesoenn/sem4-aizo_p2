//
// Created by jakub on 2025-05-26.
//

#ifndef PROJEKT2_AIZO_BELLMANFORD_H
#define PROJEKT2_AIZO_BELLMANFORD_H


#include "../structures/Node.h"
#include "../enums/GraphType.h"
#include "../structures/Edge.h"

class BellmanFord {
public:
    BellmanFord(int vertices, int edges, int** incMatrix, int source);
    BellmanFord(int vertices, int edges, Node** adjList, int source);
    ~BellmanFord();
    void start() const;
    void print() const; //print result
    [[nodiscard]] Edge* getPath(int startV, int endV, bool print) const;
    [[nodiscard]] int getPathLength(int startV, int endV) const;
private:
    void initializeSingleSource() const;
    void incMatrixVersion() const;
    void adjListVersion() const;
    [[nodiscard]] bool relax(int u, int v, int w) const;

    GraphType graphType;
    int vertices,edges, source;

    Node** adjList;
    int** incMatrix;

    int* parent;    // pi
    int* weights;   // d
};


#endif //PROJEKT2_AIZO_BELLMANFORD_H
