#include <iostream>
#include "core/FileManager.h"
#include "modes/Benchmark.h"
#include "modes/FileTest.h"
int main(int argc, char* argv[]) {
    if (argc == 1) {
        throw std::invalid_argument("ERROR: --help for more information");
    }

    std::string mode = argv[1];
    // BENCHMARK MODE
    //projekt2_aizo.exe --test <graph> <algorithm> <vertices> <density> <outputfile> <printGraph>
    if (mode == "--test") {
        if (argc != 8) {
            std::cout<<"\nBENCHMARK MODE:"<<std::endl;
            std::cout<<"\tUsage:"<<std::endl<<"\tprojekt2_aizo.exe --test <graph> <algorithm> <vertices> <density> <outputfile> <printGraph>"<<std::endl;
            std::cout<<"\n\t<graph>\tGraph representation (0 - Incidence matrix, 1 - Adjacency list)."<<std::endl;
            std::cout<<"\t<algorithm>\tAlgorithm to use (0 - Kruskal, 1 - Prim, 2 - Dijkstra, 3 - Bellman-Ford)."<<std::endl;
            std::cout<<"\t<vertices>\t\tNumber of elements to generate (vertices)."<<std::endl;
            std::cout<<"\t<density>\t\tPercentage of edges (between 1 and 100)."<<std::endl;
            std::cout<<"\t<outputfile>\tWrites algorithms details in given file."<<std::endl;
            std::cout<<"\t<printGraph>\tPrints generated graph (0 - NO, 1 - YES)."<<std::endl;
            return 1;
        }

        //Input data
        int graph = std::stoi(argv[2]);
        int algorithm = std::stoi(argv[3]);
        int vertices = std::stoi(argv[4]);
        int density = std::stoi(argv[5]);
        std::string outputFile = argv[6];
        int print = std::stoi(argv[7]);

        //Validate
        if (graph < 0 || graph > 1) {
            throw std::invalid_argument("ERROR: Wrong graph");
        }
        if (algorithm < 0 || algorithm > 3) {
            throw std::invalid_argument("ERROR: Wrong algorithm");
        }
        if (vertices <= 2) {
            throw std::invalid_argument("ERROR: Must use more than 2 vertices");
        }

        if (density < 1 || density > 100) {
            throw std::invalid_argument("ERROR: Density value must be between 1 and 100");
        }

        if (print>1 || print <0) {
            throw std::invalid_argument("ERROR: Print value must be 0 or 1");
        }

        //Start
        Benchmark benchmark(graph,algorithm,vertices,density,outputFile, print);
        benchmark.start();
    }
    // FILE TEST MODE
    // projekt2_aizo.exe --file <graph> <algorithm> <inputFile> <printAnswer> <outputFile> [startVertex] [EndVertex]
    else if (mode == "--file") {
        if (argc < 7) {
            std::cout<<"\nBENCHMARK MODE:"<<std::endl;
            std::cout<<"\tUsage:"<<std::endl<<"\tprojekt2_aizo.exe --file <graph> <algorithm> <inputFile> <printAnswer> <outputFile> [startVertex] [EndVertex]"<<std::endl;
            std::cout<<"\n\t<graph>\tGraph representation (0 - Incidence matrix, 1 - Adjacency list)."<<std::endl;
            std::cout<<"\t<algorithm>\tAlgorithm to use (0 - Kruskal, 1 - Prim, 2 - Dijkstra, 3 - Bellman-Ford)."<<std::endl;
            std::cout<<"\t<inputFile>\tFile to load graph from."<<std::endl;
            std::cout<<"\t<printAnswer>\tPrints algorithm result (0 - NO, 1 - YES)."<<std::endl;
            std::cout<<"\t<outputfile>\tWrites algorithm result in given file."<<std::endl;
            std::cout<<"\t[startVertex]\tVertex to start finding path from"<<std::endl;
            std::cout<<"\t[endVertex]\tVertex where path ends"<<std::endl;
            return 1;
        }

        //Input data
        int graph = std::stoi(argv[2]);
        int algorithm = std::stoi(argv[3]);
        std::string inputFile = argv[4];
        int print = std::stoi(argv[5]);
        std::string outputFile = argv[6];
        int startVertex=0,endVertex=0;

        //Validate
        if (graph < 0 || graph > 1) {
            throw std::invalid_argument("ERROR: Wrong graph");
        }
        if (algorithm < 0 || algorithm > 3) {
            throw std::invalid_argument("ERROR: Wrong algorithm");
        }
        if (print>1 || print <0) {
            throw std::invalid_argument("ERROR: Print value must be 0 or 1");
        }
        if (algorithm>=2 && argc!= 9) {
            throw std::invalid_argument("ERROR: For finding paths you need to provide starting and ending vertex");
        }
        if (algorithm>=2) {
            startVertex = std::stoi(argv[7]);
            endVertex = std::stoi(argv[8]);
            if (startVertex < 0 || endVertex < 0) {
                throw std::invalid_argument("ERROR: Wrong starting vertex/ending vertex values");
            }
        }

        //Start
        FileTest fileTest(graph,algorithm,inputFile,print,outputFile,startVertex,endVertex);
        fileTest.start();
    } else if (mode == "--help") {
        std::cout<<"Usage:"
            <<"\n\tprojekt2_aizo.exe --file"
            <<"\n\tprojekt2_aizo.exe --file <graph> <algorithm> <inputFile> <printAnswer> <outputFile> [startVertex] [endVertex]"
            <<"\n\t\tReads graph from a file and solves it using selected algorithm."
            <<"\n\n\tprojekt2_aizo.exe --test"
            <<"\n\tprojekt2_aizo.exe --test <graph> <algorithm> <vertices> <density> <outputFile> <printGraph>"
            <<"\n\t\tGenerates a graph and tests selected algorithm on it.\n";

    }
    else {
        throw std::invalid_argument("ERROR: Wrong mode. --help for more information.");
    }

    return 0;
}
