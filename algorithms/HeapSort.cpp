//
// Created by jakub on 27.03.2025.
//
#include "HeapSort.h"
#include <iostream>

HeapSort::HeapSort(Edge* edgeArr, int size):
    array(edgeArr),
    size(size),
    heapSize(size){}

void HeapSort::sort() {
    buildHeap();
    for (int i = size-1; i >= 1; i--) {
        std::swap(array[0], array[i]);  //put largest element last in heap
        heapSize--;                               //decrement heap size
        heapify(0);                             //heapify from 0, because it was max element changed
    }
}

void HeapSort::buildHeap() {
    //heapify from second last row
    for (int i=size/2-1; i>=0; i--) { //-1 because index from 0, not 1
        heapify(i);
    }
}

//maintaining heap properties
void HeapSort::heapify(int i) {
    int largest=i;
    int leftChild = 2*i+1;
    int rightChild = 2*i+2;
    //Searching for largest child value. In case of swap, heapify again
    if (leftChild < heapSize && array[leftChild].weight > array[largest].weight) {
        largest = leftChild;
    }
    if (rightChild < heapSize && array[rightChild].weight > array[largest].weight) {
        largest = rightChild;
    }
    if (largest != i) {
        std::swap(array[i], array[largest]);
        heapify(largest);
    }
}

bool HeapSort::verify() const {
    for (int i = 1; i < size; i++) {
        if (array[i].weight < array[i - 1].weight)
            return false;
    }
    return true;
}
