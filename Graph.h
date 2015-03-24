#ifndef __GRAPH_H__
#define __GRAPH_H__


#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "RelaxedLP.h"
#include "DFS.h"
#include <unordered_set>
#include <utility>
#define LP_EPSILON 0.000001

typedef std::pair<int,int> IntPair;


//internal representation of edge
struct edge {
	int tail,head,inverse;
	double capacity, flow;
	edge():tail(0),head(0),inverse(0),capacity(0.0),flow(0.0){}
	
	//overload operator<, required for sorting and binary search
	bool operator<(const edge& other) const{
        if(tail != other.tail){
        	return (tail < other.tail);
        }else{
        	return (head < other.head);
        }
    }
};


struct node{	
	int id;
	double mincap;  /**< capacity of minimum cut between node and parent in GH cut tree */
	int parent;	/*ptr to its parent in GH-tree*/
	bool s_side; /*true is this node is on side of min-cut*/

	//default constructor
	node():id(0),mincap(0.0),parent(0),s_side(false){};	
	
	//overload operator< for sorting
	bool operator<(const node& other) const{
		return (mincap < other.mincap);
    }		
};


class Graph
{
private:
	/****************
	*Ford-Fulkerson & Padberg-Rao 	
	****************/
	int n;  // number of nodes
	int numEdges;	//number of edges in original graph
	int *edgeList; 	
	double *capList;	//store capacity of each edge
	
	
	/****************
	*Heuristic 1	
	****************/
	set *adjacencyList;
	RelaxedLP *rlp;
	double *lp_sol;
	std::vector<Component> components;
	bool *visited;
	int G_numEdges ;
	void destruct();
	
	/****************
	*graph utility functions 	
	****************/

public:

	Graph(RelaxedLP &);
	~Graph();
	int get_num_nodes() const; //return number of nodes in the graph
	int get_num_edges() const; //return number of edges in the graph
	void convert_g_star(); //contruct graph from input file
	bool check_integrality();
	int const * const get_edgeList() const;	// return a const ptr to edgeList, edgeList is not allowed to be modified
										// const applies to the item to its left 
										// or if there is no item to its left, the item to its right)
	void construct_g_star();
	double const * const get_capList() const;	
	std::vector<Component> find_odd_cut_set();
};	

#endif
