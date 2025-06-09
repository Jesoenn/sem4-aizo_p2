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
    //Progress bar
    int interval = vertices/20;
    int progress = 5;               // every 5%

    bool cycleChanged;
    //vertices - 1 iterations of bellman ford
    for(int i=0; i<vertices-1; i++){
        //Progress bar
        if (i!=0 && vertices>=20 && i%interval == 0) {
            std::cout<<"BellmanFord progress: "<<progress<<"%"<<std::endl;
            progress+=5;
        }

        cycleChanged = false;
        for(int u=0; u<vertices; u++){  //for each vertex and its neighbours
            Node* currentVertex = adjList[u];
            while(currentVertex != nullptr){
                if (relax(u,currentVertex->vertex, currentVertex->weight)) {
                    cycleChanged = true;
                }
                currentVertex=currentVertex->nextVertex;
            }
        }
        if (!cycleChanged) {    //end algorithm if there is no change in weights
            break;
        }
    }
    std::cout<<"BellmanFord progress: 100%"<<std::endl;
}

void BellmanFord::incMatrixVersion() {
    //Progress bar
    int interval = vertices/20;
    int progress = 5;               // every 5%

    bool cycleChanged;
    for(int i=0; i<vertices-1; i++) {
        //Progress bar
        if (i!=0 && vertices>=20 && i%interval == 0) {
            std::cout<<"BellmanFord progress: "<<progress<<"%"<<std::endl;
            progress+=5;
        }

        cycleChanged = false;
        for(int edge=0; edge<edges; edge++) {
            int u=-1,v=-1,weight=0;

            //Find vertices and weight
            for (int vertex=0; vertex < vertices; vertex++) {
                if (incMatrix[vertex][edge] < 0) {
                    u = vertex;
                } else if (incMatrix[vertex][edge] > 0) {
                    v = vertex;
                    weight = incMatrix[vertex][edge];
                }
                if (v != -1 && u != -1) {
                    break;
                }
            }

            if (relax(u,v,weight)) {
                cycleChanged = true;
            }

        }
        if (!cycleChanged) {    //end algorithm if there is no change in weights
            break;
        }
    }
    std::cout<<"BellmanFord progress: 100%"<<std::endl;
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
    if(weights[u] != std::numeric_limits<int>::max() && weights[v] > weights[u]+w){
        weights[v] = weights[u]+w;
        parent[v] = u;
        return true;
    }
    return false;
}

void BellmanFord::print() {
    for (int i = 0; i < vertices; i++) {
        std::cout<<"Vertex: "<<i<<"\tWeight: "<<weights[i]<<"\tParent: "<<parent[i]<<std::endl;
    }
}
