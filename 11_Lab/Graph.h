#ifndef _GRAPH_H
#define _GRAPH_H

// Utilizes the linked list class as the return of its which the function
// shares an edge with
#include "LinkedList.h"

class Graph
{
public:

    // Constructors for the class
    Graph();
    Graph(int);
    // Destructor
    ~Graph();

    // Edges modulators
    void addEdge(int, int);
    void removeEdge(int, int);
    bool hasEdge(int, int);

    // Returning lists of the edges which exist
    LinkedList<int> outEdge(int);

    LinkedList<int> inEdge(int);

private:

    // Checks if both of the indexes are in range and does not need to be passed both of them
    void _in_range_checker(int v = 0, int e = 0);
    
    // Size variable which represents the number of verticies
    int size;
    // Create an array of booleans to represent the outer and inner edges
    // This array will use the first index as the root vertice and the row as the outbound one
    bool** graph;

};

#include <exception>
// Define Exception Classes within graph namespace
namespace GraphExceptions
{
    // Class Defined to consolidate Edge Errors
    class EdgeException : ::std::exception
    {};
    class OutEdgeExistsAlready: EdgeException
    { public: const char* what() const noexcept { return "Outbound Edge Exsists Already: Try Defining the Inbound Edge?\n"; } };
    class OutEdgeDoesntExist: EdgeException
    { public: const char* what() const noexcept { return "Outbound Edge Does not exist\n"; }};
}

#endif