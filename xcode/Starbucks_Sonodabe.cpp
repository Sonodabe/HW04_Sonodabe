#include "Starbucks_Sonodabe.h"
#include <iostream>
#include <fstream>

Entry* Starbucks_Sonodabe::buildArray(){
    string name;
    double x, y;
    ifstream myFile("../resources/Starbucks.csv");
    getline(myFile, name, ',');
    myFile.get();
    myFile >> x;
    myFile >> y;
    
    
    
    
    myFile.close();
    
    return NULL;
}

void Starbucks_Sonodabe::build(Entry* c, int n){ }
Entry* Starbucks_Sonodabe::getNearest(double x, double y){return NULL;}