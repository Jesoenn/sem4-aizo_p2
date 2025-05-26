//
// Created by jakub on 15.05.2025.
//

#include "Prim.h"

Prim::Prim(int vertices, int edges, int **incMatrix):
    vertices(vertices),
    edges(edges),
    incMatrix(incMatrix),
    graphType(GraphType::INCIDENCE_MATRIX),
    adjList(nullptr),
    mstEdges(0){
    parents = new int[vertices];
    mstArray = new Edge[vertices-1];
}

Prim::Prim(int vertices, int edges, Node **adjList):
    vertices(vertices),
    edges(edges),
    adjList(adjList),
    graphType(GraphType::ADJACENCY_LIST),
    incMatrix(nullptr),
    mstEdges(0){
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
    } else if (graphType == GraphType::INCIDENCE_MATRIX) {
        incMatrixVersion(minHeap);
    }
}

void Prim::adjListVersion(MinHeap& minHeap) {
    while (!minHeap.isEmpty()) {    //while heap is not empty
        int u = minHeap.extractMin();   //visit vertex with the lowest edge weight
        addToMST(u, minHeap.getKey(u)); //add edge to MST

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

void Prim::incMatrixVersion(MinHeap &minHeap) {
    while(!minHeap.isEmpty()){
        int u = minHeap.extractMin();   //visit vertex with the lowest edge weight
        addToMST(u, minHeap.getKey(u)); //add edge to MST

        for(int i=0; i< edges; i++){    //iterate through columns (edges)
            if(incMatrix[u][i] != 0){   //if vertex u has number (weight) there is an edge
                for(int j=0; j<vertices; j++){  //iterate through vertices to find second vertex
                    if(j==u){                   //if row = u, skip
                        continue;
                    }else if (incMatrix[j][i] != 0){
                        int v = j;
                        int weight = (incMatrix[j][i]>0) ? incMatrix[j][i] : -incMatrix[j][i];  //weight >0
                        if(minHeap.isInHeap(v) && weight<minHeap.getKey(v)){
                            parents[v] = u;
                            minHeap.setKey(v,weight);
                        }
                    }
                }
            }
        }
    }
}

void Prim::addToMST(int u, int weight) {
    if (parents[u] != -1) {
        // Add edge to MST
        mstArray[mstEdges].from = parents[u];
        mstArray[mstEdges].to = u;
        mstArray[mstEdges].weight = weight;
        mstEdges++;
    }
}

void Prim::print() {
    int cost = 0;
    std::cout<<"\n\nKruskal MST:"<<std::endl;
    for(int i =0; i<vertices-1;i++){
        cost += mstArray[i].weight;
        std::cout<<mstArray[i].from<<" -> "<<mstArray[i].to<<" : "<<mstArray[i].weight<<std::endl;
    }
    std::cout<<"Total cost: "<<cost<<std::endl;
}