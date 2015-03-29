#ifndef __FORDFULKERSON_H__
#define __FORDFULKERSON_H__

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define oo 1000000000.0




class FordFulkerson
{
private:
	const int n;  // number of nodes
	const int numEdges;
	int residualEdges;  // number of edges in residual network	
	int	const * const edgeList;
	double const * const capList;
	int *color;      // Needed for breadth-first search               
	int *pred;       // Array to store augmenting path
	int *predEdge;   // edgeTab subscript of edge used to reach vertex i in BFS
	int *firstEdge;  //indicating first in range of edges with a common tail(start point)	
	edge *edgeTab;	//store all edge objects of graph
	node * nodeList;

	static double min (double, double);
	int bfs (int, int);	
	static int tailThenHead(const void* , const void*); // this function must be static
														//used to compare edges
	void dumpEdges(int);	//output all edges in the graph						
	void dumpFinal();
	void construct_residual_graph();

public:
	FordFulkerson(const Graph&);
	~FordFulkerson();
	double max_flow(int, int);
	node* get_nodeList();
};

#endif
