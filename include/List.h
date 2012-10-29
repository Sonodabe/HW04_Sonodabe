#pragma once
#include "Node.h"

class List {
public:
    ~List();
    List(Entry* entries, int len);
    List(Entry* entries, int len, bool x);
    Node* sentinel;
    Node* getMedian();
    void insertAll(Entry* entries, int len);
    void insertAndCheckAll(Entry* entries, int len);
    void insert(Entry* toInsert);
    void insertAndCheck(Entry* toInsert);
    int length;
    bool isX;
    Entry* remove(Node* toBeRemoved);
    List* split(bool first);
private:
    double distance(double a, double b);
};