MPIC=mpic++
CPPFLAGS=-c -Wall
PROGRAM=tsp

all: a

a: list.o listNode.o graph.o
	${MPIC} main.cpp list.o listNode.o graph.o -o ${PROGRAM}

graph: graph.cpp
	${MPIC} ${CPPFLAGS} graph.cpp

list: list.cpp
	${MPIC} ${CPPFLAGS} list.cpp

listNode: listNode.cpp
	${MPIC} ${CPPFLAGS} listNode.cpp

clean:
	rm -rf *o tsp

cleanO:
	rm -rf *o

cleanE:
	rm -rf tsp
