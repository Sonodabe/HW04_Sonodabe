#pragma once
#include "Starbucks.h"

class TreeNode {
public:
    //Destuctor
    ~TreeNode();
    //Contains all of the values smaller than this node
    TreeNode* left;
    //Contains all of the values greater than this node
    TreeNode* right;
    //The data of the entry
    Entry* data;
    //True if this is an x level split, false otherwise
    bool isX;
};