//
// Created by jakub on 2025-05-12.
//

#ifndef PROJEKT2_AIZO_KRUSKAL_H
#define PROJEKT2_AIZO_KRUSKAL_H


#include "../structures/Edge.h"

class Kruskal {
public:
    Kruskal(int vertices, int edges, Edge* edgeArray);
    ~Kruskal();
    void start();
    void print() const;
    [[nodiscard]] Edge* getAnswerEdges() const;             //returns MST edges
    [[nodiscard]] int getAnswerSize() const;                //returns MST size
    bool verifyMST();

private:
    int vertices, edges;
    int* parents;                       //index is vertex, key is parent of each vertex
    int* ranks;                         //index is vertex, key is rank value
    Edge* edgeArray;
    Edge* mstArray;

    void makeSet(int v) const;              //set parents for each vertex
    int findSet(int v);                     //find root of given vertex
    void unionSets(int v1, int v2);         //combine sets

    void sortEdges() const;                 //from lowest to highest weight
};

#endif //PROJEKT2_AIZO_KRUSKAL_H
