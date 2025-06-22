//
// Created by jakub on 15.05.2025.
//

#include "MinHeap.h"
#include <iostream>
#include <limits>

MinHeap::MinHeap(int originalSize):
    heapSize(originalSize),
    originalSize(originalSize){
    keys = new int[originalSize];
    heap = new int[originalSize];
    position = new int[originalSize];
}

MinHeap::~MinHeap() {
    delete[] keys;
    delete[] heap;
    delete[] position;
}

void MinHeap::buildHeap(int source) const {
    for (int i = 0; i < originalSize; i++) {
        heap[i] = i;        //Under each heap index there is vertex (starting with 0)
        position[i] = i;    //Position of each vertex in heap is i
        keys[i] = std::numeric_limits<int>::max(); //inf value
    }

    keys[source] = 0;       //set weight of source to 0
    if (source!=0) {
        std::swap(position[heap[source]], position[heap[0]]);   // Swap vertices positions
        std::swap(heap[source], heap[0]);                       // Swap vertices in heap positions first with source
    }
    //No more heapify is needed because every weight is heap is the same (inf)
}

// void MinHeap::buildHeap(int source) const {
//     for (int i = 0; i < originalSize; i++) {
//         heap[i] = i;        //Under each heap index there is vertex (starting with 0)
//         position[i] = i;    //Position of each vertex in heap is i
//         keys[i] = std::numeric_limits<int>::max(); //inf value
//     }
//     keys[0] = 0;    //first vertex has weight of 0
// }

//Heapify down from position in heap "i"
void MinHeap::heapifyDown(int i) {
    int smallest=i;
    int leftChild = 2*i+1;
    int rightChild = 2*i+2;
    //Searching for smallest child value. In case of swap, heapify again
    if (leftChild < heapSize && keys[heap[leftChild]] < keys[heap[smallest]]) {
        smallest = leftChild;
    }
    if (rightChild < heapSize && keys[heap[rightChild]] < keys[heap[smallest]]) {
        smallest = rightChild;
    }
    if (smallest != i) {
        std::swap(position[heap[i]], position[heap[smallest]]); // Swap vertices positions
        std::swap(heap[i], heap[smallest]);                     // Swap vertices in heap positions "i" and "smallest"
        heapifyDown(smallest);
    }
}

//Heapify up the tree from given heap index (position in heap)
void MinHeap::heapifyUp(int i) {
    int parent = (i-1)/2;
    //If parent's weight is bigger "i" weight, then swap and heapify
    if (i > 0 && keys[heap[parent]] > keys[heap[i]]) {
        std::swap(position[heap[i]], position[heap[parent]]);   // Swap vertices positions
        std::swap(heap[i], heap[parent]);                       // Swap vertices in heap positions "i" and "parent"
        heapifyUp(parent);
    }
}

//Returns vertex number which has min key
int MinHeap::extractMin() {
    int min = heap[0];  //min heap -> root is minimum key
    std::swap(position[heap[0]], position[heap[heapSize-1]]);   //swap positions of root vertex(min) and last one in heap
    std::swap(heap[0], heap[heapSize-1]);                       //swap first and last heap elements
    heapSize--;                                                           //Decrease heap size, because min is extracted
    heapifyDown(0);                                                     //heapify from root

    return min;
}

void MinHeap::setKey(int v, int weight) {
    keys[v] = weight;
    heapifyUp(position[v]); //heapify in case key value (weight) is now smaller than parent's weight
}

int MinHeap::getKey(int v) const {
    return keys[v];
}

bool MinHeap::isInHeap(int v) const {
    return position[v] >= 0 && position[v] < heapSize;
}

bool MinHeap::isEmpty() const {
    return heapSize == 0;
}
