#include "Starbucks_Sonodabe.h"


void Starbucks_Sonodabe::build(Entry* c, int n){
    List* list = new List(c, n);
    
    tree = new KDTree;
    tree->root = buildTree(list);
    
    int x = 1;
    
}

TreeNode* Starbucks_Sonodabe::buildTree(List* list){
    if(list == NULL || list->length == 0)
        return NULL;
    
    TreeNode* root = new TreeNode;
    root->data = list->getMedian()->data;
    root->left = buildTree(list->split(true));
    root->right = buildTree(list->split(false)); 
    
    return root;
}

Entry* Starbucks_Sonodabe::getNearest(double x, double y){return NULL;}