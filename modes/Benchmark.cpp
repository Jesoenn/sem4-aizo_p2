//
// Created by jakub on 30.05.2025.
//

#include "Benchmark.h"

#include <iostream>
#include <stdexcept>
#include <utility>

#include "../algorithms/BellmanFord.h"
#include "../algorithms/Dijkstra.h"
#include "../algorithms/Kruskal.h"
#include "../algorithms/Prim.h"
#include "../core/Generator.h"
#include "../structures/graphs/GraphAdjList.h"
#include "../structures/graphs/GraphIncMatrix.h"

Benchmark::Benchmark(int graph, int algorithm, int vertices, int density, std::string outputFile, int printGraph):
    vertices(vertices),
    edges(-1),
    density(density),
    outputFile(std::move(outputFile)),
    time(-1){

    switch (graph) {
        case 0: graphType = GraphType::INCIDENCE_MATRIX; break;
        case 1: graphType = GraphType::ADJACENCY_LIST; break;
        default: throw std::invalid_argument("ERROR: Wrong graph type.");
    }

    switch (algorithm) {
        case 0: this->algorithm = AlgorithmType::KRUSKAL; break;
        case 1: this->algorithm = AlgorithmType::PRIM; break;
        case 2: this->algorithm = AlgorithmType::DIJKSTRA; break;
        case 3: this->algorithm = AlgorithmType::BELLMAN_FORD; break;
        default: throw std::invalid_argument("ERROR: Wrong algorithm.");
    }

    switch (printGraph) {
        case 0: this->printGraph = false; break;
        case 1: this->printGraph = true; break;
        default: throw std::invalid_argument("ERROR: Printing value can be either 0 or 1.");
    }
}

void Benchmark::start() {
    FileManager fileManager("","",outputFile);  //used to save algorithm data

    GraphDirection graphDirection;
    if (algorithm == AlgorithmType::KRUSKAL || algorithm == AlgorithmType::PRIM) {      //MST problem
        graphDirection = GraphDirection::UNDIRECTED;
    } else {        //Shortest path problem
        graphDirection = GraphDirection::DIRECTED;
    }

    //Initialize algorithm details
    Edge* edgeArray = generateEdges(graphDirection);    //Generate edge array, that is used to create graphs
    int** incMatrix = nullptr;                          //Incidence matrix
    Node** adjList = nullptr;                           //Adjacency list

    if ( algorithm == AlgorithmType::KRUSKAL) {
        performKruskal(edgeArray);              // Kruskal needs Graph class to get edge array (other algorithms don't)
    } else {
        //Generate specific graph
        if (graphType == GraphType::INCIDENCE_MATRIX) {
            incMatrix = generateIncMatrix(edgeArray, graphDirection);
        } else {
            adjList = generateAdjList(edgeArray, graphDirection);
        }

        switch (algorithm) {
            case AlgorithmType::PRIM: performPrim(incMatrix, adjList); break;
            case AlgorithmType::DIJKSTRA: performDijkstra(incMatrix, adjList); break;
            case AlgorithmType::BELLMAN_FORD: performBellmanFord(incMatrix, adjList); break;
            default: throw std::invalid_argument("ERROR: Wrong algorithm.");
        }
    }

    fileManager.saveData(algorithm, graphType, vertices, density, time);    //save algorithm data to file
    deleteGraph(incMatrix, adjList);                                        //free allocated memory
}

Edge* Benchmark::generateEdges(GraphDirection graphDirection) {
    std::cout<<"Generating edges..."<<std::endl;
    Generator generator(vertices, density, graphDirection);
    generator.start();
    edges = generator.getEdgeCount();   //Edge number
    return generator.getEdges();
}

int ** Benchmark::generateIncMatrix(const Edge* edgeArray, GraphDirection graphDirection) const {
    GraphIncMatrix graphIncMatrix(edges, vertices, graphDirection);
    std::cout<<"Generating incidence matrix..."<<std::endl;

    //Add each edge to graph
    for (int i =0; i < edges; i++) {
        graphIncMatrix.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
    }
    delete[] edgeArray; //Free memory from generated edges

    if (printGraph) {
        graphIncMatrix.print();
    }

    return graphIncMatrix.getIncMatrix();
}

