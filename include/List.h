#pragma once
#include "Node.h"

class List {
public:
    List();
    ~List();
    Node* sentinelX;
    Node* sentinelY;
    Node* getMedian(bool x);
    void insert(Entry* insertee);
    int length;
    Entry* remove(Node* toBeRemoved);
private:
    bool insertX(Node* insertee);
    void insertY(Node* insertee);
    double distance(double a, double b);
};