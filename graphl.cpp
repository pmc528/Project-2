// --------------------- graphl.cpp -----------------------------------------
// --------------------------------------------------------------
// Purpose: Implement Dijkstra's shortest path algorithm by reading in a
// data file consisting of many lines and be able to find the lowest cost
// paths.  Then display the cost and path from every node to to every
// other node.
// --------------------------------------------------------------
// Assumptions: All input data is assumed to be correctly formatted
// and valid.
// --------------------------------------------------------------

#include "graphl.h"
//#include "string.h"
//#include "limits.h"
#include <iomanip>

// --------------------- GraphL() -----------------------------------------
// Default constructor
// --------------------------------------------------------------
GraphL::GraphL()
{
    size = 0;

    for (int i = 1; i < MAXNODES_L; ++i){
        node_array[i].visited = false;
        node_array[i].edgeHead = NULL;
        node_array[i].data = NULL;
    }
}

// --------------------- ~GraphL() -----------------------------------------
// Destructor
// --------------------------------------------------------------
GraphL::~GraphL()
{
    makeEmpty();
}

// --------------------- makeEmpty() -----------------------------------------
// Deletes object
// Helper function for Destructor
// --------------------------------------------------------------
void GraphL::makeEmpty()
{
    for (int x = 1; x <= size; ++x)
    {
        node_array[x].visited = false;
        delete node_array[x].data;  // delete edge name
        node_array[x].data = NULL;  // set edge name to NULL

        if (node_array[x].edgeHead != NULL) // check for linked list in array index
        {
            EdgeNode* del = node_array[x].edgeHead;

            while (del != NULL) // traverse linked list
            {
                node_array[x].edgeHead = node_array[x].edgeHead->nextEdge;
                delete del; // delete node
                del = NULL; // set node to NULL
                del = node_array[x].edgeHead;   // move head
            }
        }
    }
}

// --------------------- buildGraph() -----------------------------------------
// Builds up graph node information and adjacency list of edges between each
// node reading from a data file
// --------------------------------------------------------------
void GraphL::buildGraph(ifstream& infile2)
{
    // read from data file
    infile2 >> size;            // sets the size
    string nodeName = "";       // name of each node
    getline(infile2, nodeName); // read line

    for (int i = 1; i <= size; ++i) // insert edge names
    {
        getline(infile2, nodeName);
        NodeData* tmp = new NodeData(nodeName);
        node_array[i].data = tmp;   // insert into array
    }

    int from, to;

    while (infile2 >> from >> to)   // fill linked list
    {
        if (from == 0)
        {
            break;
        }

        if (node_array[from].edgeHead == NULL)  // first node at array index
        {
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = to;            // insert adjacent
            node_array[from].edgeHead = node;   // point to head
            node_array[from].edgeHead->nextEdge  = NULL;
        }
        else    // additional nodes in linked list
        {
            EdgeNode* node = new EdgeNode;
            node->adjGraphNode = to;            // insert adjacent
            node->nextEdge = node_array[from].edgeHead;  // move pointer
            node_array[from].edgeHead = node;  // assign as head
        }
    }
}

// --------------------- depthFirstSearch() -----------------------------------------
// Makes a depth-first search and displays each node in depth-first order
// --------------------------------------------------------------
void GraphL::depthFirstSearch()
{
    cout << "Depth-fisrt ordering:";    // typo deliberate to match output

    for (int v = 1; v <= size; ++v) // loop through size
    {
        if (!node_array[v].visited)   // check if node has been visited
        {
            depthFirstSearchHelper(v);  // call helper
        }
    }

    cout << endl;
}

// --------------------- depthFirstSearchHelper() -----------------------------------------
// Helper function for depthFirstSearch()
// Recursively finds the depthFirstSearch
// --------------------------------------------------------------
void GraphL::depthFirstSearchHelper(int v)
{
    cout << setw(2) << v;   // print node
    node_array[v].visited = true;   // mark visited
    EdgeNode* current = node_array[v].edgeHead; // move pointer to head

    while (current != NULL) // loop till end of linked list
    {
        if (!node_array[current->adjGraphNode].visited) // check if visited
        {
            depthFirstSearchHelper(current->adjGraphNode);  // call helper
        }

        current = current->nextEdge;    // move pointer to next node in linked list
    }
}

// --------------------- displayGraph() -----------------------------------------
// Displays each node information and edge in the graph
// --------------------------------------------------------------
void GraphL::displayGraph()
{

    cout << "Graph:" << endl;

    for (int i = 1; i <= size; ++i) // print array info
    {
        // print index and name of the node
        cout << "Node" << i << "      " << *node_array[i].data << endl << endl;

        EdgeNode* current = node_array[i].edgeHead; // assign to current

        while (current != NULL) // check for linked list
        {
            // print linked list
            cout << setw(7) << "edge " << i << setw(2) << current->adjGraphNode << endl;
            current = current->nextEdge;  // move pointer to next node in linked list
        }
    }
}
