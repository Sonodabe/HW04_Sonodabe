#include "Starbucks.h"


class Starbucks_Sonodabe : public Starbucks {
public:
	virtual void build(Entry* c, int n);
    virtual Entry* getNearest(double x, double y);    
};