//
// Created by jakub on 15.05.2025.
//

#include "Prim.h"
#include "iostream"

Prim::Prim(int vertices, int edges, int **incMatrix):
    graphType(GraphType::INCIDENCE_MATRIX),
    vertices(vertices),
    edges(edges),
    progress(5),
    adjList(nullptr),
    incMatrix(incMatrix),
    mstEdges(0){
    interval = (vertices - 1)/20;
    parents = new int[vertices];
    mstArray = new Edge[vertices-1];
}

Prim::Prim(int vertices, int edges, Node **adjList):
    graphType(GraphType::ADJACENCY_LIST),
    vertices(vertices),
    edges(edges),
    progress(5),
    adjList(adjList),
    incMatrix(nullptr),
    mstEdges(0){
    interval = (vertices - 1)/20;
    parents = new int[vertices];
    mstArray = new Edge[vertices-1];
}

Prim::~Prim() {
    delete[] parents;
    delete[] mstArray;
}


void Prim::start() {
    //build minimum heap
    MinHeap minHeap = MinHeap(vertices);
    minHeap.buildHeap(0);   //Build heap with vertex 0 key = 0

    //set parents of each vertex
    for (int i = 0; i < vertices; i++) {
        parents[i] = -1;    //No parent
    }

    if (graphType == GraphType::ADJACENCY_LIST) {
        adjListVersion(minHeap);
    } else if (graphType == GraphType::INCIDENCE_MATRIX) {
        incMatrixVersion(minHeap);
    }
}

void Prim::adjListVersion(MinHeap& minHeap) {
    while (!minHeap.isEmpty()) {    //for each vertex and while heap is not empty
        // MST is completed
        if (mstEdges == vertices - 1) {
            break;
        }

        int u = minHeap.extractMin();   //extract vertex with the current lowest edge weight
        addToMST(u, minHeap.getKey(u)); //add edge to MST

        Node* v = adjList[u];           //v is the first neighbour of vertex u
        //Find neighbour that is not in MST and has the lowest weight
        while (v != nullptr) {
            //if current vertex is in heap (not chosen) and its weight is smaller than the one in heap (which is infinite by default)
            if (minHeap.isInHeap(v->vertex) && v->weight < minHeap.getKey(v->vertex)) {
                parents[v->vertex] = u;                     //set u as parent of v
                minHeap.setKey(v->vertex, v->weight);     //update weight in heap
            }
            v = v->nextVertex;                              //v = next neighbour of u
        }

    }
}

void Prim::incMatrixVersion(MinHeap &minHeap) {
    while(!minHeap.isEmpty()){  //for each vertex and while heap is not empty
        // MST is completed
        if (mstEdges == vertices - 1) {
            break;
        }

        int u = minHeap.extractMin();   //visit vertex with the lowest edge weight
        addToMST(u, minHeap.getKey(u)); //add edge to MST

        for(int i=0; i< edges; i++){    //iterate through columns (edges) to find edge which contains vertex u
            if(incMatrix[u][i] != 0){   //if vertex u has number (weight) there is an edge
                for(int j=0; j<vertices; j++){  //iterate through rows (vertices) to find second vertex
                    if(j==u){                   //if row = u, skip
                        continue;
                    }else if (incMatrix[j][i] != 0){
                        int v = j;
                        int weight = std::abs(incMatrix[j][i]);
                        //if current vertex is in heap (not chosen) and its weight is smaller than the one in heap (which is infinite by default)
                        if(minHeap.isInHeap(v) && weight<minHeap.getKey(v)){
                            parents[v] = u;             //set u as parent of v
                            minHeap.setKey(v,weight);   //update weight in heap
                        }
                        break;
                    }
                }
            }
        }
    }
}

void Prim::addToMST(int u, int weight) {
    if (parents[u] != -1) {
        if (mstEdges!=0 && vertices>=20 && mstEdges%interval == 0 && progress <= 100) {
            std::cout<<"Prim progress: "<<progress<<"%"<<std::endl;
            progress+=5;
        }

        // Add edge to MST
        mstArray[mstEdges].from = parents[u];
        mstArray[mstEdges].to = u;
        mstArray[mstEdges].weight = weight;
        mstEdges++;
    }
}

void Prim::print() const {
    int cost = 0;
    std::cout<<"\n\nPrim MST:"<<std::endl;
    for(int i =0; i<vertices-1;i++){
        cost += mstArray[i].weight;
        std::cout<<mstArray[i].from<<" -> "<<mstArray[i].to<<" : "<<mstArray[i].weight<<std::endl;
    }
    std::cout<<"\nTotal cost: "<<cost<<std::endl;
}

Edge * Prim::getAnswerEdges() const {
    //Copy mst array because it will be deleted in destructor
    Edge* mstArrayCopy = new Edge[vertices-1];
    for(int i =0; i<vertices-1;i++){
        mstArrayCopy[i]=mstArray[i];
    }

    return mstArrayCopy;
}

int Prim::getAnswerSize() const {
    return vertices-1;
}

bool Prim::verifyMST() const {
    int countErr=0;
    for (int i=0; i<vertices; i++) {
        if (parents[i] == -1) {
            countErr++;
        }
    }
    if (countErr!=1) {
        return false;
    }
    return true;
}
