#include "LinkedList.h"
#include "Graph.h"
#include "Queue.h"

using namespace std;
#include <iostream>

int main()
{

    //user input
    int numVert;
    int choice = 7;
    int fromVert;
    int toVert;
    LinkedList<int> temp;

    cout << "Number of verticies in graph:  " << endl;
    cin >> numVert;
    cout << endl;
    cout << "Verticies are numbered 0 to " << numVert - 1 << endl;
    cout << endl;
    Graph testGraph(numVert);

    cout << "Press 1 to add an edge to graph." << endl;
    cout << "Press 2 remove an edge from graph." << endl;
    cout << "Press 3 Find an edge in the graph." << endl;
    cout << "Press 4 Find the out edges of a vertices" << endl;
    cout << "Press 5 Find the in edges of a vertices" << endl;
    cout << "Press 6 to DFS" << endl;
    cout << "Press 7 to BFS" << endl;
    cout << "Press 8 to Quit" << endl;

    cout << endl;
    cout << "Choice:  ";
    cin >> choice;
    cout << endl;

    while (choice != 0) {

        switch (choice) {
            case 1:
                cout<<"Enter first vertice: "<<endl;
                cin >> fromVert;
                cout << "Enter second vertice: " << endl;
                cin >> toVert;
                try
                {
                    testGraph.addEdge(fromVert, toVert);
                    cout << "Edge between " << fromVert << " and " << toVert << " created..." << endl;
                    cout << endl;
                }
                catch(out_of_range e)
                {
                    cout << "Entered index which was out of bounds\n";
                }
                break;
            case 2:
                cout << "Enter first vertice: " << endl;
                cin >> fromVert;
                cout << "Enter second vertice: " << endl;
                cin >> toVert;
                testGraph.removeEdge(fromVert, toVert);
                cout << "Edge between " << fromVert << " and " << toVert << " removed..." << endl;
                cout << endl;
                break;
            case 3:
                cout << "Enter first vertice: " << endl;
                cin >> fromVert;
                cout << "Enter second vertice: " << endl;
                cin >> toVert;
                testGraph.hasEdge(fromVert, toVert);
                cout << "Edge between "<< fromVert << " and "<<toVert<<" found..." << endl;
                cout << endl;
                break;
            case 4:
                cout << "Enter vertice: " << endl;
                cin >> fromVert;
                cout << "The out edges for " << fromVert << " are: " << endl;
                
                temp = (testGraph.outEdge(fromVert));
                if (temp.isEmpty()) {
                    cout << "none"<<endl;
                    break;
                }
                for (int i = 0; i < numVert; i++) {
                    if (temp.SeeAt(i) != nullptr) {
                        cout << "->" << *(temp.SeeAt(i)) << endl;
                    }
                }
                temp.~LinkedList();
                cout << endl;
                break;
            case 5:
                cout << "Enter vertice: " << endl;
                cin >> toVert;
                cout << "The in edges for " << toVert << " are: " << endl;
                temp = (testGraph.inEdge(toVert));
                if (temp.isEmpty()) {
                    cout << "none" << endl;
                    break;
                }
                for (int i = 0; i < numVert; i++) {
                    if (temp.SeeAt(i) != nullptr) {
                        cout << "->" << *(temp.SeeAt(i)) << endl;
                    }
                }
                temp.~LinkedList();
                cout << endl;
                break;
            case 6:
                cout << "Enter vertice: " << endl;
                cin >> toVert;
                cout << "Verticies visited in DFS " << toVert << " are: " << endl;
                temp = (testGraph.DFS(toVert));
                if (temp.isEmpty()) {
                    cout << "none" << endl;
                    break;
                }
                for (int i = 0; i < numVert; i++) {
                    if (temp.SeeAt(i) != nullptr) {
                        cout << "->" << *(temp.SeeAt(i)) << endl;
                    }
                }
                temp.~LinkedList();
                cout << endl;
                break;
            case 7:
                cout << "Enter vertice: " << endl;
                cin >> toVert;
                cout << "Verticies visited in BFS" << toVert << " are: " << endl;
                temp = (testGraph.BFS(toVert));
                if (temp.isEmpty()) {
                    cout << "none" << endl;
                    break;
                }
                for (int i = 0; i < numVert; i++) {
                    if (temp.SeeAt(i) != nullptr) {
                        cout << "->" << *(temp.SeeAt(i)) << endl;
                    }
                }
                temp.~LinkedList();
                cout << endl;
                break;
            case 8:
                return 0;

        }

        cout << "Press 1 to add an edge to graph." << endl;
        cout << "Press 2 remove an edge from graph." << endl;
        cout << "Press 3 Find an edge in the graph." << endl;
        cout << "Press 4 Find the out edges of a vertices" << endl;
        cout << "Press 5 Find the in edges of a vertices" << endl;
        cout << "Press 6 to DFS" << endl;
        cout << "Press 7 to BFS" << endl;
        cout << "Press 8 to Quit" << endl;

        cout << endl;
        cout << "Choice:  ";
        cin >> choice;
        cout << endl;
    }


   /* // Create a graph with a certain size
    Graph graph(4);

    graph.addEdge(2, 3);
    graph.addEdge(3, 1);
    graph.addEdge(1, 3);
    graph.addEdge(0, 1);
    graph.addEdge(2, 0);
    graph.addEdge(1, 2);

    cout << "BFS Output\n";
    LinkedList<int> temp = graph.BFS(3);
    temp.Draw();

    cout << std::endl << "DFS Output\n";
    temp = graph.DFS(1);
    temp.Draw();*/

}