// --------------------- graphm.cpp -----------------------------------------
// --------------------------------------------------------------
// Purpose: Implement Dijkstra's shortest path algorithm by reading in a
// data file consisting of many lines and be able to find the lowest cost
// paths.  Then display the cost and path from every node to to every
// other node.
// --------------------------------------------------------------
// Assumptions: All input data is assumed to be correctly formatted
// and valid.
// --------------------------------------------------------------

#include "graphm.h"
//#include "string.h"
//#include "limits.h"
#include <iomanip>

// --------------------- Default Constructor -----------------------------------------
// Constructs an empty table and initializes all values
// --------------------------------------------------------------
GraphM::GraphM()
{
    size = 0;

    for (int i = 1; i < MAXNODES_M; i++)
    {
        for (int j = 1; j < MAXNODES_M; j++)
        {
            C[i][j] = INT_MAX;
            T[i][j].visited = false;
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
        }
    }
}

// --------------------- buildGraph() -----------------------------------------
// Builds up graph node information and adjacency matrix of edges
// between each node reading from a file
// --------------------------------------------------------------
void GraphM::buildGraph(ifstream& infile1)
{
    // read from data file
    infile1 >> size;                // sets the size
    string nodeName = "";           // name of each node
    getline(infile1, nodeName);     // read line

    for (int i = 1; i <= size; ++i)
    {
        data[i].setData(infile1);   // sets node names
    }

    int from, to, dist;

    while (infile1 >> from >> to >> dist)
    {
        if (from == 0)
        {
            break;  // reads file till from node is 0
        }

        C[from][to] = dist; // set the C table
    }
}
// --------------------- findShortestPath() -----------------------------------------
// Finds the shortest path between every node to every other node
// in the graph using Dijkstra's algorithm
// --------------------------------------------------------------
void GraphM::findShortestPath()
{
    for (int source = 1; source <= size; source++)
    {
        T[source][source].dist = 0;
        T[source][source].visited = true;

        for (int n = 1; n <= size; n++) // find neighbor nodes
        {
            if (C[source][n] != INT_MAX)
            {
                T[source][n].dist = C[source][n];
                T[source][n].path = source;
            }
        }

        int v = 0;  // smallest vertex

        do  // find smallest weight
        {
            int min = INT_MAX;
            v = 0;

            for (int n = 1; n <= size; n++) // find closest child and continue search
            {
                if (!T[source][n].visited && (C[source][n] < min))
                {
                    min = C[source][n];
                    v = n;
                }
            }

            if (v == 0)
            {
                break;  // end loop
            }

            T[source][v].visited = true;  // node visited

            for (int w = 1; w <= size; ++w)
            {
                if (T[source][w].visited)
                {
                    continue;
                }

                if (C[v][w] == INT_MAX)
                {
                    continue;
                }

                if (v == w)
                {
                    continue;
                }

                if (T[source][w].dist > T[source][v].dist + C[v][w])
                {
                    T[source][w].dist = T[source][v].dist + C[v][w];
                    T[source][w].path = v;
                }
            }
        }

        while (v != 0); // end loop
    }
}

// --------------------- insertEdge() -----------------------------------------
// Inserts an edge into a graph between 2 given nodes
// --------------------------------------------------------------
bool GraphM::insertEdge(int from, int to, int dist)
{
    // check to make sure insert is legal
    if (from > size || from < 1)
    {
        return false;
    }

    if (to > size || to < 1)
    {
        return false;
    }

    if (dist != 0 && from == to)
    {
        return false;
    }

    if (dist < 0)
    {
        return false;
    }

    C[from][to] = dist;   // edge inserted
    findShortestPath();   // redo Dijkstra's algorithm with change

    return true;
}

// --------------------- removeEdge() -----------------------------------------
// Removes an edge between 2 given nodes
// --------------------------------------------------------------
bool GraphM::removeEdge(int from, int to)
{
    // check to make sure remove is legal
    if (from > size || from < 1)
    {
        return false;
    }

    if (to > size || to < 1)
    {
        return false;
    }

    C[from][to] = INT_MAX;  // edge removed
    findShortestPath();     // redo Dijkstra's algorithm with change

    return true;
}

// --------------------- displayAll() -----------------------------------------
// Uses couts to demonstrate that the alogorithm works properly
// Uses helper function findPath()
// --------------------------------------------------------------

void GraphM::displayAll()
{
    // print table titles for readout
    cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
        << setw(14) << "Dijkstra's" << setw(7) << "Path" << endl;

    for (int from = 1; from <= size; from++)
    {
        cout << data[from] << endl << endl;     // print node name

        for (int to = 1; to <= size; to++)
        {
            if (T[from][to].dist != 0)
            {
                cout << setw(27) << from;   // print from node
                cout << setw(10) << to;     // print to node

                if (T[from][to].dist == INT_MAX)
                {
                    cout << setw(12) << "----" << endl; // no adjacent nodes
                }
                else
                {
                    cout << setw(12) << T[from][to].dist;   // print distance
                    cout << setw(10);

                    findPath(from, to); // call helper
                    cout << endl;
                }
            }
        }
    }
}

// --------------------- display() -----------------------------------------
// Uses couts to display the shortest distance with path info between the
// fromNode to the toNode
// Uses helper function findPath()
// Uses helper function findData()
// --------------------------------------------------------------
void GraphM::display(int from, int to)
{
    if ((from > size || from < 0) || (to > size || to < 0)) //check if edge exist
    {
        cout << setw(7) << from << setw(7) << to;   // print data
        cout << setw(15) << "----" << endl; // not valid

        return;
    }

    cout << setw(7) << from << setw(7) << to;   // print node from and to data

    if (T[from][to].dist != INT_MAX)    // adjacent node check
    {
        cout << setw(12) << T[from][to].dist << setw(15); // print distance

        findPath(from, to); // call helper
        cout << endl;

        findData(from, to); // call helper
    }
    else    // no adjacent node
    {
        cout << setw(15) << "----" << endl;
    }

    cout << endl;
}

// --------------------- findData() -----------------------------------------
// Helper function for display()
// Recursively finds data for the given edge distance
// --------------------------------------------------------------
void GraphM::findData(int from, int to)
{
    if (T[from][to].dist == INT_MAX)
    {
        return; // no data
    }

    if (from == to)
    {
        cout << data[to] << endl;   // print data

        return;
    }

    int nodeData = to; // assign to node to nodeData

    findData(from, to = T[from][to].path);  // call helper

    cout << data[nodeData] << endl << endl;    // print data
}

// --------------------- findPath() -----------------------------------------
// Helper function for display() and displayAll()
// Recursively finds path for a given edge
// --------------------------------------------------------------
void GraphM::findPath(int from, int to)
{
    if (T[from][to].dist == INT_MAX)
    {
        return; // no path
    }

    if (from == to)
    {
        cout << to << " ";  // print data

        return;
    }

    int pathData = to; // assign to path to pathData
    findPath(from, to = T[from][to].path);

    cout << pathData << " ";   // print path
}
