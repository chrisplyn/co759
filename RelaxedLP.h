#ifndef __RELAXEDLP_H__
#define __RELAXEDLP_H__

#include <cplex.h>
#include "lp.h"
#include "util.h"
#include <math.h>
#include <vector>
#include <utility> 
#include <string>
#define LP_EPSILON 0.000001

typedef std::pair<int,int> IntPair;

class RelaxedLP
{
private:
	/****************
	*store graph data 	
	****************/
	int numNodes;  // number of nodes
	int numEdges;	//number of edges in original graph G
	int *edgeList; 	
	int *weightList;	//store weight of each edge
	std::vector<IntPair> *adjacencyList; //adjacency list of original graph G
	double obj_val,*lp_sol;		//optimal value and solution of the relaxed LP problem
	CO759lp *lp;
	
	/****************
	*utility functions 	
	****************/
	void destruct();
	static int euclid_edgelen(int , int , double *, double *);


public:
	RelaxedLP();
	~RelaxedLP();
	int getprob(char *filename, int geometric_data=0, int seed=0, int ncount_rand=0 ,int gridsize_rand = 100);
	int init_relaxed_lp();
	const std::vector<IntPair> * const get_adjacencyList();
	
	int solve_relaxed_lp();
	int get_num_nodes();
	int get_num_edges();
	int const * get_edgeList();
	CO759lp * get_relaxed_lp();
	double * get_relaxed_lp_sol();
	double get_relaxed_lp_objval();	
	void print_relaxed_lp_sol();
	void write_relaxed_lp_sol(const std::string&);

};


#endif
