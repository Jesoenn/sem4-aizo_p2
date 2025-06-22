//
// Created by jakub on 2025-05-12.
//

#include <iostream>
#include "Kruskal.h"
#include "HeapSort.h"

Kruskal::Kruskal(int vertices, int edges, Edge *edgeArray):
    vertices(vertices),
    edges(edges),
    edgeArray(edgeArray){
    mstArray = new Edge[vertices-1];
    parents = new int[vertices];
    ranks = new int[vertices];
}

void Kruskal::makeSet(int v) const {
    parents[v] = v;
    ranks[v] = 0;
}

int Kruskal::findSet(int v) {
    // Find set vertex ("root")
    if(v != parents[v]){
        parents[v] = findSet(parents[v]);
    }
    return parents[v];
}

void Kruskal::unionSets(int v1, int v2) {
    int root1 = findSet(v1);
    int root2 = findSet(v2);

    //attach set with smaller rank to set with larger rank
    if(ranks[root1]>ranks[root2]){
        parents[root2]=root1;       //new root of v2
    } else{
        parents[root1]=root2;       //new root of v1
        if(ranks[root1] == ranks[root2]){
            ranks[root2]++;         //increment rank of v2 set
        }
    }

}

void Kruskal::start() {
    //For each vertex create set
    for(int i=0; i<vertices; i++){
        makeSet(i);
    }

    //Sort edges from smallest to largest weight
    sortEdges();

    int mstEdgeNum = 0;                //How many MST edges
    int interval = (vertices-1)/20;    //Every interval (5%) print % of performed algorithm
    int progress = 5;

    //Edges are sorted in non-decreasing order
    for(int i=0; i<edges; i++){
        // MST is completed, end loop
        if (mstEdgeNum == vertices - 1) {
            break;
        }

        int v1 = edgeArray[i].from;
        int v2 = edgeArray[i].to;

        if(findSet(v1)!= findSet(v2)){     //if 2 different sets, combine them
            if (mstEdgeNum!=0 && vertices>=20 && mstEdgeNum%interval == 0 && progress <= 100) {
                std::cout<<"Kruskal progress: "<<progress<<"%"<<std::endl;
                progress+=5;
            }

            //copy object/add edge to MST
            mstArray[mstEdgeNum]=edgeArray[i];
            mstEdgeNum++;

            unionSets(v1,v2);   //Combine sets
        }

    }
}

Kruskal::~Kruskal() {
    std::cout<<"Kruskal destructor initiated...\n";
    delete[] ranks;
    std::cout<<"ranks deleted\n";
    delete[] parents;
    std::cout<<"parents deleted\n";
    delete[] edgeArray;
    std::cout<<"edge array deleted\n";
    delete[] mstArray;
}

//Sort edge array
void Kruskal::sortEdges() const {
    HeapSort heapSort(edgeArray,edges);
    heapSort.sort();
}

void Kruskal::print() const {
    int cost = 0;
    std::cout<<"\n\nKruskal MST:"<<std::endl;
    for(int i =0; i<vertices-1;i++){
        cost += mstArray[i].weight;
        std::cout<<mstArray[i].from<<" -> "<<mstArray[i].to<<" : "<<mstArray[i].weight<<std::endl;
    }
    std::cout<<"\nTotal cost: "<<cost<<std::endl;
}

Edge * Kruskal::getAnswerEdges() const {
    //Copy mst array because it will be deleted in destructor
    Edge* mstArrayCopy = new Edge[vertices-1];
    for(int i =0; i<vertices-1;i++){
        mstArrayCopy[i]=mstArray[i];
    }

    return mstArrayCopy;
}

int Kruskal::getAnswerSize() const {
    return vertices-1;
}

bool Kruskal::verifyMST() {
    int root = findSet(0);
    for (int i=1; i<vertices; i++) {
        if (findSet(i) != root) {
            return false;
        }
    }
    return true;
}
