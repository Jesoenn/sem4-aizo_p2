//
// Created by jakub on 15.05.2025.
//

#ifndef MINHEAP_H
#define MINHEAP_H



class MinHeap {
public:
    explicit MinHeap(int originalSize);
    ~MinHeap();                     //free keys/heap/position memory

    void buildHeap(int source) const;
    void heapifyDown(int i);        //Heapify down the tree from given heap index
    void heapifyUp(int i);          //Heapify up the tree from given heap index
    int extractMin();               //Returns vertex number which has min key
    void setKey(int v, int weight); //Set vertex weight
    [[nodiscard]] int getKey(int v) const;              //Returns vertex weight
    [[nodiscard]] bool isInHeap(int v) const;
    [[nodiscard]] bool isEmpty() const;                 //Returns if heap has more vertices

private:
    int heapSize,originalSize;
    int* keys;      //index = vertex number, elements -> weights
    int* heap;      //each element is vertex number
    int* position;  //index = vertex number, holds index of vertex location in heap

};



#endif //MINHEAP_H
