//
// Created by jakub on 15.05.2025.
//

#ifndef MINHEAP_H
#define MINHEAP_H



class MinHeap {
public:
    MinHeap(int originalSize);
    ~MinHeap();

    void buildHeap();
    void heapifyDown(int i);
    void heapifyUp(int i);
    int extractMin();
    void decreaseKey();
    void setKey(int i, int weight);
    int getKey(int i);
    bool isInHeap(int i);
    bool isEmpty();
private:
    int heapSize,originalSize;
    int* keys;      //index = vertex number, holds key values
    int* heap;      //each value is vertex number
    int* position;  //index = vertex number, holds index of vertex location in heap

};



#endif //MINHEAP_H
