#include "list.h"

list::list()
{
  head = 0;
  tail = 0;
  itemCount = 0;
}

list::~list()
{

}

void list::EnqueueNode(listNode *node)
{
  if(!this->head && !this->tail)
  {
    this->head = node;
    this->tail = node;
  }
  else
  {
    node->setPrev(this->tail);
    this->tail->setNext(node);
    this->tail = node;
  }
  this->itemCount++;
}

listNode *list::Dequeue()
{
  listNode *n = 0;
  n = this->head;
  if(this->itemCount == 1)
  {
    n->setPrev(0);
    n->setNext(0);
    this->head = 0;
    this->tail = 0;
    this->itemCount = 0;
  }
  else if (this->itemCount > 1)
  {
    this->head = this->head->getNext();
    this->head->setPrev(0);
    n->setNext(0);
    n->setPrev(0);
    this->itemCount--;
  }
  return n;
}

int list::getItemCount()
{
  return itemCount;
}

void list::setItemCount(int itemCount)
{
  this->itemCount = itemCount;
}
