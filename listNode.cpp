#include "listNode.h"

listNode::listNode()
{
  data = 0;
  prev = 0;
  next = 0;
}

listNode::~listNode()
{

}

void listNode::setPrev(listNode *node)
{
  this->prev = node;
}

void  listNode::setNext(listNode *node)
{
  this->next = node;
}

listNode *listNode::getPrev()
{
  return this->prev;
}

listNode *listNode::getNext()
{
  return this->next;
}
