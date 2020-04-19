#This is the MakeFile for the project

CXX := g++
CXX_ARGS := -g -Wall

default: build

# Setup build for the main and for the other c++
# Files

build: Graph.o basic_tester.o LinkedList.h Graph.h
	$(CXX) $(CXX_ARGS) Graph.o basic_tester.o -o a.out
	
Graph.o: Graph.cpp LinkedList.h Queue.h Graph.h
	$(CXX) $(CXX_ARGS) -c Graph.cpp

basic_tester.o: basic_tester.cpp LinkedList.h Graph.h
	$(CXX) $(CXX_ARGS) -c basic_tester.cpp

clean:
	$(RM) *.o *.out ~*
