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

// GraphIncMatrix::~GraphIncMatrix() {
//     std::cout<<"Matrix destructor initiated..."<<std::endl;
//     for(int i = 0; i<vertices; i++){    //For each row
//         delete[] incMatrix[i];          //delete its column
//     }
//     delete[] incMatrix;                 //delete all rows
//     incMatrix = nullptr;
//     std::cout<<"Matrix deleted"<<std::endl;
// }

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
    std::cout<<"\n\nINCIDENCE MATRIX GRAPH REPRESENTATION\n";
    for(int i = 0; i<vertices; i++){
        for(int j = 0; j<edges; j++){
            std::cout<<incMatrix[i][j]<<"\t";
        }
        std::cout<<std::endl;
    }
    std::cout<<"\n\n";
}

//This works only on Kruskal/Prim -> elements are always >0 row 71
Edge* GraphIncMatrix::getEdgeArray() {
    Edge* edgeArray = new Edge[edges];
    for(int j = 0; j<edges; j++){       //column
        int foundV = 0;                 //which vertex is found
        for(int i=0; i<vertices; i++){  //row
            // save vertices in edge
            if(incMatrix[i][j]!=0){

                //This "if" can be changed, so it works on directed graphs
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

int** GraphIncMatrix::getIncMatrix(){
    return incMatrix;
}

