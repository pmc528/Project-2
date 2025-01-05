// --------------------- graphl.h -----------------------------------------
//
// Shyawn Karim, CSS 343
// Created:         October 26, 2015
// Last Modified:   Novemeber 12, 2015
// --------------------------------------------------------------
// Purpose: Implement Dijkstra's shortest path algorithm by reading in a
// data file consisting of many lines and be able to find the lowest cost
// paths.  Then display the cost and path from every node to to every
// other node.
// --------------------------------------------------------------
// Assumptions: All input data is assumed to be correctly formatted
// and valid.
// --------------------------------------------------------------

#ifndef DIJKSTRASSHORTESTPATH_GRAPHL_H
#define DIJKSTRASSHORTESTPATH_GRAPHL_H


#include "nodedata.h"
#include <iostream>
#include <fstream>

using namespace std;


int const MAXNODES_L = 101;  // const size of an array
//--------------------------  class GraphL  ---------------------------------
//  ADT: GraphL calculates depth-first algorithm (search alway starts at
//  node #1).Reads data from provided data file, and find the depth-firts
//  recovery path. Also, display all inforamtion of the current  GraphL.
//
//  Implementation and assumptions:
//  -- Implemenet as Graph by using array and linked list
//  -- Implemenet depth-fist algorithm
//  -- Assumption: the data file has to be correct in order to build
//     object GraphL.
//---------------------------------------------------------------------------
class GraphL
{
public:
    // Constructor and Destructor
    GraphL();
    ~GraphL();

    // Functions
    void buildGraph(ifstream&);
    void depthFirstSearch();
    void displayGraph();
private:
    int size;
    struct EdgeNode;               // struct declaration
    struct GraphNode
    {
        EdgeNode* edgeHead;        // head of the list of edges
        NodeData* data;            // data information about each node
        bool visited;
    };
    GraphNode node_array[MAXNODES_L];

    struct EdgeNode
    {
        int adjGraphNode;           // subscript of the adjacent graph node
        EdgeNode* nextEdge;         // next node
    };

    // Delete object
    void makeEmpty();

    // helper for depthFirstSearch()
    void depthFirstSearchHelper(int v);
};


#endif //DIJKSTRASSHORTESTPATH_GRAPHL_H
