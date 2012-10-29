#pragma once
#include "Starbucks.h"

class TreeNode {
public:
    ~TreeNode();
    TreeNode* left;
    TreeNode* right;
    Entry* data;
    bool isX;
};