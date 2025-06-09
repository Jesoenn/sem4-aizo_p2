#include <iostream>

#include "algorithms/BellmanFord.h"
#include "algorithms/Kruskal.h"
#include "algorithms/Prim.h"
#include "core/FileManager.h"
#include "core/Generator.h"
#include "algorithms/Dijkstra.h"
#include "modes/Benchmark.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        throw std::invalid_argument("ERROR: --help for more information");
    }
    std::string mode = argv[1];
    // BENCHMARK mode
    //projekt2_aizo.exe --test <graph> <algorithm> <vertices> <density> <outputfile>
    if (mode == "--test") {
        if (argc != 7) {
            std::cout<<"\nBENCHMARK MODE:"<<std::endl;
            std::cout<<"\tUsage:"<<std::endl<<"\tprojekt2_aizo.exe --test <graph> <algorithm> <vertices> <density> <outputfile>"<<std::endl;
            std::cout<<"\n\t<graph>\tGraph representation (0 - Incidence matrix, 1 - Adjacency list)."<<std::endl;
            std::cout<<"\t<algorithm>\tAlgorithm to use (0 - Kruskal, 1 - Prim, 2 - Dijkstra, 3 - Bellman-Ford)."<<std::endl;
            std::cout<<"\t<vertices>\t\tNumber of elements to generate (vertices)."<<std::endl;
            std::cout<<"\t<density>\t\tPercentage of edges (between 1 and 100)."<<std::endl;
            std::cout<<"\t<outputfile>\tWrites Algorithms details in given file."<<std::endl;
            return 1;
        }

        //Input data
        int graph = std::stoi(argv[2]);
        int algorithm = std::stoi(argv[3]);
        int vertices = std::stoi(argv[4]);
        int density = std::stoi(argv[5]);
        std::string outputFile = argv[6];

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

        Benchmark benchmark(graph,algorithm,vertices,density,outputFile);
        benchmark.start();
    } else if (mode == "--file") {

    } else if (mode == "--help") {
        std::cout<<"Usage:"<<"\n\tprojekt2_aizo.exe --file\n\tprojekt2_aizo.exe --test\n";
    }
    else {
        throw std::invalid_argument("ERROR: Wrong mode.");
    }

    return 0;
}
