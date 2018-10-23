#include "graph.h"

graph::graph()
{
  this->numNodes = 0;
  this->matrix = new int(numNodes*numNodes);
}

graph::graph(int numNodes, char * filename)
{
  this->numNodes = numNodes;
  this->matrix = new int[numNodes*numNodes];
  ifstream ifs(filename);
  for (int i = 0; i < numNodes * numNodes; ++i ) {
    ifs >> matrix[i];
  }
  ifs.close();
}

graph::~graph()
{

}

void graph::printMatrix()
{
  for (int i = 0;i < numNodes; ++i) {
    for (int j = 0; j < numNodes; ++j) {
      cout << matrix[numNodes * i + j] << ' ';
    }
    cout << '\n';
  }
}

int graph::getNumNodes()
{
  return numNodes;
}

void graph::setNumNodes(int n)
{
  numNodes = n;
}

int *graph::getMatrix()
{
  return matrix;
}

void graph::setMatrix(int *matrix)
{
  delete [] this->matrix;
  this->matrix = matrix;
}
