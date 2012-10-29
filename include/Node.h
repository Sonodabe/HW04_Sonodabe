#pragma once
#include "Starbucks.h"

class Node{
public:
    //Destructer
    ~Node(){
        delete data;
        delete prev;
        delete next;
        data = NULL;
        prev = NULL;
        next = NULL;
    }
    //Date of the node
    Entry* data;
    //Previous pointer
    Node* prev;
    //next pointer
    Node* next;
};