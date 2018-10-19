#include <iostream>
#include <cstdio>
#include "list.h"
#include <mpi.h>
#include <getopt.h>
#include "graph.h"
#include <cstdlib>
#include "listNode.h"

using namespace std;

void masterWork(int rank)
{
  cout << 'a' << '\n';
}

void slaveWork(int rank)
{
  cout << 'b' << '\n';
  
}

int main(int argc, char** argv)
{
  //cout << "hello world\n";
  int rank, size;
  int *matrix;
  int nFlag = 0, fFlag = 0;
  int option = 0;
  int numNodes;
  char *filename = 0;

  while((option = getopt(argc,argv,":n:f:"))!=-1)
  {
    switch (option) {
      case 'n':
        numNodes = atoi(optarg);
        nFlag = 1;
        break;
      case 'f':
        filename = optarg;
        fFlag = 1;
        break;
      case ':':
        cerr << "Option -" << optopt << " requires an operand" << '\n';
        exit(-1);
      case '?':
        cerr << "Unrecognized option: -" << optopt << '\n';
        exit(-1);
    }
  }

  if(!nFlag || !fFlag){
    if(!nFlag){
      cerr << "use -n option to give number of nodes" << '\n';
    }
    if (!fFlag) {
      cerr << "use -f option to give filename" << '\n';
    }
    exit(-1);
  }

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  MPI_Datatype matrixType;
  graph *grp;
  listNode *node = new listNode();

  int a = 2;
  node->setData(&a);

  if(rank == 0)
  {
    grp = new graph(numNodes,filename);

    matrix = grp->getMatrix();

    MPI_Type_contiguous(numNodes*numNodes, MPI_INT, &matrixType);
    MPI_Type_commit(&matrixType);
    MPI_Bcast(matrix, 1, matrixType, 0, MPI_COMM_WORLD);

    masterWork(rank);
  }
  else
  {
    grp = new graph();

    MPI_Type_contiguous(numNodes*numNodes, MPI_INT, &matrixType);
    MPI_Type_commit(&matrixType);
    matrix = new int(numNodes*numNodes);
    MPI_Bcast(matrix, 1, matrixType, 0, MPI_COMM_WORLD);

    grp->setNumNodes(numNodes);
    grp->setMatrix(matrix);

    slaveWork(rank);
  }


  MPI_Abort(MPI_COMM_WORLD,911);
  //MPI_Finalize();
  return 0;
}
