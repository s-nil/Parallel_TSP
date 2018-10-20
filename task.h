#ifndef TASK_H
#define TASK_H
#include <climits>

class task
{
  int globalMIN;
  int partialMIN;
  int cityToVisit;
  int visitedCount;
  int *visited;
public:
  task();
  task(int);
  ~task();
  int getGlobalMIN();
  int getPartialMIN();
  int getCityToVisit();
  int getVisitedCount();
  void setGlobalMIN(int);
  void setPartialMIN(int);
  void setCityToVisit(int);
  void setVisitedCount(int);
};

#endif // TASK_H
