#include <iostream>
#include <cstdio>
#include "list.h"
#include <mpi.h>
#include <getopt.h>
#include "graph.h"
#include <cstdlib>
#include "listNode.h"
#include "task.h"
#define TASK_TAG 1
#define AVAILABLE_TAG 2
#define FINALIZE_TAG 3

using namespace std;

void masterWork(graph *grp)
{
  MPI_Status status;
  task *t,*tt, *tasks;
  listNode *node;
  list *taskList, *availableWorkers;
  int globalMIN = INT_MAX;
  int num = 1;
  int n = grp->getNumNodes();

  taskList = new list;
  availableWorkers = new list;

  for (int i = 0; i < n-1; ++i) {
    t = new task(n);
    t->setCityToVisit(i+1);
    t->setGlobalMIN(INT_MAX);
    t->setPartialMIN(0);
    t->setVisitedCount(1);
    node = new listNode;
    node->setData(t);
    taskList->EnqueueNode(node);
  }


  //MPI_Send(void* data,int count,MPI_Datatype datatype,int destination,int tag,MPI_Comm communicator)
  MPI_Send(&num,1,MPI_INT,1, 0,MPI_COMM_WORLD);
}

void slaveWork(graph *grp,int rank)
{
  int num;
  //MPI_Recv(void* data,int count,MPI_Datatype datatype,int source,int tag,MPI_Comm communicator,MPI_Status* status)
  MPI_Recv(&num,1, MPI_INT,0,0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  listNode *node = new listNode();


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
  listNode *node = new listNode;


  if(rank == 0)
  {
    grp = new graph(numNodes,filename);

    matrix = grp->getMatrix();

    MPI_Type_contiguous(numNodes*numNodes, MPI_INT, &matrixType);
    MPI_Type_commit(&matrixType);
    MPI_Bcast(matrix, 1, matrixType, 0, MPI_COMM_WORLD);

    masterWork(grp);
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

    slaveWork(grp,rank);
  }


  MPI_Abort(MPI_COMM_WORLD,911);
  //MPI_Finalize();
  return 0;
}
