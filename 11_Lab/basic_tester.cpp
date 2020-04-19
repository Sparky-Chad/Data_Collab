#include "LinkedList.h"
#include "Graph.h"


#include <iostream>

int main()
{
    // Create a graph with a certain size
    Graph graph(4);

    graph.addEdge(2, 3);
    graph.addEdge(3, 1);
    graph.addEdge(1, 3);
    graph.addEdge(0, 1);
    graph.addEdge(2, 0);
    graph.addEdge(1, 2);

    std::cout << "BFS Output\n";
    LinkedList<int> temp = graph.BFS(3);
    temp.Draw();

    std::cout << std::endl << "DFS Output\n";
    temp = graph.DFS(1);
    temp.Draw();

}