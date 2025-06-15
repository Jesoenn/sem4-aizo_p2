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

void Kruskal::makeSet(int v) {
    parents[v] = v;
    ranks[v] = 0;
}

int Kruskal::findSet(int v) {
    if(v != parents[v]){
        parents[v] = findSet(parents[v]);
    }
    return parents[v];
}

void Kruskal::unionSets(int v1, int v2) {
    int root1 = findSet(v1);
    int root2 = findSet(v2);

    //attach shorter set to longer
    if(ranks[root1]>ranks[root2]){
        parents[root2]=root1;
    } else{
        parents[root1]=root2;
        if(ranks[root1] == ranks[root2]){
            ranks[root2]++;
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

    int mstEdgeNum = 0;
    int interval = (vertices-1)/20;    //every interval (5%) print % of performed algorithm
    int progress = 5;

    for(int i=0; i<edges; i++){
        // MST is completed
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

            mstArray[mstEdgeNum]=edgeArray[i];   //copy object/add edge to MST
            mstEdgeNum++;
            unionSets(v1,v2);
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

void Kruskal::sortEdges() {
    HeapSort heapSort(edgeArray,edges);
    heapSort.sort();
}

void Kruskal::print() {
    int cost = 0;
    std::cout<<"\n\nKruskal MST:"<<std::endl;
    for(int i =0; i<vertices-1;i++){
        cost += mstArray[i].weight;
        std::cout<<mstArray[i].from<<" -> "<<mstArray[i].to<<" : "<<mstArray[i].weight<<std::endl;
    }
    std::cout<<"\nTotal cost: "<<cost<<std::endl;
}

Edge * Kruskal::getAnswerEdges() {
    //Copy mst array because it will be deleted in destructor
    Edge* mstArrayCopy = new Edge[vertices-1];
    for(int i =0; i<vertices-1;i++){
        mstArrayCopy[i]=mstArray[i];
    }

    return mstArrayCopy;
}

int Kruskal::getAnswerSize() {
    return vertices-1;
}
