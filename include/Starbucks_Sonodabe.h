#include "Starbucks.h"
#include "List.h"


class Starbucks_Sonodabe : public Starbucks {
public:
    List* list;
	virtual void build(Entry* c, int n);
    virtual Entry* getNearest(double x, double y);    
};