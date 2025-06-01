//
// Created by jakub on 30.05.2025.
//

#include "Benchmark.h"

#include <stdexcept>
#include <utility>
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

// TODO: usunac incmatrix na koniec
void Benchmark::start() {
    FileManager fileManager("","",outputFile);

    GraphDirection graphDirection;
    if (algorithm == AlgorithmType::KRUSKAL || algorithm == AlgorithmType::PRIM) {
        graphDirection = GraphDirection::UNDIRECTED;
    } else {
        graphDirection = GraphDirection::DIRECTED;
    }

    //Potrzbeuje klasy incmatrix/adjlist do getedgearray kruskal
    if ( algorithm == AlgorithmType::KRUSKAL) {                 //Kruskal need GraphIncMatrix/GraphAdjList classes to get arrays

    } else if (graphType == GraphType::INCIDENCE_MATRIX) {
        int** incMatrix = generateIncMatrix(graphDirection);
    } else {
        Node** adjList = generateAdjList(graphDirection);
    }

}

int ** Benchmark::generateIncMatrix(GraphDirection graphDirection) {
    Generator generator(vertices, density, graphDirection);
    generator.start();
    int edgeCount = generator.getEdgeCount();
    Edge* edgeArray = generator.getEdges();

    GraphIncMatrix graphIncMatrix(edgeCount, vertices, graphDirection);
    for (int i =0; i < edgeCount; i++) {
        graphIncMatrix.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
    }
    delete[] edgeArray;

    return graphIncMatrix.getIncMatrix();
}

Node ** Benchmark::generateAdjList(GraphDirection graphDirection) {
    Generator generator(vertices, density, graphDirection);
    generator.start();
    int edgeCount = generator.getEdgeCount();
    Edge* edgeArray = generator.getEdges();

    GraphAdjList graphAdjList(edgeCount, vertices, graphDirection);
    for (int i =0; i < edgeCount; i++) {
        graphAdjList.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
    }
    delete[] edgeArray;

    return graphAdjList.getAdjList();
}

void Benchmark::startMST() {
    if (algorithm == AlgorithmType::KRUSKAL) {


    }
}

void Benchmark::startPath() {
}
