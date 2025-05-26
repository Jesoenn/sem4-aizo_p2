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

void MinHeap::buildHeap() {
    for (int i = 0; i < originalSize; i++) {
        heap[i] = i;
        position[i] = i;
        keys[i] = std::numeric_limits<int>::max(); //in theory inf value
    }
    keys[0] = 0;    //first vertex has weight of 0
}

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
        std::swap(position[heap[i]], position[heap[smallest]]);
        std::swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}

//Heapify up the tree from given heap index
void MinHeap::heapifyUp(int i) {
    int parent = (i-1)/2;
    if (i > 0 && keys[heap[parent]] > keys[heap[i]]) {
        std::swap(position[heap[i]], position[heap[parent]]);
        std::swap(heap[i], heap[parent]);
        heapifyUp(parent);
    }
}

//Returns vertex number which has min key
int MinHeap::extractMin() {
    int min = heap[0];
    std::swap(position[heap[0]], position[heap[heapSize-1]]);   //swap positions of each vertex
    std::swap(heap[0], heap[heapSize-1]);                       //swap first and last heap element
    heapSize--;
    heapifyDown(0);                                                 //heapify from root

    return min;
}

void MinHeap::setKey(int v, int weight) {
    keys[v] = weight;
    heapifyUp(position[v]); //in case key value (weight) is now smaller in child
}

int MinHeap::getKey(int v) {
    return keys[v];
}

bool MinHeap::isInHeap(int v) {
    return position[v] >= 0 && position[v] < heapSize;
}

bool MinHeap::isEmpty() {
    return heapSize == 0;
}
