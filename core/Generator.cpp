//
// Created by jakub on 21.05.2025.
//

#include "Generator.h"
#include <iostream>
#include <random>

Generator::Generator(int vertices, int density, GraphDirection graphDirection):
    vertices(vertices),
    graphDirection(graphDirection),
    currentEdge(0){
    //Density is percentage (1,40,100, etc.)
    if (graphDirection == GraphDirection::UNDIRECTED) {
        //max edges without cycles * density
        edges = static_cast<int>(vertices*(vertices-1)/2.0*(density/100.0));
    } else {
        edges = static_cast<int>(vertices*(vertices-1)*(density/100.0));
    }

    if (density>100 || edges<vertices) {
        throw std::invalid_argument("Wrong density");
    }

    edgeArray = new Edge[edges];

    adjMatrix = new bool*[vertices];
    for (int i = 0; i < vertices; ++i) {
        adjMatrix[i] = new bool[vertices];
        for (int j=0 ; j<vertices; ++j) {
            adjMatrix[i][j] = false;
        }
    }
}

Generator::~Generator() {
    for (int i = 0; i < vertices; ++i) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
    std::cout<<"Generator -> bool adj matrix deleted"<<std::endl;
}

void Generator::start() {
    generateConnectedGraph();
    generateEdges();

    // std::cout<<"\n\n\n\n";
    // std::cout<<"EDGES: "<<edges<<std::endl<<std::endl;
    // for (int i =0; i<currentEdge; i++) {
    //     std::cout<<edgeArray[i].from <<" -> "<<edgeArray[i].to<<" | "<<edgeArray[i].weight<<std::endl;
    // }
}

//generate Hamilton cycle
void Generator::generateConnectedGraph() {
    int* edgesPlacement = new int[vertices];
    int* keys = new int[vertices];      //each element i vertex number
    int unvisited = vertices;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distWeight(1, 100);

    for (int i =0 ;i<vertices;i++) {    //fill arrays
        keys[i] = i;
        edgesPlacement[i] = -1;
    }

    //generate edges
    for (int i =0; i<vertices; i++) {
        //generate unvisited vertex
        std::uniform_int_distribution<int> distVertex(0, unvisited-1);
        int endVertex = distVertex(gen);
        edgesPlacement[i] = keys[endVertex];
        std::swap(keys[endVertex], keys[unvisited-1]);
        unvisited--;
    }


    // Add edge
    edgeArray[0].to = edgesPlacement[0];
    edgeArray[0].from = edgesPlacement[vertices-1];
    edgeArray[0].weight = distWeight(gen);
    currentEdge++;

    adjMatrix[edgeArray[0].from][edgeArray[0].to] = true;
    if (graphDirection == GraphDirection::UNDIRECTED) {
        adjMatrix[edgeArray[0].to][edgeArray[0].from] = true;
    }

    //add edges to edge array and bool adj matrix
    for (int i =1; i<vertices; i++) {
        edgeArray[i].from = edgesPlacement[i-1];
        edgeArray[i].to = edgesPlacement[i];
        edgeArray[i].weight = distWeight(gen);
        currentEdge++;

        adjMatrix[edgeArray[i].from][edgeArray[i].to] = true;
        if (graphDirection == GraphDirection::UNDIRECTED) {
            adjMatrix[edgeArray[i].to][edgeArray[i].from] = true;
        }
    }

    delete[] edgesPlacement;
    delete[] keys;
}

void Generator::generateEdges() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distWeight(1, 100);
    std::uniform_int_distribution<int> distVertex(0, vertices-1);
    //for directed and undirected
    while (currentEdge<edges) {
        int startVertex = distVertex(gen);
        int endVertex = distVertex(gen);

        // Check if cycle
        if (startVertex == endVertex) {
            continue;
        }

        // Check if edge exists in DIRECTED, in UNDIRECTED index positioning doesn't matter
        if (adjMatrix[startVertex][endVertex] == true) {
            continue;
        }

        // Add edge
        edgeArray[currentEdge].from = startVertex;
        edgeArray[currentEdge].to = endVertex;
        edgeArray[currentEdge].weight = distWeight(gen);
        currentEdge++;

        adjMatrix[startVertex][endVertex] = true;
        if (graphDirection == GraphDirection::UNDIRECTED) {
            adjMatrix[endVertex][startVertex] = true;
        }
    }
}
