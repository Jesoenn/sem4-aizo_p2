//
// Created by jakub on 15.05.2025.
//

#include "Prim.h"

Prim::Prim(int vertices, int edges, int **incMatrix):
    vertices(vertices),
    edges(edges),
    incMatrix(incMatrix),
    graphType(GraphType::INCIDENCE_MATRIX),
    adjList(nullptr) {
    parents = new int[vertices];
    mstArray = new Edge[vertices-1];
}

Prim::Prim(int vertices, int edges, Node **adjList):
    vertices(vertices),
    edges(edges),
    adjList(adjList),
    graphType(GraphType::ADJACENCY_LIST),
    incMatrix(nullptr) {
    parents = new int[vertices];
    mstArray = new Edge[vertices-1];
}

Prim::~Prim() {
    delete[] parents;
}


void Prim::start() {
    MinHeap minHeap = MinHeap(vertices);
    minHeap.buildHeap();
    for (int i = 0; i < vertices; i++) {
        parents[i] = -1;    //No parent
    }

    if (graphType == GraphType::ADJACENCY_LIST) {
            adjListVersion(minHeap);
    }

    //TEMP PRINT
    for(int i =0; i<vertices-1;i++){
        std::cout<<mstArray[i].from<<" -> "<<mstArray[i].to<<" : "<<mstArray[i].weight<<std::endl;
    }
}

void Prim::adjListVersion(MinHeap& minHeap) {
    int mstEdges = 0;
    while (!minHeap.isEmpty()) {    //while heap is not empty
        int u = minHeap.extractMin();   //get vertex with the lowest weight to get to

        if (parents[u] != -1) {
            // Add edge to MST
            mstArray[mstEdges].from = parents[u];
            mstArray[mstEdges].to = u;
            mstArray[mstEdges].weight = minHeap.getKey(u);
            mstEdges++;
        }

        Node* v = adjList[u];
        while (v != nullptr) {
            if (minHeap.isInHeap(v->vertex) && v->weight < minHeap.getKey(v->vertex)) { //if vertex is not chosen and weight is lower than current one
                parents[v->vertex] = u;
                minHeap.setKey(v->vertex, v->weight);
            }
            v = v->nextVertex;
        }

    }
}
