//
// Created by jakub on 2025-05-12.
//

#ifndef PROJEKT2_AIZO_NODE_H
#define PROJEKT2_AIZO_NODE_H


class Node {
public:
    Node(int vertex, int weight);
    int vertex, weight;
    Node* nextVertex;
};


#endif //PROJEKT2_AIZO_NODE_H
