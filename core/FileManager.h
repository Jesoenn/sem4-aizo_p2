//
// Created by jakub on 25.05.2025.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "../structures/Edge.h"
#include <string>


class FileManager {
public:
    FileManager(std::string inputFileName, std::string outputFileName, std::string saveDataFileName);

    ~FileManager();
    Edge* readFile();
    int getEdgeCount();
    int getVerticesCount();

private:
    const std::string inputFileName,outputFileName,saveDataFileName;
};



#endif //FILEMANAGER_H
