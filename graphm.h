// --------------------- graphm.h -----------------------------------------
// --------------------------------------------------------------
// Purpose: Implement Dijkstra's shortest path algorithm by reading in a
// data file consisting of many lines and be able to find the lowest cost
// paths.  Then display the cost and path from every node to to every
// other node.
// --------------------------------------------------------------
// Assumptions: All input data is assumed to be correctly formatted
// and valid.
// --------------------------------------------------------------


#ifndef DIJKSTRASSHORTESTPATH_GRAPHM_H
#define DIJKSTRASSHORTESTPATH_GRAPHM_H


#include "nodedata.h"
#include <fstream>
#include <iostream>

using namespace std;

int const MAXNODES_M = 101;                 // constant size for T and C table


class GraphM
{
public:
    // Constructor
    GraphM();

    // Functions
    void buildGraph(ifstream&);
    void findShortestPath();
    bool insertEdge(int from, int to, int dist);
    bool removeEdge(int from, int to);
    void display(int from, int to);
    void displayAll();

private:
    struct TableType
    {
        bool visited;                       // whether node has been visited
        int dist;                           // shortest distance from source known so far
        int path;                           // previous node in path of min dist
    };

    NodeData data[MAXNODES_M];              // data for graph nodes
    int C[MAXNODES_M][MAXNODES_M];          // cost array, the adjacency matrix
    int size;                               // number of nodes in the graph
    TableType T[MAXNODES_M][MAXNODES_M];    // stores visited, distance, path

    // helper for display()
    void findData(int from, int to);

    // helper for display() and displayAll()
    void findPath(int from, int to);
};


#endif //DIJKSTRASSHORTESTPATH_GRAPHM_H
