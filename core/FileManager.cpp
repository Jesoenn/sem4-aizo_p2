//
// Created by jakub on 25.05.2025.
//

#include "FileManager.h"
#include <utility>
#include <iostream>
#include <fstream>

FileManager::FileManager(std::string inputFileName, std::string outputFileName, std::string saveDataFileName):
    inputFileName(std::move(inputFileName)),
    outputFileName(std::move(outputFileName)),
    saveDataFileName(std::move(saveDataFileName)){}

FileManager::~FileManager() {

}

Edge * FileManager::readFile() {
    int input;
    std::ifstream file(inputFileName);

    if (!file.is_open()) {
        std::cerr << "Cannot open file. Array is empty" << std::endl;
        return nullptr;
    }

    file >> input;  //edges
    const int edgeCount=input;
    file >> input;  //vertices
    Edge* edgeArray = new Edge[edgeCount];
    int currentEdge=0;
    int from, to, weight;

    while (file>>from) {
        if (currentEdge >= edgeCount) {
            delete[] edgeArray;
            std::cerr << "More edges than expected!" << std::endl;
            return nullptr;
        }

        if (!(file >> to >> weight)) {
            delete[] edgeArray;
            std::cerr << "Error reading edge data!" << std::endl;
            return nullptr;
        }
        edgeArray[currentEdge].from = from;
        edgeArray[currentEdge].to = to;
        edgeArray[currentEdge].weight = weight;
        currentEdge++;
    }

    if (currentEdge < edgeCount) {
        delete[] edgeArray;
        std::cerr << "Less edges than expected!" << std::endl;
        return nullptr;
    }

    file.close();
    return edgeArray;
}

int FileManager::getEdgeCount() {
    std::ifstream file(inputFileName);
    if (!file.is_open()) {
        std::cerr << "Cannot open file. Wrong edge count!" << std::endl;
        return -1;
    }

    int edgeCount = 0;
    file >> edgeCount;
    file.close();
    return edgeCount;
}

int FileManager::getVerticesCount() {
    std::ifstream file(inputFileName);
    if (!file.is_open()) {
        std::cerr << "Cannot open file. Wrong vertices count!" << std::endl;
        return -1;
    }

    int verticesCount = 0;
    file >> verticesCount >> verticesCount;  // odczytaj obie liczby, ale zwróć drugą
    file.close();
    return verticesCount;
}

void FileManager::saveData(AlgorithmType algorithm, GraphType graphType, int vertices, int density, int time) {
    std::ofstream file(saveDataFileName, std::ios::app);
    if (!file.is_open()) {
        std::cout << "Cannot open/create data file." << std::endl;
        return;
    }

    //Algorytm | Graf | wierzcholki | gestosc | czas
    file << toString(algorithm) << "\t"
    <<  toString(graphType) << "\t"
    << vertices << "\t"
    << density << "\t"
    << time << std::endl;

    file.close();
}

void FileManager::saveResult(int vertices, int edges, Edge *edgeArray) {
    std::ofstream file(outputFileName);
    if (!file.is_open()) {
        std::cout << "Cannot open/create data file." << std::endl;
        return;
    }
    file<<edges<<"\t"<<vertices<<std::endl;
    for (int i = 0; i < edges; i++) {
        file<<edgeArray[i].from<<"\t"<<edgeArray[i].to<<"\t"<<edgeArray[i].weight<<std::endl;
    }

    file.close();
}

std::string FileManager::toString(AlgorithmType algorithm) {
    switch (algorithm) {
        case AlgorithmType::PRIM: return "PRIM";
        case AlgorithmType::KRUSKAL: return "KRUSKAL";
        case AlgorithmType::DIJKSTRA: return "DIJKSTRA";
        case AlgorithmType::BELLMAN_FORD: return "BELLMAN_FORD";
        default: return "INVALID";
    }
}

std::string FileManager::toString(GraphType graphType) {
    switch (graphType) {
        case GraphType::ADJACENCY_LIST: return "ADJACENCY_LIST";
        case GraphType::INCIDENCE_MATRIX: return "INCIDENCE_MATRIX";
        default: return "INVALID";
    }
}
