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

    [[nodiscard]] Edge* readFile() const;   //Read edges from given file
    [[nodiscard]] int getEdgeCount() const;
    [[nodiscard]] int getVerticesCount() const;
    void saveData(AlgorithmType algorithm, GraphType graphType, int vertices, int density, int time) const;   // Save algorithm results
    void saveResult(int vertices, int edges, const Edge* edgeArray) const;  // Save algorithm result (graph) in given file

private:
    const std::string inputFileName,outputFileName,saveDataFileName;
    static std::string toString(AlgorithmType algorithm);
    static std::string toString(GraphType graphType);
};



#endif //FILEMANAGER_H
