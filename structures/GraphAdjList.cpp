//
// Created by jakub on 2025-05-13.
//

#include <iostream>
#include "GraphAdjList.h"

GraphAdjList::GraphAdjList(int edges, int vertices, GraphDirection graphDirection):
    edges(edges),
    vertices(vertices),
    graphDirection(graphDirection) {
    adjList = nullptr;
    initialize();
}
GraphAdjList::~GraphAdjList() {
    std::cout<<"Adjacency list destructor initiated..."<<std::endl;
    for(int i = 0; i<vertices; i++){   //rows
        Node* temp = adjList[i];
        while(temp != nullptr){
            Node* next = temp->nextVertex;
            delete temp;
            temp = next;
        }
    }
    delete[] adjList;
    adjList = nullptr;
    std::cout<<"Adjacency list deleted"<<std::endl;
}

void GraphAdjList::initialize() {
    adjList = new Node*[vertices];
    for (int i=0; i<vertices; i++) {
        adjList[i] = nullptr;
    }
}

void GraphAdjList::addEdge(int vFrom, int vTo, int weight) {
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

void GraphAdjList::print() {
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
