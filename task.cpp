#include "task.h"

task::task()
{

}

task::task(int n)
{
  globalMIN = INT_MAX;
  cityToVisit = 0;
  partialMIN = 0;
  visitedCount = 0;
  visited = new int[n];
  for (int i = 0; i < n; ++i) {
    visited[i] = 0;
  }
}

task::~task()
{

}

int task::getGlobalMIN()
{
  return globalMIN;
}

int task::getPartialMIN()
{
  return partialMIN;
}

int task::getCityToVisit()
{
    return cityToVisit;
}

int task::getVisitedCount()
{
  return visitedCount;
}
void task::setGlobalMIN(int g)
{
  globalMIN = g;
}

void task::setPartialMIN(int p)
{
  partialMIN = p;
}

void task::setCityToVisit(int n)
{
  cityToVisit = n;
}

void task::setVisitedCount(int c)
{
  visitedCount = c;
}
