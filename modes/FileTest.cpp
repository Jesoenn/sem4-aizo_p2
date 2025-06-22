//
// Created by jakub on 15.06.2025.
//

#include "FileTest.h"

#include <fstream>
#include <iostream>
#include <utility>

#include "../algorithms/BellmanFord.h"
#include "../algorithms/Dijkstra.h"
#include "../algorithms/Kruskal.h"
#include "../algorithms/Prim.h"
#include "../core/FileManager.h"
#include "../enums/GraphDirection.h"
#include "../structures/graphs/GraphAdjList.h"
#include "../structures/graphs/GraphIncMatrix.h"

FileTest::FileTest(int graph, int algorithm, std::string inputFile, int printAnswer, std::string outputFile,int startVertex, int endVertex):
    vertices(-1),
    edges(-1),
    inputFile(std::move(inputFile)),
    outputFile(std::move(outputFile)),
    startVertex(startVertex),
    endVertex(endVertex),
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

    switch (printAnswer) {
        case 0: this->printAnswer = false; break;
        case 1: this->printAnswer = true; break;
        default: throw std::invalid_argument("ERROR: Printing value can be either 0 or 1.");
    }
}

// Test files
void FileTest::start() {
    FileManager fileManager(inputFile,outputFile,"");   //Read graph, save graph
    edges = fileManager.getEdgeCount(); //get total edges
    vertices = fileManager.getVerticesCount();  //get total vertices

    if (startVertex >= vertices || endVertex >= vertices) {
        throw std::invalid_argument("ERROR: Start vertex or end vertex exceeds number of vertices.");
    }

    Edge* edgeArray = fileManager.readFile();   //get edges

    GraphDirection graphDirection;
    if (algorithm == AlgorithmType::KRUSKAL || algorithm == AlgorithmType::PRIM) {      //MST problem
        graphDirection = GraphDirection::UNDIRECTED;
    } else {        //Shortest path problem
        graphDirection = GraphDirection::DIRECTED;
    }

    int answerEdges=0;                                  //MST/Path edge count
    Edge* answerEdgeArray;                              //MST/Path edge array

    int** incMatrix = nullptr;                          //Incidence matrix
    Node** adjList = nullptr;                           //Adjacency list

    if ( algorithm == AlgorithmType::KRUSKAL) {
        answerEdgeArray=performKruskal(edgeArray, answerEdges);              // Kruskal needs Graph class to get edge array (other algorithms don't)
    } else {
        //Generate specific graph
        if (graphType == GraphType::INCIDENCE_MATRIX) {
            incMatrix = generateIncMatrix(edgeArray, graphDirection);
        } else {
            adjList = generateAdjList(edgeArray, graphDirection);
        }

        switch (algorithm) {
            case AlgorithmType::PRIM: answerEdgeArray = performPrim(incMatrix, adjList, answerEdges); break;
            case AlgorithmType::DIJKSTRA: answerEdgeArray = performDijkstra(incMatrix, adjList, answerEdges); break;
            case AlgorithmType::BELLMAN_FORD: answerEdgeArray = performBellmanFord(incMatrix, adjList, answerEdges); break;
            default: throw std::invalid_argument("ERROR: Wrong algorithm.");
        }
    }

    fileManager.saveResult(vertices, answerEdges, answerEdgeArray);         //save answerEdgeArray to file
    delete[] answerEdgeArray;
    deleteGraph(incMatrix, adjList);                                        //free allocated memory for graphs
}

int ** FileTest::generateIncMatrix(const Edge *edgeArray, GraphDirection graphDirection) const {
    GraphIncMatrix graphIncMatrix(edges, vertices, graphDirection);
    std::cout<<"Generating incidence matrix..."<<std::endl;

    //Add each edge to graph
    for (int i =0; i < edges; i++) {
        graphIncMatrix.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
    }
    delete[] edgeArray; //Free memory from generated edges

    return graphIncMatrix.getIncMatrix();
}

Node ** FileTest::generateAdjList(const Edge *edgeArray, GraphDirection graphDirection) const {
    GraphAdjList graphAdjList(edges, vertices, graphDirection);
    std::cout<<"Generating adjacency list..."<<std::endl;

    //Add each edge to graph
    for (int i =0; i < edges; i++) {
        graphAdjList.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
    }
    delete[] edgeArray; //Free memory from generated edges

    return graphAdjList.getAdjList();
}

