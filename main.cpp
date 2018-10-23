#include <iostream>
#include <cstdio>
#include "list.h"
#include <mpi.h>
#include <getopt.h>
#include "graph.h"
#include <cstdlib>
#include "listNode.h"
#include <climits>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#define TASK_TAG 1
#define AVAILABLE_TAG 2
#define FINALIZE_TAG 3

using namespace std;

typedef struct{
  int globalMIN;
  int partialMIN;
  int cityToVisit;
  int cityVisitedCount;
  int cityVisited[];
} task;

task *createNewTask(int a, int b)
{
  task *t = (task *)malloc((sizeof(task) + sizeof(int) * b )*a);
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < b; j++) {
      t[i].cityVisited[j] = 0;
    }
  }
  return t;
}

MPI_Datatype createTaskType(int n)
{
  MPI_Datatype taskType;

  MPI_Type_contiguous(n + 4, MPI_INT, &taskType);
  MPI_Type_commit(&taskType);

  return taskType;
}

void masterWork(graph *grp)
{
  int n = grp->getNumNodes();
  MPI_Datatype taskType = createTaskType(n);
  MPI_Status status;
  task *t,*tt, *tasks;
  listNode *node;
  list *taskList, *availableWorkers;
  int globalMIN = INT_MAX;
  int rank;

  taskList = new list;
  availableWorkers = new list;

  for (int i = 0; i < n-1; ++i) {
    t = createNewTask(1,n);
    t->cityToVisit = i + 1;
    t->globalMIN = INT_MAX;
    t->partialMIN = 0;
    t->cityVisitedCount = 1;
    node = new listNode;
    node->setData(t);
    taskList->EnqueueNode(node);
  }

  int s = n-1;
  do {
    MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    if(status.MPI_TAG == AVAILABLE_TAG)
    {
      MPI_Recv(&rank, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, &status);
      if(taskList->getItemCount() > 0)
      {
        tt = (task *)taskList->Dequeue()->getData();
        tt->globalMIN = globalMIN;
        MPI_Send(tt, 1, taskType, rank, TASK_TAG, MPI_COMM_WORLD);
      }
    }
    else
    {
      MPI_Recv(&rank, 1, MPI_INT, status.MPI_SOURCE, status.MPI_TAG, MPI_COMM_WORLD, &status);
    }
    MPI_Send(&rank, 1, MPI_INT, rank, FINALIZE_TAG, MPI_COMM_WORLD);
    s--;
  } while(s);

}

void slaveWork(graph *grp, int rank)
{
  int n = grp->getNumNodes();
  MPI_Datatype taskType = createTaskType(n);
  MPI_Status status;
  listNode *node = new listNode();

  do {
    MPI_Send(&rank, 1, MPI_INT, 0, AVAILABLE_TAG, MPI_COMM_WORLD);
    MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

    if(status.MPI_TAG == FINALIZE_TAG)
      break;

    
  } while(1);

}

int main(int argc, char** argv)
{
  int rank, size;
  int *matrix;
  int nFlag = 0, fFlag = 0;
  int option = 0;
  int numNodes;
  char *filename = 0;
  MPI_Datatype matrixType;

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


  graph *grp;
  //listNode *node = new listNode;


  if(rank == 0)
  {
    grp = new graph(numNodes,filename);

    matrix = grp->getMatrix();

    MPI_Type_contiguous(numNodes*numNodes, MPI_INT, &matrixType);
    MPI_Type_commit(&matrixType);
    MPI_Bcast(matrix, 1, matrixType, 0, MPI_COMM_WORLD);

    matrix = 0;
    masterWork(grp);
  }
  else
  {
    grp = new graph();

    MPI_Type_contiguous(numNodes*numNodes, MPI_INT, &matrixType);
    MPI_Type_commit(&matrixType);
    matrix = new int[numNodes*numNodes];
    //MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
    MPI_Bcast(matrix, 1, matrixType, 0, MPI_COMM_WORLD);

    grp->setNumNodes(numNodes);
    grp->setMatrix(matrix);
    slaveWork(grp,rank);
  }

  MPI_Finalize();
  return 0;
}

/*#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  int rank, size;
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if(rank == 0){
    MPI_Status status;
    MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    cout << status.MPI_SOURCE << '\n';
  }else{
    MPI_Send(&rank, 1, MPI_INT, 0, 7, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}*/
