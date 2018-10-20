EXECS=main list listNode
MPIC=mpic++
CPPFLAGS=-c -Wall

all: a

a: main.o list.o listNode.o graph.o task.o
	${MPIC} -o tsp main.o list.o listNode.o graph.o task.o

task: task.cpp
	${MPIC} ${CPPFLAGS} task.cpp

graph: graph.cpp
	${MPIC} ${CPPFLAGS} graph.cpp

list: list.cpp
	${MPIC} ${CPPFLAGS} list.cpp

listNode: listNode.cpp
	${MPIC} ${CPPFLAGS} -c listNode.cpp

main: main.cpp
	${MPIC} ${CPPFLAGS} -c main.cpp

clean:
	rm -rf *o tsp

cleanO:
	rm -rf *o

cleanE:
	rm -rf tsp
