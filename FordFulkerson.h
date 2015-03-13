#ifndef __FORDFULKERSON_H__
#define __FORDFULKERSON_H__


#include <string>
#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define oo 1000000000

//internal representation of edge
struct edge {
	int tail=0,head=0,capacity=0,flow=0,inverse=0;
	// bool operator<(const edge& other) const{
 //        if(tail != other.tail){
 //        	return (tail < other.tail);
 //        }else{
 //        	return (head < other.head);
 //        }
 //    }
};

class FordFulkerson
{
private:
	int n;  // number of nodes
	int residualEdges;  // number of edges in residual network
	
	int *firstEdge;  // Table indicating first in range of edges with a common tail(start point)
	int *color;      // Needed for breadth-first search               
	int *pred;       // Array to store augmenting path
	int *predEdge;   // edgeTab subscript of edge used to reach vertex i in BFS
	edge *edgeTab;


	int min (int, int);
	int bfs (int, int);
	
	void dumpEdges(int);
	void dumpFinal();
	static int tailThenHead(const void* , const void* ); // this function must be static

public:
	FordFulkerson();
	~FordFulkerson();
	int max_flow (int, int);
	void read_input_file(std::string &);

	
	//void read_input_file(int *);
};

#endif