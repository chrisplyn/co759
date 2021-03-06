#ifndef __GRAPH_H__
#define __GRAPH_H__


#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "RelaxedLP.h"
#include "DFS.h"
#include "Bimap.h"
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
	int n;  // number of nodes of G
	int num_g_star_prime_Edges; //number of edges in G*'
	int *edgeList; 		//store the edge of G*'
	double *capList;	//store capacity of each edge
	Bimap map;	//mapping node in G to G*'
	
	/****************
	*Heuristic 1	
	****************/
	set *adjacencyList;
	RelaxedLP *rlp;	
	double *lp_sol;	//lp solution x*	
	std::vector<Component> components;	//store connected components 
	bool *visited;	
	int G_numEdges ;	
	int const * G_edgeList;
	
	/****************
	*graph utility functions 	
	****************/
	void destruct();	//free memory
	static void construct_adjacencyList(double ,int&, int , const int*, double *, set *);
	void construct_graph(double);	

public:

	Graph(RelaxedLP &);
	~Graph();
	int get_g_star_prime_num_nodes() const; //return number of nodes in the G*'
	int get_g_star_prime_num_edges() const; //return number of edges in the G*'
	int const * const get_edgeList() const;	// return a const ptr to edgeList of G*'
	double const * const get_capList() const;	//return capacity of each edge in G*'
	bool check_integrality();	//check whether x* is integral	
	
	void construct_g_star();	//construct G*
	void construct_g_star_2();	//construct G*2
	void construct_g_star_prime(); //contruct G*'
	const Bimap& get_g_prime_node_map() const;	//return node mapping of G->G*'	
	std::vector<Component> find_odd_cut_set();	//return connect component of odd size
};	

#endif