Node ** Benchmark::generateAdjList(const Edge* edgeArray, GraphDirection graphDirection) const {
    GraphAdjList graphAdjList(edges, vertices, graphDirection);
    std::cout<<"Generating adjacency list..."<<std::endl;

    //Add each edge to graph
    for (int i =0; i < edges; i++) {
        graphAdjList.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
    }
    delete[] edgeArray; //Free memory from generated edges

    if (printGraph) {
        graphAdjList.print();
    }

    return graphAdjList.getAdjList();
}

void Benchmark::performKruskal(const Edge *edgeArray) {
    if (graphType == GraphType::INCIDENCE_MATRIX) {
        //Create graph from generated edges
        GraphIncMatrix graphIncMatrix(edges, vertices, GraphDirection::UNDIRECTED);
        std::cout<<"Generating incidence matrix..."<<std::endl;

        //Add each edge to graph
        for (int i =0; i < edges; i++) {
            graphIncMatrix.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
        }
        delete[] edgeArray; //Free memory from generated edges

        if (printGraph) {
            graphIncMatrix.print();
        }

        //Perform algorithm
        timer.start();
        Kruskal kruskal(vertices,edges,graphIncMatrix.getEdgeArray());
        kruskal.start();
        timer.stop();
        //kruskal.print();
        time = timer.result();
    } else {
        //Create graph from generated edges
        GraphAdjList graphAdjList(edges, vertices, GraphDirection::UNDIRECTED);

        //Add each edge to graph
        std::cout<<"Generating adjacency list..."<<std::endl;
        for (int i =0; i < edges; i++) {
            graphAdjList.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
        }
        delete[] edgeArray; //Free memory from generated edges

        if (printGraph) {
            graphAdjList.print();
        }

        //Perform algorithm
        timer.start();
        Kruskal kruskal(vertices,edges,graphAdjList.getEdgeArray());
        kruskal.start();
        timer.stop();
        //kruskal.print();
        time = timer.result();
    }
}

void Benchmark::performPrim(int **incMatrix, Node **adjList) {
    // Incidence matrix version
    if (incMatrix != nullptr) {
        Prim prim(vertices,edges,incMatrix);
        timer.start();
        prim.start();
        timer.stop();
        //prim.print();
        time = timer.result();
    }
    // Adjacency list version
    else {
        Prim prim(vertices,edges,adjList);
        timer.start();
        prim.start();
        timer.stop();
        //prim.print();
        time = timer.result();
    }
}

void Benchmark::performDijkstra(int **incMatrix, Node **adjList) {
    // incidence matrix version
    if (incMatrix != nullptr) {
        Dijkstra dijkstra(vertices,edges,incMatrix, 0);
        timer.start();
        dijkstra.start();
        timer.stop();
        //dijkstra.print();
        time = timer.result();
    }
    // Adjacency list version
    else {
        Dijkstra dijkstra(vertices,edges,adjList, 0);
        timer.start();
        dijkstra.start();
        timer.stop();
        //dijkstra.print();
        time = timer.result();
    }
}

void Benchmark::performBellmanFord(int **incMatrix, Node **adjList) {
    // incidence matrix version
    if (incMatrix != nullptr) {
        BellmanFord bellmanFord(vertices, edges, incMatrix, 0);
        timer.start();
        bellmanFord.start();
        timer.stop();
        //bellmanFord.print();
        time = timer.result();
    }
    // Adjacency list version
    else {
        BellmanFord bellmanFord(vertices, edges, adjList, 0);
        timer.start();
        bellmanFord.start();
        timer.stop();
        //bellmanFord.print();
        time = timer.result();
    }
}

void Benchmark::deleteGraph(int** incMatrix, Node** adjList) const {
    if (incMatrix != nullptr) {
        //delete incidence matrix
        for(int i = 0; i<vertices; i++){    //For each row
            delete[] incMatrix[i];          //delete its column
        }
        delete[] incMatrix;                 //delete all rows
    } else if (adjList != nullptr) {
        //delete adjacency list
        for(int i = 0; i<vertices; i++){    //for each vertex
            Node* temp = adjList[i];        //first neighbour
            while(temp != nullptr){         //delete each neighbour starting from first
                Node* next = temp->nextVertex;
                delete temp;
                temp = next;
            }
        }
        delete[] adjList;                   //delete array (vertices)
    }
}

