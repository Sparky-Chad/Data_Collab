#include "LinkedList.h"
#include "Graph.h"

#include <stdio.h>

#include <iostream>

int main()
{
    // Create a graph with a certain size
    Graph graph(25);

    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < rand()%6; j++)
        {
            try
            {
                graph.addEdge(i, rand()%25);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
        }
    }

    std::cout << "BFS Output\n";
    LinkedList<int> temp = graph.BFS(3);
    temp.Draw();

    std::cout << std::endl << "DFS Output\n";
    temp = graph.DFS(1);
    temp.Draw();

}