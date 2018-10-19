#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "listNode.h"

using namespace std;

class list
{
  listNode *head;
  listNode *tail;
  int itemCount;
public:
  list();
  ~list();
  void EnqueueNode(listNode *);
  listNode *Dequeue();
  int getItemCount();
  void setItemCount(int itemCount);
  listNode *getHead();
  listNode *getTail();

};

#endif // LIST_H
