#ifndef __HEURISTICS1__H
#define __HEURISTICS1__H

#include "RelaxedLP.h"
#include "Graph.h"

class Heuristics1
{

public:
	static int add_constraint_util(Component&, int, RelaxedLP &);
	static std::vector<int> findGamma(Component &, RelaxedLP &);
	static void add_constraint(RelaxedLP &, Graph& );
};

#endif
