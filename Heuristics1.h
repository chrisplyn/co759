#ifndef __HEURISTICS1__H
#define __HEURISTICS1__H

#include "RelaxedLP.h"
#include "Graph.h"

class Heuristics1
{
private:
	std::vector<IntPair> const * const adjacencyList;
	CO759lp *lp;
	Graph *g;
	std::vector<int> findGamma(Component &);	
	int add_constraint_util(std::vector<int>&, int);
	static int min(int, int);
public:
	Heuristics1(RelaxedLP &, Graph &);
	~Heuristics1();
	void add_constraint();
	
};

#endif
