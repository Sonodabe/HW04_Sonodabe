#include "Starbucks.h"
#include "List.h"
#include "KDTree.h"


class Starbucks_Sonodabe : public Starbucks {
public:
    KDTree* tree;
    TreeNode* buildTree(List* list);
	virtual void build(Entry* c, int n);
    virtual Entry* getNearest(double x, double y);    
};