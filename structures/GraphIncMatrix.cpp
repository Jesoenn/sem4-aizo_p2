//
// Created by jakub on 2025-05-13.
//

#include "GraphIncMatrix.h"
#include <iostream>
GraphIncMatrix::GraphIncMatrix(int edges, int vertices, GraphDirection graphDirection):
        edges(edges),
        vertices(vertices),
        graphDirection(graphDirection){
    lastEdge = 0;
    incMatrix = nullptr;
    initialize();
}

GraphIncMatrix::~GraphIncMatrix() {
    std::cout<<"Matrix destructor initiated..."<<std::endl;
    for(int i = 0; i<vertices; i++){   //rows
        delete[] incMatrix[i];
    }
    delete[] incMatrix;
    incMatrix = nullptr;
    std::cout<<"Matrix deleted"<<std::endl;
}

void GraphIncMatrix::initialize() {
    incMatrix = new int*[vertices];         //rows
    for(int i = 0; i<vertices; i++){
        incMatrix[i] = new int[edges];
        for (int j = 0; j < edges; j++){    //columns
            incMatrix[i][j] = 0;
        }
    }
}

void GraphIncMatrix::addEdge(int vFrom, int vTo, int weight) {
    if (lastEdge == edges){
        throw std::out_of_range("Edge number is already reached");
    } else if (vFrom < 0 || vFrom >= vertices || vTo < 0 || vTo >= vertices) {
        throw std::invalid_argument("Vertex index out of bounds");
    }

    if(graphDirection == GraphDirection::DIRECTED){
        incMatrix[vFrom][lastEdge] = -weight;
    } else{
        incMatrix[vFrom][lastEdge] = weight;
    }
    incMatrix[vTo][lastEdge] = weight;
    lastEdge++;
}

void GraphIncMatrix::print() {
    for(int i = 0; i<vertices; i++){
        for(int j = 0; j<edges; j++){
            std::cout<<incMatrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

Edge* GraphIncMatrix::getEdgeArray() {
    Edge* edgeArray = new Edge[edges];
    for(int j = 0; j<edges; j++){       //column
        int foundV = 0;
        for(int i=0; i<vertices; i++){  //row
            // save vertices in edge
            if(incMatrix[i][j]!=0){
                if(foundV == 0){
                    edgeArray[j].from = i;
                    edgeArray[j].weight = incMatrix[i][j];  //undirected graph so weight is always positive
                    foundV++;
                } else {
                    edgeArray[j].to = i;
                    break;
                }
            }
        }
    }
    return edgeArray;
}

