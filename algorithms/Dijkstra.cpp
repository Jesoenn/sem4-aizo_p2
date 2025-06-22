//
// Created by jakub on 2025-05-26.
//

#include "Dijkstra.h"
#include "../structures/MinHeap.h"
#include <limits>
#include <iostream>

Dijkstra::Dijkstra(int vertices, int edges, int** incMatrix, int source):
    graphType(GraphType::INCIDENCE_MATRIX),
    vertices(vertices),
    edges(edges),
    source(source),
    incMatrix(incMatrix){
    parent = new int[vertices];
    weights = new int[vertices];
    adjList = nullptr;
}

Dijkstra::Dijkstra(int vertices, int edges, Node** adjList, int source):
    graphType(GraphType::ADJACENCY_LIST),
    vertices(vertices),
    edges(edges),
    source(source),
    adjList(adjList){
    parent = new int[vertices];
    weights = new int[vertices];
    incMatrix = nullptr;
}

Dijkstra::~Dijkstra(){
    delete[] parent;
    delete[] weights;
}

void Dijkstra::start() const {
    initializeSingleSource();
    if(graphType == GraphType::ADJACENCY_LIST){
        adjListVersion();
    } else {
        incMatrixVersion();
    }
}

void Dijkstra::initializeSingleSource() const {
    for(int i = 0; i<vertices; i++){
        parent[i] = -1;
        weights[i] = std::numeric_limits<int>::max();   //INF
    }

    //Source has no weight and parent
    parent[source] = source;
    weights[source] = 0;
}

void Dijkstra::adjListVersion() const {
    MinHeap minHeap = MinHeap(vertices);
    minHeap.buildHeap(source);              //Build heap with source key as 0

    //Progress bar
    int visitedCount = 0;
    int interval = vertices/20;
    int progress = 5;               // every 5%

    // For every vertex in heap
    while(!minHeap.isEmpty()){
        int u = minHeap.extractMin();   //extract vertex with the lowest path weight

        visitedCount++;
        if (visitedCount!=0 && vertices>=20 && visitedCount%interval == 0 && progress<=100) {
            std::cout<<"Dijkstra progress: "<<progress<<"%"<<std::endl;
            progress+=5;
        }

        //For each adjacent vertex to u
        Node* currentV = adjList[u];
        while(currentV != nullptr){
            //relax edges
            if(relax(u, currentV->vertex, currentV->weight)){
                minHeap.setKey(currentV->vertex, weights[currentV->vertex]);
            }
            currentV = currentV->nextVertex;
        }
    }
}

void Dijkstra::incMatrixVersion() const {
    MinHeap minHeap = MinHeap(vertices);
    minHeap.buildHeap(source);

    //Progress bar
    int visitedCount = 0;
    int interval = vertices/20;
    int progress = 5;               // every 5%

    // For every vertex in heap
    while(!minHeap.isEmpty()){
        int u = minHeap.extractMin();   //extract vertex with the lowest path weight

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
                        //relax edge
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

bool Dijkstra::relax(int u, int v, int w) const {
    //If cost to get to parent is not infinite and new weights make path cost less, then switch parents
    if(weights[u] != std::numeric_limits<int>::max() && weights[v] > weights[u]+w){
        weights[v] = weights[u]+w;
        parent[v] = u;
        return true;
    }
    return false;
}

void Dijkstra::print() const {
    for (int i = 0; i < vertices; i++) {
        std::cout<<"Vertex: "<<i<<"\tWeight: "<<weights[i]<<"\tParent: "<<parent[i]<<std::endl;
    }
}

Edge * Dijkstra::getPath(int startV, int endV, bool print) const {
    int currentV = endV;                                            //start from last
    int pathLength = getPathLength(startV, endV);
    Edge* pathArray = new Edge[pathLength];

    if (print) {
        std::cout<<"\n\nShortest path (read from bottom):\n";
    }

    for (int i = pathLength-1; i >= 0; i--) {                       //from last array element to first
        int weight = weights[currentV]-weights[parent[currentV]];   //Edge weight
        pathArray[i].from = parent[currentV];
        pathArray[i].to = currentV;
        pathArray[i].weight = weight;
        currentV=parent[currentV];                                  //Move back from end vertex to start
        if (print) {
            std::cout<<pathArray[i].from<<" ->\t"<<pathArray[i].to<<" ["<<pathArray[i].weight<<"]"<<std::endl;
        }
    }
    if (print) {
        std::cout<<"Total cost: "<<weights[endV]-weights[startV]<<std::endl;
    }
    return pathArray;
}

int Dijkstra::getPathLength(int startV, int endV) const {
    int currentV = endV;
    int pathLength = 0;

    //Calculate path length for path array elements
    //Loop from end vertex until starting vertex is reached
    while (currentV != startV && currentV >= 0 && currentV < vertices) {
        currentV = parent[currentV];
        pathLength++;
    }

    //At the end of the loop currentV should be startV. If it's not, then end vertex is not reachable
    if (currentV != startV) {
        std::string errorMsg = "Vertex "+std::to_string(endV)+" is not reachable from vertex "+std::to_string(startV);
        throw std::invalid_argument(errorMsg);
    }

    return pathLength;
}
