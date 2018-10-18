EXECS=main list listNode
MPIC=mpic++
#CPPFLAGS=-std=c++0x

all: a

a: main.o list.o listNode.o
	${MPIC} -o tsp main.o list.o listNode.o

list: list.cpp
	${MPIC} -c list.cpp

listNode: listNode.cpp
	${MPIC} -c listNode.cpp

main: main.cpp
	${MPIC} -c main.cpp

clean:
	rm -rf *o tsp

cleanO:
	rm -rf *o

cleanE:
	rm -rf tsp
