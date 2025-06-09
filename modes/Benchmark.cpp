//
// Created by jakub on 30.05.2025.
//

#include "Benchmark.h"

#include <stdexcept>
#include <utility>

#include "../algorithms/BellmanFord.h"
#include "../algorithms/Dijkstra.h"
#include "../algorithms/Kruskal.h"
#include "../algorithms/Prim.h"
#include "../core/Generator.h"
#include "../structures/graphs/GraphAdjList.h"
#include "../structures/graphs/GraphIncMatrix.h"

Benchmark::Benchmark(int graph, int algorithm, int vertices, int density, std::string outputFile):
    vertices(vertices),
    density(density),
    outputFile(std::move(outputFile)){

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
}

void Benchmark::start() {
    FileManager fileManager("","",outputFile);

    GraphDirection graphDirection;
    if (algorithm == AlgorithmType::KRUSKAL || algorithm == AlgorithmType::PRIM) {
        graphDirection = GraphDirection::UNDIRECTED;
    } else {
        graphDirection = GraphDirection::DIRECTED;
    }
    Edge* edgeArray = generateEdges(graphDirection);
    int** incMatrix = nullptr;
    Node** adjList = nullptr;

    if ( algorithm == AlgorithmType::KRUSKAL) {
        performKruskal(edgeArray);              // Kruskal needs Graph class to get edge array (other algorithms don't)
    } else {
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

    fileManager.saveData(algorithm, graphType, vertices, density, time);    //save data to file

    deleteGraph(incMatrix, adjList);
}

Edge* Benchmark::generateEdges(GraphDirection graphDirection) {
    std::cout<<"Generating edges..."<<std::endl;
    Generator generator(vertices, density, graphDirection);
    generator.start();
    edges = generator.getEdgeCount();
    return generator.getEdges();
}

int ** Benchmark::generateIncMatrix(Edge* edgeArray, GraphDirection graphDirection) {
    GraphIncMatrix graphIncMatrix(edges, vertices, graphDirection);
    std::cout<<"Generating incidence matrix..."<<std::endl;
    for (int i =0; i < edges; i++) {
        graphIncMatrix.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
    }
    delete[] edgeArray;

    return graphIncMatrix.getIncMatrix();
}

Node ** Benchmark::generateAdjList(Edge* edgeArray, GraphDirection graphDirection) {
    GraphAdjList graphAdjList(edges, vertices, graphDirection);
    std::cout<<"Generating adjacency list..."<<std::endl;
    for (int i =0; i < edges; i++) {
        graphAdjList.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
    }
    delete[] edgeArray;

    return graphAdjList.getAdjList();
}

void Benchmark::performKruskal(Edge *edgeArray) {
    if (graphType == GraphType::INCIDENCE_MATRIX) {
        GraphIncMatrix graphIncMatrix(edges, vertices, GraphDirection::UNDIRECTED);
        std::cout<<"Generating incidence matrix..."<<std::endl;
        for (int i =0; i < edges; i++) {
            graphIncMatrix.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
        }
        delete[] edgeArray;
        timer.start();
        Kruskal kruskal(vertices,edges,graphIncMatrix.getEdgeArray());
        kruskal.start();
        timer.stop();
        //kruskal.print();
        time = timer.result();
    } else {
        GraphAdjList graphAdjList(edges, vertices, GraphDirection::UNDIRECTED);
        std::cout<<"Generating adjacency list..."<<std::endl;
        for (int i =0; i < edges; i++) {
            graphAdjList.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
        }
        delete[] edgeArray;

        timer.start();
        Kruskal kruskal(vertices,edges,graphAdjList.getEdgeArray());
        kruskal.start();
        timer.stop();
        //kruskal.print();
        time = timer.result();
    }
}

void Benchmark::performPrim(int **incMatrix, Node **adjList) {
    // incidence matrix version
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
        Dijkstra dijkstra(vertices,edges,incMatrix);
        timer.start();
        dijkstra.start();
        timer.stop();
        //dijkstra.print();
        time = timer.result();
    }
    // Adjacency list version
    else {
        Dijkstra dijkstra(vertices,edges,adjList);
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
        BellmanFord bellmanFord(vertices, edges, incMatrix);
        timer.start();
        bellmanFord.start();
        timer.stop();
        //bellmanFord.print();
        time = timer.result();
    }
    // Adjacency list version
    else {
        BellmanFord bellmanFord(vertices, edges, adjList);
        timer.start();
        bellmanFord.start();
        timer.stop();
        //bellmanFord.print();
        time = timer.result();
    }
}

void Benchmark::deleteGraph(int** incMatrix, Node** adjList) {
    if (incMatrix != nullptr) {
        for(int i = 0; i<vertices; i++){    //For each row
            delete[] incMatrix[i];          //delete its column
        }
        delete[] incMatrix;                 //delete all rows
    } else if (adjList != nullptr) {
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

