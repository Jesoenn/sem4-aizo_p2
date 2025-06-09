//
// Created by jakub on 25.05.2025.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "../structures/Edge.h"
#include <string>

#include "../enums/AlgorithmType.h"
#include "../enums/GraphType.h"


class FileManager {
public:
    FileManager(std::string inputFileName, std::string outputFileName, std::string saveDataFileName);

    ~FileManager();
    Edge* readFile();
    int getEdgeCount();
    int getVerticesCount();
    void saveData(AlgorithmType algorithm, GraphType graphType, int vertices, int density, int time);

    //Zapisac -> ALGORYTM TYPGRAFU WIERZCHOLKI DENSITY CZAS

private:
    const std::string inputFileName,outputFileName,saveDataFileName;
    std::string toString(AlgorithmType algorithm);
    std::string toString(GraphType graphType);
};



#endif //FILEMANAGER_H
