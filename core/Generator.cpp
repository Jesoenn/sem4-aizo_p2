//
// Created by jakub on 21.05.2025.
//

#include "Generator.h"
#include <iostream>
#include <random>

Generator::Generator(int vertices, int density, GraphDirection graphDirection):
    vertices(vertices),
    currentEdge(0),
    graphDirection(graphDirection){

    //Calculate edges number based on density
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
    generateConnectedGraph();   //Firstly generate connected graph
    generateEdges();            //Then keep generating based on density (number of edges)
}

Edge * Generator::getEdges() const {
    return edgeArray;
}

int Generator::getEdgeCount() const {
    return edges;
}

void Generator::generateConnectedGraph() {
    std::vector<int> visited;
    std::vector<int> available;

    visited.push_back(0);             //Start from vertex 0
    for(int i = 1; i<vertices; i++){    //All vertices from 1 are available
        available.push_back(i);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distWeight(1, 1000000);  //Generated weight from 1 to 1 000 000

    //Until every vertex is visited
    while(visited.size()<vertices){
        std::uniform_int_distribution<int> distStart(0, static_cast<int>(visited.size()-1));
        std::uniform_int_distribution<int> distEnd(0, static_cast<int>(available.size()-1));

        int startIndex = distStart(gen);
        int endIndex = distEnd(gen);
        int startVertex = visited.at(startIndex);
        int endVertex = available.at(endIndex);

        visited.push_back(endVertex);   //End of the edge
        available.erase(available.begin()+endIndex);    //Remove vertex from available

        // Add edge
        edgeArray[currentEdge].to = endVertex;
        edgeArray[currentEdge].from = startVertex;
        edgeArray[currentEdge].weight = distWeight(gen);
        currentEdge++;

        adjMatrix[startVertex][endVertex] = true;               //Edge from startVertex -> endVertex
        if (graphDirection == GraphDirection::UNDIRECTED) {
            adjMatrix[endVertex][startVertex] = true;           //Edge from endVertex -> startEdge if graph is undirected
        }
    }
}

void Generator::generateEdges() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distWeight(1, 1000000);  //Generated weight from 1 to 1 000 000
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

        adjMatrix[startVertex][endVertex] = true;               //Edge from startVertex -> endVertex
        if (graphDirection == GraphDirection::UNDIRECTED) {
            adjMatrix[endVertex][startVertex] = true;           //Edge from endVertex -> startEdge if graph is undirected
        }
    }
}
