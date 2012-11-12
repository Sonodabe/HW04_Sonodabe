#pragma once
#include "Entry_Sonodabe.h"

class TreeNode {
public:
    //Destuctor
    ~TreeNode();
    //Contains all of the values smaller than this node
    TreeNode* left;
    //Contains all of the values greater than this node
    TreeNode* right;
    //The data of the entry
    Entry_Sonodabe* data;
    //True if this is an x level split, false otherwise
    bool isX;
};