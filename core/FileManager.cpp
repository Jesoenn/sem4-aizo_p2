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