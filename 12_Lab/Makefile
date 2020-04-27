# Just defined now to run default as the tester


CXX := g++
CXX_ARGS := -g -Wall

default: tester


tester: tester.cpp algorithms.h Queue.h
	$(CXX) $(CXX_ARGS) tester.cpp -o a.out



clean:
	$(RM) *.o *.out ~*