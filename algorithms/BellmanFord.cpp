//
// Created by jakub on 2025-05-26.
//

#include "BellmanFord.h"
#include <limits>
#include <iostream>

BellmanFord::BellmanFord(int vertices, int edges, int **incMatrix):
    vertices(vertices),
    edges(edges),
    incMatrix(incMatrix),
    graphType(GraphType::INCIDENCE_MATRIX){
    parent = new int[vertices];
    weights = new int[vertices];
    adjList = nullptr;
}

BellmanFord::BellmanFord(int vertices, int edges, Node **adjList):
    vertices(vertices),
    edges(edges),
    adjList(adjList),
    graphType(GraphType::ADJACENCY_LIST){
    parent = new int[vertices];
    weights = new int[vertices];
    incMatrix = nullptr;
}

BellmanFord::~BellmanFord() {
    delete[] weights;
    delete[] parent;
}

void BellmanFord::start() {
    initializeSingleSource();
    if(graphType == GraphType::ADJACENCY_LIST){
        adjListVersion();
    } else{
        incMatrixVersion();
    }
}

void BellmanFord::adjListVersion() {
    for(int i=0; i<vertices-1; i++){

    }
}

void BellmanFord::incMatrixVersion() {

}

void BellmanFord::initializeSingleSource() {
    parent[0] = 0;
    weights[0] = 0;

    for(int i = 1; i<vertices; i++){
        parent[i] = -1;
        weights[i] = std::numeric_limits<int>::max();   //INF
    }
}

bool BellmanFord::relax(int u, int v, int w) {
    return false;
}

void BellmanFord::print() {

}
