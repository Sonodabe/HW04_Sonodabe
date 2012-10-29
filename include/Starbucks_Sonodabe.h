#include "Starbucks.h"
#include "List.h"
#include "KDTree.h"


class Starbucks_Sonodabe : public Starbucks {
public:
    KDTree* tree;
    TreeNode* buildTree(List* list, bool onX);
	virtual void build(Entry* c, int n);
    virtual Entry* getNearest(double x, double y);    
    TreeNode* getNearest(double x, double y, TreeNode* root);
    Entry* getManNearest(double x, double y, List* list);    


};