Edge* FileTest::performKruskal(const Edge *edgeArray, int &answerEdges) {
    Edge* answerEdgeArray=nullptr;
    if (graphType == GraphType::INCIDENCE_MATRIX) {
        //Create graph edges
        GraphIncMatrix graphIncMatrix(edges, vertices, GraphDirection::UNDIRECTED);
        std::cout<<"Generating incidence matrix..."<<std::endl;

        //Add each edge to graph
        for (int i =0; i < edges; i++) {
            graphIncMatrix.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
        }
        delete[] edgeArray; //Free memory from generated edges

        //Perform algorithm
        timer.start();
        Kruskal kruskal(vertices,edges,graphIncMatrix.getEdgeArray());
        kruskal.start();
        timer.stop();

        if (printAnswer) {
            kruskal.print();
        }

        time = timer.result();
        answerEdges = kruskal.getAnswerSize();      //get MST size
        answerEdgeArray = kruskal.getAnswerEdges(); //get MST edge array
        std::cout<<"\nMST exists: "<<kruskal.verifyMST()<<std::endl;
        std::cout<<"Time: "<<time<<std::endl<<std::endl;
    } else {
        //Create graph from edges
        GraphAdjList graphAdjList(edges, vertices, GraphDirection::UNDIRECTED);
        std::cout<<"Generating adjacency list..."<<std::endl;

        //Add each edge to graph
        for (int i =0; i < edges; i++) {
            graphAdjList.addEdge(edgeArray[i].from, edgeArray[i].to, edgeArray[i].weight);
        }
        delete[] edgeArray; //Free memory from generated edges

        //Perform algorithm
        timer.start();
        Kruskal kruskal(vertices,edges,graphAdjList.getEdgeArray());
        kruskal.start();
        timer.stop();

        if (printAnswer) {
            kruskal.print();
        }

        time = timer.result();
        answerEdges = kruskal.getAnswerSize();      //get MST size
        answerEdgeArray = kruskal.getAnswerEdges(); //get MST edge array
        std::cout<<"\nMST exists: "<<kruskal.verifyMST()<<std::endl;
        std::cout<<"Time: "<<time<<std::endl<<std::endl;
    }

    return answerEdgeArray;
}

Edge* FileTest::performPrim(int **incMatrix, Node **adjList, int &answerEdges) {
    Edge* answerEdgeArray=nullptr;
    // Incidence matrix version
    if (incMatrix != nullptr) {
        Prim prim(vertices,edges,incMatrix);
        timer.start();
        prim.start();
        timer.stop();

        if (printAnswer) {
            prim.print();
        }

        time = timer.result();
        answerEdges = prim.getAnswerSize();      //get MST size
        answerEdgeArray = prim.getAnswerEdges(); //get MST edge array
        std::cout<<"\nMST exists: "<<prim.verifyMST()<<std::endl;
        std::cout<<"Time: "<<time<<std::endl<<std::endl;
    }
    // Adjacency list version
    else {
        Prim prim(vertices,edges,adjList);
        timer.start();
        prim.start();
        timer.stop();

        if (printAnswer) {
            prim.print();
        }

        time = timer.result();
        answerEdges = prim.getAnswerSize();      //get MST size
        answerEdgeArray = prim.getAnswerEdges(); //get MST edge array
        std::cout<<"MST exists: "<<prim.verifyMST()<<std::endl;
        std::cout<<"Time: "<<time<<std::endl<<std::endl;
    }
    return answerEdgeArray;
}

Edge * FileTest::performDijkstra(int **incMatrix, Node **adjList, int &answerEdges) {
    Edge* answerEdgeArray=nullptr;
    // incidence matrix version
    if (incMatrix != nullptr) {
        Dijkstra dijkstra(vertices,edges,incMatrix,startVertex);
        timer.start();
        dijkstra.start();
        timer.stop();

        if (printAnswer) {
            dijkstra.print();
        }

        time = timer.result();
        std::cout<<"Time: "<<time<<std::endl<<std::endl;
        answerEdges = dijkstra.getPathLength(startVertex,endVertex);
        answerEdgeArray = dijkstra.getPath(startVertex,endVertex, printAnswer);
    }
    // Adjacency list version
    else {
        Dijkstra dijkstra(vertices,edges,adjList,startVertex);
        timer.start();
        dijkstra.start();
        timer.stop();

        if (printAnswer) {
            dijkstra.print();
        }

        time = timer.result();
        std::cout<<"Time: "<<time<<std::endl<<std::endl;
        answerEdges = dijkstra.getPathLength(startVertex,endVertex);
        answerEdgeArray = dijkstra.getPath(startVertex,endVertex, printAnswer);
    }
    return answerEdgeArray;
}

Edge * FileTest::performBellmanFord(int **incMatrix, Node **adjList, int &answerEdges) {
    Edge* answerEdgeArray=nullptr;
    // incidence matrix version
    if (incMatrix != nullptr) {
        BellmanFord bellmanFord(vertices, edges, incMatrix,startVertex);
        timer.start();
        bellmanFord.start();
        timer.stop();

        if (printAnswer) {
            bellmanFord.print();
        }

        time = timer.result();
        std::cout<<"Time: "<<time<<std::endl<<std::endl;
        answerEdges = bellmanFord.getPathLength(startVertex,endVertex);
        answerEdgeArray = bellmanFord.getPath(startVertex,endVertex,printAnswer);
    }
    // Adjacency list version
    else {
        BellmanFord bellmanFord(vertices, edges, adjList,startVertex);
        timer.start();
        bellmanFord.start();
        timer.stop();

        if (printAnswer) {
            bellmanFord.print();
        }

        time = timer.result();
        std::cout<<"Time: "<<time<<std::endl<<std::endl;
        answerEdges = bellmanFord.getPathLength(startVertex,endVertex);
        answerEdgeArray = bellmanFord.getPath(startVertex,endVertex,printAnswer);
    }
    return answerEdgeArray;
}

void FileTest::deleteGraph(int **incMatrix, Node **adjList) const {
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
