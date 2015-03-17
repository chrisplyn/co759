#ifndef __GRAPH_H__
#define __GRAPH_H__


#include <string>
#include <stdio.h>
#include <stdlib.h>


//internal representation of edge
struct edge {
	int tail=0,head=0,inverse=0;
	double capacity=0.0, flow=0.0;

	//overload operator<, required for sorting and binary search
	bool operator<(const edge& other) const{
        if(tail != other.tail){
        	return (tail < other.tail);
        }else{
        	return (head < other.head);
        }
    }
};



class Graph
{
private:
	/****************
	*store graph data 	
	****************/
	int n;  // number of nodes
	int numEdges;	//number of edges in original graph
	int *edgeList; 	
	double *capList;	//store capacity of each edge
	/****************
	*graph utility functions 	
	****************/

public:
	Graph();
	~Graph();
	int get_num_nodes() const; //return number of nodes in the graph
	int get_num_edges() const; //return number of edges in the graph
	void read_input_file(const std::string &); //contruct graph from input file
	
	int const * const get_edgeList() const;	// return a const ptr to edgeList, edgeList is not allowed to be modified
										// const applies to the item to its left 
										// or if there is no item to its left, the item to its right)
	double const * const get_capList() const;
	
};	

#endif