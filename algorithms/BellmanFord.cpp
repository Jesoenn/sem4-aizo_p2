//
// Created by jakub on 2025-05-26.
//

#include "BellmanFord.h"
#include <limits>
#include <iostream>

BellmanFord::BellmanFord(int vertices, int edges, int **incMatrix, int source):
    graphType(GraphType::INCIDENCE_MATRIX),
    vertices(vertices),
    edges(edges),
    source(source),
    incMatrix(incMatrix){
    parent = new int[vertices];
    weights = new int[vertices];
    adjList = nullptr;
}

BellmanFord::BellmanFord(int vertices, int edges, Node **adjList, int source):
    graphType(GraphType::ADJACENCY_LIST),
    vertices(vertices),
    edges(edges),
    source(source),
    adjList(adjList){
    parent = new int[vertices];
    weights = new int[vertices];
    incMatrix = nullptr;
}

BellmanFord::~BellmanFord() {
    delete[] weights;
    delete[] parent;
}

void BellmanFord::start() const {
    initializeSingleSource();
    if(graphType == GraphType::ADJACENCY_LIST){
        adjListVersion();
    } else{
        incMatrixVersion();
    }
}

void BellmanFord::adjListVersion() const {
    //Progress bar
    int interval = vertices/100;
    int progress = 1;               // every 5%

    //vertices - 1 iterations of bellman ford
    for(int i=0; i<vertices-1; i++){
        //Progress bar
        std::cout<<"Iteration: "<<i<<std::endl;
        if (i!=0 && vertices>=100 && i%interval == 0) {
            std::cout<<"BellmanFord progress: "<<progress<<"%"<<std::endl;
            progress+=1;
        }

        bool cycleChanged = false;
        for(int u=0; u<vertices; u++){  //for each vertex and its neighbours
            Node* currentVertex = adjList[u];

            //for every neighbour of u
            while(currentVertex != nullptr){
                //relax edge
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

void BellmanFord::incMatrixVersion() const {
    //Progress bar
    int interval = vertices/100;
    int progress = 1;               // every 5%

    //vertices - 1 iterations of bellman ford
    for(int i=0; i<vertices-1; i++) {
        //Progress bar
        std::cout<<"Iteration: "<<i<<std::endl;
        if (i!=0 && vertices>=100 && i%interval == 0) {
            std::cout<<"BellmanFord progress: "<<progress<<"%"<<std::endl;
            progress+=1;
        }

        bool cycleChanged = false;
        for(int edge=0; edge<edges; edge++) {
            int u=-1,v=-1,weight=0;

            //Find vertices and weight of edge in iteration
            //Iterate through rows (vertices)
            for (int vertex=0; vertex < vertices; vertex++) {
                if (incMatrix[vertex][edge] < 0) {
                    u = vertex; //beginning of edge
                } else if (incMatrix[vertex][edge] > 0) {
                    v = vertex; //ending of edge
                    weight = incMatrix[vertex][edge];
                }

                //if edge is found end loop
                if (v != -1 && u != -1) {
                    break;
                }
            }

            //relax edge
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

void BellmanFord::initializeSingleSource() const {
    for(int i = 0; i<vertices; i++){
        parent[i] = -1;
        weights[i] = std::numeric_limits<int>::max();   //INF
    }

    //Source has no weight and parent
    parent[source] = source;
    weights[source] = 0;
}

bool BellmanFord::relax(int u, int v, int w) const {
    //If cost to get to parent is not infinite and new weights make path cost less, then switch parents
    if(weights[u] != std::numeric_limits<int>::max() && weights[v] > weights[u]+w){
        weights[v] = weights[u]+w;
        parent[v] = u;
        return true;
    }
    return false;
}

void BellmanFord::print() const {
    for (int i = 0; i < vertices; i++) {
        std::cout<<"Vertex: "<<i<<"\tWeight: "<<weights[i]<<"\tParent: "<<parent[i]<<std::endl;
    }
}

Edge * BellmanFord::getPath(int startV, int endV, bool print) const {
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

int BellmanFord::getPathLength(int startV, int endV) const {
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
