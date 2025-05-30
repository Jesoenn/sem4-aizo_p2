#include <iostream>

#include "algorithms/BellmanFord.h"
#include "algorithms/Kruskal.h"
#include "algorithms/Prim.h"
#include "core/FileManager.h"
#include "core/Generator.h"
#include "algorithms/Dijkstra.h"

int main() {
    // GraphIncMatrix test(6,4,GraphDirection::UNDIRECTED);
    //
    // test.addEdge(0,1,1);
    // test.addEdge(1,2,3);
    // test.addEdge(1,2,2);
    // test.addEdge(2,3,4);
    // test.addEdge(0,1,14214);
    // test.addEdge(0,3,1);
    //
    // test.print();
    //
    // Kruskal kruskal(4,6,test.getEdgeArray());
    // kruskal.start();

    GraphAdjList list(7,5,GraphDirection::DIRECTED);
     // GraphIncMatrix list(7,5,GraphDirection::DIRECTED);
     std::cout<<"\n\n";
     list.addEdge(0,1,1);
     list.addEdge(1,2,1);
     list.addEdge(0,3,10);
     list.addEdge(1,3,1);
     list.addEdge(1,4,10);
     list.addEdge(2,4,1);
     list.addEdge(3,4,10);
     std::cout<<"\n\n";
     list.print();

     // Dijkstra dijkstra(5,7,list.getIncMatrix());
     // dijkstra.start();
     // dijkstra.print();
//    BellmanFord bellmanFord(5,7,list.getAdjList());
//    bellmanFord.start();
//    bellmanFord.print();

//    Kruskal kruskal(5,7,list.getEdgeArray());
//    kruskal.start();

     // Prim prim(5,7,list.getIncMatrix());
     // prim.start();

//    FileManager fileManager("test.txt","","");
//    fileManager.readFile();

    Generator generator(4,100,GraphDirection::UNDIRECTED);
    generator.start();

    return 0;
}
