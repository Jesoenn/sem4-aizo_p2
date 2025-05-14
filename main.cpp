#include <iostream>
#include "structures/Graph.h"
#include "structures/GraphIncMatrix.h"
#include "structures/GraphAdjList.h"
#include "algorithms/Kruskal.h"

int main() {
    GraphIncMatrix test(6,4,GraphDirection::UNDIRECTED);

    test.addEdge(0,1,1);
    test.addEdge(1,2,3);
    test.addEdge(1,2,2);
    test.addEdge(2,3,4);
    test.addEdge(0,1,14214);
    test.addEdge(0,3,1);

    test.print();

    Kruskal kruskal(4,6,test.getEdgeArray());
    kruskal.start();




//    int* p = new int(2);
//    std::cout<<*p<<std::endl;
//    delete p;
//    p = nullptr;
//    GraphAdjList list(3,3,GraphDirection::DIRECTED);
//    std::cout<<"\n\n";
//    list.addEdge(0,2,20);
//    list.addEdge(0,1,10);
//    list.addEdge(2,1,30);
//    list.print();



    return 0;
}
