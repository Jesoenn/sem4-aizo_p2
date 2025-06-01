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
// GraphAdjList::~GraphAdjList() {
//     std::cout<<"Adjacency list destructor initiated..."<<std::endl;
//     for(int i = 0; i<vertices; i++){    //for each vertex
//         Node* temp = adjList[i];        //first neighbour
//         while(temp != nullptr){         //delete each neighbour starting from first
//             Node* next = temp->nextVertex;
//             delete temp;
//             temp = next;
//         }
//     }
//     delete[] adjList;                   //delete array (vertices)
//     adjList = nullptr;
//     std::cout<<"Adjacency list deleted"<<std::endl;
// }

void GraphAdjList::initialize() {
    adjList = new Node*[vertices];      //create array, each index is vertex
    for (int i=0; i<vertices; i++) {    //set pointers to nullptr (for value checking purposes)
        adjList[i] = nullptr;
    }
}

void GraphAdjList::addEdge(int vFrom, int vTo, int weight) {
    if (vFrom < 0 || vFrom >= vertices || vTo < 0 || vTo >= vertices) {
        throw std::invalid_argument("Vertex index out of bounds");
    }

    Node* newNode = new Node(vTo, weight);
    newNode->nextVertex = adjList[vFrom];   //new neighbour is put as first in adjList
    adjList[vFrom] = newNode;

    if(graphDirection == GraphDirection::UNDIRECTED){ //if undirected edge goes both ways
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

Edge* GraphAdjList::getEdgeArray() {
    Edge* edgeArray = new Edge[edges];
    int edgeIndex = 0;

    //For each vertex find its neighbours and add to edge array
    for (int i=0; i < vertices; i++) {
        Node* temp = adjList[i];
        while(temp != nullptr) {
            //This will work only on undirected graph
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

Node ** GraphAdjList::getAdjList() {
    return adjList;
}
