//
// Created by jakub on 2025-05-26.
//

#include "Dijkstra.h"
#include "../structures/MinHeap.h"
#include <limits>
#include <iostream>

Dijkstra::Dijkstra(int vertices, int edges, int** incMatrix):
    vertices(vertices),
    edges(edges),
    incMatrix(incMatrix),
    graphType(GraphType::INCIDENCE_MATRIX){
    parent = new int[vertices];
    weights = new int[vertices];
    adjList = nullptr;
}

Dijkstra::Dijkstra(int vertices, int edges, Node** adjList):
    vertices(vertices),
    edges(edges),
    adjList(adjList),
    graphType(GraphType::ADJACENCY_LIST){
    parent = new int[vertices];
    weights = new int[vertices];
    incMatrix = nullptr;
}

Dijkstra::~Dijkstra(){
    delete[] parent;
    delete[] weights;
}

void Dijkstra::start(){
    initializeSingleSource();
    if(graphType == GraphType::ADJACENCY_LIST){
        adjListVersion();
    } else {
        incMatrixVersion();
    }
}

void Dijkstra::initializeSingleSource() {
    parent[0] = 0;
    weights[0] = 0;

    for(int i = 1; i<vertices; i++){
        parent[i] = -1;
        weights[i] = std::numeric_limits<int>::max();   //INF
    }
}

void Dijkstra::adjListVersion() {
    MinHeap minHeap = MinHeap(vertices);
    minHeap.buildHeap();

    //Progress bar
    int visitedCount = 0;
    int interval = vertices/20;
    int progress = 5;               // every 5%

    while(!minHeap.isEmpty()){
        int u = minHeap.extractMin();

        visitedCount++;
        if (visitedCount!=0 && vertices>=20 && visitedCount%interval == 0 && progress<=100) {
            std::cout<<"Dijkstra progress: "<<progress<<"%"<<std::endl;
            progress+=5;
        }

        //For each adjacent vertex
        Node* currentV = adjList[u];
        while(currentV != nullptr){
            if(relax(u, currentV->vertex, currentV->weight)){
                minHeap.setKey(currentV->vertex, weights[currentV->vertex]);
            }
            currentV = currentV->nextVertex;
        }
    }
}

void Dijkstra::incMatrixVersion() {
    MinHeap minHeap = MinHeap(vertices);
    minHeap.buildHeap();

    //Progress bar
    int visitedCount = 0;
    int interval = vertices/20;
    int progress = 5;               // every 5%

    while(!minHeap.isEmpty()){
        int u = minHeap.extractMin();

        visitedCount++;
        if (visitedCount!=0 && vertices>=20 && visitedCount%interval == 0 && progress<=100) {
            std::cout<<"Dijkstra progress: "<<progress<<"%"<<std::endl;
            progress+=5;
        }

        //For each adjacent vertex
        for(int currentEdge = 0; currentEdge<edges; currentEdge++){
            //if u vertex is starting vertex
            if(incMatrix[u][currentEdge]<0){
                //Search for ending vertex
                for(int vertex = 0; vertex< vertices; vertex++){
                    if(incMatrix[vertex][currentEdge] > 0){
                        if(relax(u, vertex, incMatrix[vertex][currentEdge])){
                            minHeap.setKey(vertex,weights[vertex]);
                        }
                        break;
                    }
                }
            }
        }
    }
}

bool Dijkstra::relax(int u, int v, int w) {
    if(weights[v] > weights[u]+w){
        weights[v] = weights[u]+w;
        parent[v] = u;
        return true;
    }
    return false;
}

void Dijkstra::print() {
    for (int i = 0; i < vertices; i++) {
        std::cout<<"Vertex: "<<i<<"\tWeight: "<<weights[i]<<"\tParent: "<<parent[i]<<std::endl;
    }
}

Edge * Dijkstra::getPath(int startV, int endV, bool print) {
    int currentV = endV;                                            //start from last
    int pathLength = getPathLength(startV, endV);
    Edge* pathArray = new Edge[pathLength];

    if (print) {
        std::cout<<"\n\nShortest path (read from bottom):\n";
    }

    for (int i = pathLength-1; i >= 0; i--) {                       //from last array element to first
        int weight = weights[currentV]-weights[parent[currentV]];
        pathArray[i].from = parent[currentV];
        pathArray[i].to = currentV;
        pathArray[i].weight = weight;
        currentV=parent[currentV];
        if (print) {
            std::cout<<pathArray[i].from<<" ->\t"<<pathArray[i].to<<" ["<<pathArray[i].weight<<"]"<<std::endl;
        }
    }
    if (print) {
        std::cout<<"Total cost: "<<weights[endV]-weights[startV]<<std::endl;
    }
    return pathArray;
}

int Dijkstra::getPathLength(int startV, int endV) {
    int currentV = endV;
    int pathLength = 0;

    //Calculate path length for path array elements
    while (currentV != startV && currentV >= 0 && currentV < vertices) {
        currentV = parent[currentV];
        pathLength++;
    }

    return pathLength;
}


