#include "Starbucks_Sonodabe.h"


void Starbucks_Sonodabe::build(Entry* c, int n){
    list = new List();
    for(int i = 0; i<n; i++){
        list->insert(c+i);
    }
    

}

Entry* Starbucks_Sonodabe::getNearest(double x, double y){return NULL;}