#include "List.h"

List::List(){
    sentinelX = new Node;
    sentinelY = new Node;
    
    sentinelX->nextX = sentinelX;
    sentinelX->prevX = sentinelX;
    sentinelY->nextY = sentinelY;
    sentinelY->prevY = sentinelY;
    
    sentinelX->nextY = NULL;
    sentinelX->prevY = NULL;
    sentinelY->nextX = NULL;
    sentinelY->prevX = NULL;
    
    length = 0;
}

void List::insert(Entry* insertee){
    Node* temp = new Node;
    temp->data = insertee;
    
    if(insertX(temp)){
        insertY(temp);
        length++;   
    }
    
}

Node* List::getMedian(bool x){
    int medianIndex = length/2+1;
    Node* cur;
    
    if(x){
        cur = sentinelX;
        for(int i = 0; i<medianIndex; i++)
            cur = cur->nextX;
    }else{
        cur = sentinelY;
        for(int i = 0; i<medianIndex; i++)
            cur = cur->nextY;
    }
    
    return cur;
}

Entry* List::remove(Node* toBeRemoved){
    if(toBeRemoved == NULL || toBeRemoved == sentinelX ||
       toBeRemoved == sentinelY)
        return NULL;
    
    toBeRemoved->prevX->nextX = toBeRemoved->nextX;
    toBeRemoved->nextX->prevX = toBeRemoved->prevX;
    toBeRemoved->prevY->nextY = toBeRemoved->nextY;
    toBeRemoved->nextY->prevY = toBeRemoved->prevY;
    
    Entry* data = toBeRemoved->data;
    delete toBeRemoved;
    
    
    length--;
    
    return data;
}


bool List::insertX(Node* insertee){
    double posX = insertee->data->x;
    double posY = insertee->data->y;
    Node* cur = sentinelX->nextX;
    
    double distX, distY;
    
    while(cur != sentinelX && cur->data->x < posX){
        distX = distance(cur->data->x, posX);
        distY = distance(cur->data->y, posY);
        if(distX <= 0.00001 && distY <= 0.00001)
            return false;
        
        cur = cur->nextX;
    }
    
    if(cur == sentinelX){
        sentinelX->prevX->nextX = insertee;
        insertee->prevX = sentinelX->prevX;
        insertee->nextX = sentinelX;
        sentinelX->prevX = insertee;
        return true;
    }
    
    distX = distance(cur->data->x, posX);
    distY = distance(cur->data->y, posY);
    if(distX <= 0.00001 && distY <= 0.00001)
        return false;
    
    cur->prevX->nextX = insertee;
    insertee->prevX = cur->prevX;
    insertee->nextX = cur;
    cur->prevX = insertee;
    return true;
}

void List::insertY(Node* insertee){
    double posY = insertee->data->y;
    Node* cur = sentinelY->nextY;
        
    while(cur != sentinelY && cur->data->y < posY)
        cur = cur->nextY;

    
    cur->prevY->nextY = insertee;
    insertee->prevY = cur->prevY;
    insertee->nextY = cur;
    cur->prevY = insertee;    
}

double List::distance(double a, double b){
    double dist = a-b;
    if(dist>=0)
        return dist;
    return -dist;
}
