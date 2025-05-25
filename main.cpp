#include <iostream>
#include "algorithms/Kruskal.h"
#include "algorithms/Prim.h"
#include "core/FileManager.h"
#include "core/Generator.h"

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

//    GraphAdjList list(7,5,GraphDirection::UNDIRECTED);
    // GraphIncMatrix list(7,5,GraphDirection::DIRECTED);
    // std::cout<<"\n\n";
    // list.addEdge(0,1,2);
    // list.addEdge(0,2,5);
    // list.addEdge(0,3,4);
    // list.addEdge(1,3,7);
    // list.addEdge(2,3,1);
    // list.addEdge(2,4,6);
    // list.addEdge(3,4,3);
    // std::cout<<"\n\n";
    // list.print();

//    Kruskal kruskal(5,7,list.getEdgeArray());
//    kruskal.start();

     // Prim prim(5,7,list.getIncMatrix());
     // prim.start();

    Generator generator(4,100,GraphDirection::DIRECTED);
    generator.start();

    FileManager fileManager("test.txt","","");
    fileManager.readFile();

    return 0;
}
