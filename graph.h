#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>

using namespace std;

class graph
{
  int numNodes;
  int *matrix;
public:
  graph();
  graph(int,char *);
  ~graph();
  void printMatrix();
  int getNumNodes();
  void setNumNodes(int);
  int *getMatrix();
  void setMatrix(int *);
};

#endif // GRAPH_H
