/*
    Implementing the class graph.h file such that it follows 
    the specifications given by the lab assignment.
*/
#define GRAPH_DEFAULT_SIZE 50
// Class Being Defined
#include "Graph.h"
// Class with some standard exception classes
#include <stdexcept>
// For the Linked Lists
#include "LinkedList.h"
Graph::Graph()
{
    size = GRAPH_DEFAULT_SIZE;
    graph = new bool*[size];
    // Assign for each row a new 

    for(int i = 0; i < size; i++)
    {
        graph[i] = new bool[size];
        for(int j = 0; j < size; j++)
        {
            // Set the normal value to false
            graph[i][j] = false;
        }
    }
}

Graph::Graph(int in_size)
{
    size = in_size;
    graph = new bool*[size];

    //Assign a row to each element
    for(int i = 0; i < size; i++)
    {
        graph[i] = new bool[size];
        for(int j = 0; j < size; j++)
        {
            // Set normal value to false
            graph[i][j] = false;
        }
    }
}

Graph::~Graph()
{
    for(int i = 0; i < size; i++)
    {
        delete[] graph[i];
    }
    delete graph;
    size = 0;
}

void Graph::addEdge(int v, int e)
{
    _in_range_checker(v, e);
    
    if(graph[v][e]) throw GraphExceptions::OutEdgeExistsAlready();

    // If there were no exceptions then add this to the value
    // Now the vertice v has and edge outbound to e
    graph[v][e] = true;
    
}

// This function will remove the outbound edge to another vertice
// Also will sanitize the inputs and throw errors if the edge does not
// already exist
void Graph::removeEdge(int v, int e)
{
    _in_range_checker(v, e);

    if(!graph[v][e]) throw GraphExceptions::OutEdgeDoesntExist();

    graph[v][e] = false;
}

// Check Edge will return a boolean of whether v has an outbound edge with e
bool Graph::hasEdge(int v, int e)
{
    _in_range_checker(v, e);

    // Return if the edge exists
    return graph[v][e];
}

// Return a linked list of the ints which this shares an
// outbound border with
LinkedList<int> Graph::outEdge(int v)
{
    _in_range_checker(v);
    LinkedList<int> output;

    // Now iterate through the list and return the index 
    // if it contains an outbound edge
    for(int i = 0; i < size; i++)
    {
        if(graph[v][i])
        {
            output.addItem(new int(i));
        }
    }

    // Return the linked list
    return output;    
}

// Return a linked list of the verticies which have an
// inbound edge with the given vertice
LinkedList<int> Graph::inEdge(int v)
{
    _in_range_checker(v);
    LinkedList<int> output;

    // Iterate through the edges that may have an
    // inbound connection to the given vertice
    for(int i = 0; i < size; i++)
    {
        if(graph[i][v])
        {
            output.addItem(new int(i));
        }
    }

    // Return Linked List
    return output;
}


// Exception handler for input values
void Graph::_in_range_checker(int v, int e)
{
    // This checks for an out of range fatal exception
    if(v >= size || v < 0)
    {
        throw std::out_of_range("v index: Out of Range");
    }
    if(e >= size || e < 0)
    {
        throw std::out_of_range("e index: Out of Range");
    }
}