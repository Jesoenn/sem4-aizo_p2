//
// Created by jakub on 2025-05-12.
//

#include <iostream>
#include "Graph.h"

Graph::Graph(int edges, int vertices, GraphType graphType, GraphDirection graphDirection):
    edges(edges),
    vertices(vertices),
    graphType(graphType),
    graphDirection(graphDirection){
    lastEdge = 0;
    incMatrix = nullptr;
    adjList = nullptr;
    if(graphType == GraphType::INCIDENCE_MATRIX){
        initializeMatrix();
    } else if(graphType == GraphType::ADJACENCY_LIST){
        initializeAdjList();
    }
}

Graph::~Graph() {
    std::cout<<"Destructor initiated..."<<std::endl;
    if(graphType == GraphType::INCIDENCE_MATRIX){
        for(int i = 0; i<vertices; i++){   //rows
            delete[] incMatrix[i];
        }
        delete[] incMatrix;
        incMatrix = nullptr;
        std::cout<<"Matrix deleted"<<std::endl;
    } else if(graphType == GraphType::ADJACENCY_LIST){
        for(int i = 0; i<vertices; i++){   //rows
            //zapisac nastepnika
            //usunac obecnego
        }
        delete[] adjList;
        adjList = nullptr;
        std::cout<<"Adjacency list deleted"<<std::endl;
    }
}

void Graph::initializeMatrix() {
    incMatrix = new int*[vertices];         //rows
    for(int i = 0; i<vertices; i++){
        incMatrix[i] = new int[edges];
        for (int j = 0; j < edges; j++){    //columns
            incMatrix[i][j] = 0;
        }
    }
}

void Graph::initializeAdjList() {
    adjList = new Node*[vertices];
    for (int i=0; i<vertices; i++) {
        adjList[i] = nullptr;
    }
}

void Graph::addEdge(int vFrom, int vTo, int weight) {
    if(graphType == GraphType::INCIDENCE_MATRIX){
        addEdgeMatrix(vFrom,vTo,weight);
    } else if (graphType == GraphType::ADJACENCY_LIST){
        addEdgeAdjList(vFrom,vTo, weight);
    }
}

void Graph::addEdgeMatrix(int vFrom, int vTo, int weight) {
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

void Graph::addEdgeAdjList(int vFrom, int vTo, int weight) {
    if (vFrom < 0 || vFrom >= vertices || vTo < 0 || vTo >= vertices) {
        throw std::invalid_argument("Vertex index out of bounds");
    }

    Node* newNode = new Node(vTo, weight);
    newNode->nextVertex = adjList[vFrom];
    adjList[vFrom] = newNode;

    if(graphDirection == GraphDirection::UNDIRECTED){
        newNode = new Node(vFrom, weight);
        newNode->nextVertex = adjList[vTo];
        adjList[vTo] = newNode;
    }

}

void Graph::printGraph() {
    if(graphType == GraphType::INCIDENCE_MATRIX){
        printMatrix();
    } else if(graphType == GraphType::ADJACENCY_LIST){
        printList();
    }
}

void Graph::printMatrix() {
    for(int i = 0; i<vertices; i++){
        for(int j = 0; j<edges; j++){
            std::cout<<incMatrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void Graph::printList() {
    for(int i=0; i<vertices; i++){
        std::cout<<i<<": ";
        Node* temp = adjList[i];
        while(temp != nullptr){
            std::cout<<temp->vertex<<" ["<<temp->weight<<"]";
            temp = temp->nextVertex;
            if(temp != nullptr){
                std::cout<<" -> ";
            }
        }
        std::cout<<std::endl;
    }
}