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

};
