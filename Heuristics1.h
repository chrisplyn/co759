#ifndef __HEURISTICS1__H
#define __HEURISTICS1__H

#include "RelaxedLP.h"
#include "Graph.h"

class Heuristics1
{
private:
	// std::vector<IntPair> const * const adjacencyList;
	// CO759lp *lp;
	// Graph *g;
	static std::vector<int> findGamma(Component &, RelaxedLP &);	
	static int add_constraint_util(std::vector<int>&, int, RelaxedLP &);
	static int min(int, int);
public:
	// Heuristics1(RelaxedLP &, Graph &);
	// ~Heuristics1();
	static void add_constraint(RelaxedLP &, Graph& );
	
};

#endif
