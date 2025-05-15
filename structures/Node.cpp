//
// Created by jakub on 2025-05-12.
//

#include "Node.h"

Node::Node(int vertex, int weight):
    vertex(vertex),
    weight(weight) {
    nextVertex = nullptr;
}
