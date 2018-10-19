#ifndef LISTNODES_H
#define LISTNODES_H

#include <iostream>

using namespace std;

class listNode
{
  void *data;
  listNode *prev;
  listNode *next;
public:
    listNode();
    ~listNode();
    void *getData();
    listNode *getPrev();
    listNode *getNext();
    void setData(void *);
    void setPrev(listNode *);
    void setNext(listNode *);

};

#endif // LISTNODES_H
