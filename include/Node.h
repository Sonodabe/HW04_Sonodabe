#pragma once
#include "Starbucks.h"

class Node{
public:
    //Date of the node
    Entry* data;
    //Previous pointer
    Node* prev;
    //next pointer
    Node* next;
};