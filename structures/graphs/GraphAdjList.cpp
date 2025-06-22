//
// Created by jakub on 2025-05-13.
//

#include <iostream>
#include "GraphAdjList.h"

GraphAdjList::GraphAdjList(int edges, int vertices, GraphDirection graphDirection):
    graphDirection(graphDirection),
    edges(edges),
    vertices(vertices) {
    adjList = nullptr;
    initialize();
}

void GraphAdjList::initialize() {
    adjList = new Node*[vertices];      //create array, each index is vertex
    for (int i=0; i<vertices; i++) {    //set pointers to nullptr (for value checking purposes)
        adjList[i] = nullptr;
    }
}

void GraphAdjList::addEdge(int vFrom, int vTo, int weight) const {
    if (vFrom < 0 || vFrom >= vertices || vTo < 0 || vTo >= vertices) {
        throw std::invalid_argument("Vertex index out of bounds");
    }

    Node* newNode = new Node(vTo, weight);    //End of the edge
    newNode->nextVertex = adjList[vFrom];           //new neighbour is put as first in adjList, rest is pushed right
    adjList[vFrom] = newNode;                       //First neighbour

    if(graphDirection == GraphDirection::UNDIRECTED){ //if undirected edge goes both ways
        newNode = new Node(vFrom, weight);
        newNode->nextVertex = adjList[vTo];
        adjList[vTo] = newNode;
    }
}

void GraphAdjList::print() const {
    std::cout<<"\n\nADJACENCY LIST GRAPH REPRESENTATION\n";
    for(int i=0; i<vertices; i++){
        std::cout<<i<<": ";
        Node* temp = adjList[i];
        while(temp != nullptr){
            std::cout<<temp->vertex<<" ["<<temp->weight<<"]";
            temp = temp->nextVertex;
            if(temp != nullptr){
                std::cout<<" ->\t";
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<"\n\n";
}

//Returns edge array, works only for undirected graphs -> Kruskal alg
Edge* GraphAdjList::getEdgeArray() const {
    Edge* edgeArray = new Edge[edges];
    int edgeIndex = 0;

    //For each vertex find its neighbours and add to edge array
    for (int i=0; i < vertices; i++) {
        Node* temp = adjList[i];
        while(temp != nullptr) {
            //This works only on undirected graph
            //Connect lower vertex number to higher (removes duplicates)
            if (i<temp->vertex) {
                edgeArray[edgeIndex].from = i;
                edgeArray[edgeIndex].to = temp->vertex;
                edgeArray[edgeIndex].weight = temp->weight;
                edgeIndex++;
            }
            temp=temp->nextVertex;
        }
    }
    return edgeArray;
}

Node ** GraphAdjList::getAdjList() const {
    return adjList;
}
