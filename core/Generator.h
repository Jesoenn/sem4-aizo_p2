//
// Created by jakub on 21.05.2025.
//

#ifndef GENERATOR_H
#define GENERATOR_H
#include "../enums/GraphDirection.h"
#include "../structures/Edge.h"


class Generator {
public:
    Generator(int vertices, int density, GraphDirection graphDirection);    //Density is percentage (1,40,100, etc.)
    ~Generator();
    void start();
    [[nodiscard]] Edge* getEdges() const;   //Get generated array
    [[nodiscard]] int getEdgeCount() const; //Get number of generated edges

private:
    int vertices, edges, currentEdge;
    GraphDirection graphDirection;
    Edge* edgeArray;    //Generated array
    bool** adjMatrix;   //Adjacency matrix used to check if edge is already generated

    void generateConnectedGraph();
    void generateEdges();
};



#endif //GENERATOR_H
