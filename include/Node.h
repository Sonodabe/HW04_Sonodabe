#pragma once
#include "Entry_Sonodabe.h"

class Node{
public:
    //Date of the node
    Entry_Sonodabe* data;
    //Previous pointer
    Node* prev;
    //next pointer
    Node* next;
};