#pragma once
#include "Starbucks.h"

class Node{
public:
    ~Node(){
        delete data;
        delete prev;
        delete next;
        data = NULL;
        prev = NULL;
        next = NULL;
    }
    Entry* data;
    Node* prev;
    Node* next;
};