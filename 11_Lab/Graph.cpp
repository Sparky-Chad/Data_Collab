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
// For the use of a queue data structure in the BFS
#include "Queue.h"

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

/*
    The Depth Search Function and recursive helper function will search through the
    graph and continue deeper before moving to the side. This will return a linked list
    which holds the values starting with the beginning by which the program searched

    The helper Function will be made to better hold a recursive system
*/
LinkedList<int> Graph::DFS(int v)
{
    // new Boolean array of the size as the graph
    bool *visited = new bool[size];
    for (int i = 0; i < size; i++)
    {
        visited[i] = false;
    }
    visited[v] = true;

    // Create the output linked list
    LinkedList<int> output;
    output.addItem(new int(v));

    // Get a list of out edges
    LinkedList<int> edges = this->outEdge(v);
    int* temp;

    temp = edges.SeeAt(0);
    while(temp != nullptr)
    {
        if(!visited[*temp]){
            LinkedList<int>* passer = &output;
            DFS_Recursive(*temp, visited, passer);
        }
        temp = edges.SeeNext();
    }
    
    delete[] visited;
    return output;
}

// The helper function will just utilize the functions which have been given to the program
// and will not need to make any returns
void Graph::DFS_Recursive(int v, bool* visited, LinkedList<int>* output)
{
    // Use initialization to set visited and add to out
    visited[v] = true;
    output->addItem(new int(v));

    // Now get the edges of the current vertice and then attempt traversal
    LinkedList<int> edges = this->outEdge(v);
    int* temp;

    temp = edges.SeeAt(0);
    while(temp != nullptr)
    {
        if(!visited[*temp])
        {
            DFS_Recursive(*temp, visited, output);
        }
        temp = edges.SeeNext();
    }
}
// Referenced: https://www.tutorialspoint.com/data_structures_algorithms/depth_first_traversal.htm

/*
    The BFS function uses an older implemented queue class to hold its values.
    The linked list will still be the output in this case but all of the 
*/
LinkedList<int> Graph::BFS(int v)
{
    // Create the initialization
    bool* visited = new bool[size];
    for(int i = 0; i < size; i++)
    {
        visited[i] = false;
    }
    visited[v] = true;

    // Create the linked list and the queue
    LinkedList<int> output;

    // The queue will be used as essentially a buffer. It
    // will check if the edges given by verticies have been
    // visited to prevent duplicates
    Queue<int> queue(size);
    int* current = nullptr;

    int* processing;
    queue.enque(new int(v));

    LinkedList<int> edges;

    // During the while loop, add the value to the list and then add
    // the others to the visited list. And add them to the queue if not 
    // already have been visited
    while(!queue.checkempty())
    {
        current = queue.deque();
        output.addItem(current);

        edges = this->outEdge(*current);

        processing = edges.SeeAt(0);

        while(processing != nullptr)
        {
            if(!visited[*processing])
            {
                visited[*processing] = true;
                v = *processing;
                queue.enque(new int(v));
            }
            processing = edges.SeeNext();
        }

        edges.Reset();

    }

    delete[] visited;
    return output;
}
// Referenced: https://www.tutorialspoint.com/data_structures_algorithms/breadth_first_traversal.htm

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