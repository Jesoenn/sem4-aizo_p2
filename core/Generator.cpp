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

    if (density>100 || edges<vertices-1) {
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

    std::cout<<"\n\n\n\n";
    std::cout<<"EDGES: "<<edges<<std::endl<<std::endl;
    for (int i =0; i<currentEdge; i++) {
        std::cout<<edgeArray[i].from <<" -> "<<edgeArray[i].to<<" | "<<edgeArray[i].weight<<std::endl;
    }
    std::cout<<"\n\n\n\n";
}

void Generator::generateConnectedGraph() {
    std::vector<int> visited;
    std::vector<int> available;

    visited.push_back(0);   //Start from vertex 0
    for(int i = 1; i<vertices; i++){    //All vertices from 1 are available
        available.push_back(i);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distWeight(1, 100);

    while(visited.size()<vertices){
        std::uniform_int_distribution<int> distStart(0, static_cast<int>(visited.size()-1));
        std::uniform_int_distribution<int> distEnd(0, static_cast<int>(available.size()-1));
        int startIndex = distStart(gen);
        int endIndex = distEnd(gen);

        int startVertex = visited.at(startIndex);
        int endVertex = available.at(endIndex);

        visited.push_back(endVertex);
        available.erase(available.begin()+endIndex);

        // Add edge
        edgeArray[currentEdge].to = endVertex;
        edgeArray[currentEdge].from = startVertex;
        edgeArray[currentEdge].weight = distWeight(gen);
        currentEdge++;

        adjMatrix[startVertex][endVertex] = true;
        if (graphDirection == GraphDirection::UNDIRECTED) {
            adjMatrix[endVertex][startVertex] = true;
        }
    }
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
        if (adjMatrix[startVertex][endVertex]) {
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
