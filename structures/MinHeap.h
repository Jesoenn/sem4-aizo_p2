//
// Created by jakub on 15.05.2025.
//

#ifndef MINHEAP_H
#define MINHEAP_H



class MinHeap {
public:
    explicit MinHeap(int originalSize);
    ~MinHeap();

    void buildHeap();
    void heapifyDown(int i);
    void heapifyUp(int i);          //Heapify up the tree from given heap index
    int extractMin();               //Returns vertex number which has min key
    void setKey(int v, int weight);
    int getKey(int v);
    bool isInHeap(int v);
    bool isEmpty();
private:
    int heapSize,originalSize;
    int* keys;      //index = vertex number, holds key values/weights
    int* heap;      //each value is vertex number
    int* position;  //index = vertex number, holds index of vertex location in heap

};



#endif //MINHEAP_H
