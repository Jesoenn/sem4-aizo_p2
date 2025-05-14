//
// Created by jakub on 27.03.2025.
//

#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "../structures/Edge.h"

class HeapSort {
public:
    HeapSort(Edge* edgeArr, int size);
    void sort();
    bool verify();
private:
    void buildHeap();
    void heapify(int i);

    Edge* array;
    int size,heapSize;
};

#endif //HEAPSORT_H
